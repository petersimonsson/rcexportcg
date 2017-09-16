/**************************************************************************
  RCExportCG
  Copyright (C) 2017  Peter Simonsson <peter.simonsson@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/
#include "rundowncreator.h"
#include "rundown.h"
#include "rundownrow.h"
#include "rundownrowmodel.h"
#include "folder.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

RundownCreator::RundownCreator(QObject *parent) : QObject(parent)
{
    m_netManager = new QNetworkAccessManager(this);

    connect(m_netManager, &QNetworkAccessManager::finished, this, &RundownCreator::handleFinished);

    m_rundownRowModel = new RundownRowModel(this);
}

RundownCreator::~RundownCreator()
{
    qDeleteAll(m_folderHash);
    m_folderHash.clear();
}

QUrlQuery RundownCreator::createRequestQuery(const QString &action, const QList<QPair<QString, QString> > &extraItems) const
{
    QUrlQuery query;
    query.addQueryItem("APIKey", m_apiKey);
    query.addQueryItem("APIToken", m_apiToken);
    query.addQueryItem("Action", action);

    QList<QPair<QString, QString> >::const_iterator it = extraItems.begin();
    for(;it != extraItems.end(); ++it)
    {
        query.addQueryItem((*it).first, (*it).second);
    }

    return query;
}

void RundownCreator::getFoldersAndRundows()
{
    QUrl requestUrl = m_apiUrl;
    requestUrl.setQuery(createRequestQuery("getFolders"));

    QNetworkRequest request(requestUrl);
    m_netManager->get(request);
    emit status(tr("Fetching folders..."));
}

void RundownCreator::getRundowns()
{
    QUrl requestUrl = m_apiUrl;
    requestUrl.setQuery(createRequestQuery("getRundowns"));

    QNetworkRequest request(requestUrl);
    m_netManager->get(request);
    emit status(tr("Fetching Rundowns..."));
}

void RundownCreator::fetchRows(quint32 rundownId)
{
    QUrl requestUrl = m_apiUrl;
    QList<QPair<QString, QString> > extraItems;
    extraItems.append(QPair<QString, QString>("RundownID", QString::number(rundownId)));
    extraItems.append(QPair<QString, QString>("GetObjects", "true"));
    extraItems.append(QPair<QString, QString>("GetRowsWithoutObjects", "false"));
    requestUrl.setQuery(createRequestQuery("getRows", extraItems));

    QNetworkRequest request(requestUrl);
    m_netManager->get(request);
    emit status(tr("Fetching Rows..."));
}

void RundownCreator::handleFinished(QNetworkReply *reply)
{
    QString query = reply->url().query();
    QByteArray data = reply->readAll();
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    switch(statusCode)
    {
    case 200:
        if(query.contains("Action=getRundowns"))
            handleRundowns(data);
        else if (query.contains("Action=getRows"))
            handleRows(data);
        else if(query.contains("Action=getFolders"))
            handleFolders(data);
        else
            qDebug() << data;
        break;
    case 400:
        emit error(tr("Bad request to RundownCreator: %1").arg(QString::fromUtf8(data)));
        break;
    case 401:
        emit error(tr("Authentication with RundownCreator failed"));
        break;
    case 500:
        emit error(tr("Internal RundownCreator server error."));
        break;
    default:
        emit debug(tr("Code: %1 Data: %2").arg(statusCode).arg(QString::fromUtf8(data)));
        break;
    }

    reply->deleteLater();
}

void RundownCreator::handleRundowns(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonArray array = doc.array();

    foreach(const QJsonValue &value, array)
    {
        QJsonObject object = value.toObject();
        Rundown *rundown = new Rundown(object.value("RundownID").toInt(),
                                       object.value("Title").toString());
        rundown->setFolderId(object.value("FolderID").toInt());
        rundown->setFrozen(object.value("Frozen").toInt());
        rundown->setLocked(object.value("Locked").toInt());
        rundown->setArchived(object.value("Archived").toInt());
        rundown->setTemplate(object.value("Template").toInt());
        rundown->setDeleted(object.value("Deleted").toInt());
        Folder *folder = m_folderHash.value(rundown->folderId());

        if(folder)
        {
            folder->appendRundown(rundown);
        }
        else
        {
            emit error(tr("Did not find the folder for %1").arg(rundown->title()));
            delete rundown;
        }
    }

    emit rundownsReceived();
    emit status(tr("Rundowns received."));
}

void RundownCreator::handleRows(const QByteArray &data)
{
    m_rundownRowModel->clear();

    QJsonDocument rowsDocument = QJsonDocument::fromJson(data);

    QJsonArray array = rowsDocument.array();

    foreach(const QJsonValue &value, array)
    {
        QJsonObject object = value.toObject();
        quint32 rundownId = object.value("RundownID").toInt();
        quint32 rowId = object.value("RowID").toInt();

        foreach(const QJsonValue &objectValue, object.value("Objects").toArray())
        {
            QJsonObject objectObject = objectValue.toObject();
            QString type = objectObject.value("Type").toString();
            QJsonObject payloadObject = objectObject.value("Payload").toObject();
            RundownRow *row = new RundownRow(type);
            row->setRundownId(rundownId);
            row->setRowId(rowId);
            row->setPageNumber(object.value("PageNumber").toString());
            row->setStorySlug(object.value("StorySlug").toString());
            QVariantHash attrHash = payloadObject.toVariantHash();
            attrHash.insert("page", row->pageNumber());
            attrHash.insert("storyslug", row->storySlug());
            row->setAttributes(attrHash);
            m_rundownRowModel->appendRow(row);
        }
    }

    emit status(tr("Rows recieved."));
}

void RundownCreator::handleFolders(const QByteArray &data)
{
    qDeleteAll(m_folderHash);
    m_folderHash.clear();

    QJsonDocument rowsDocument = QJsonDocument::fromJson(data);
    QJsonArray array = rowsDocument.array();

    foreach(const QJsonValue &value, array)
    {
        QJsonObject object = value.toObject();
        Folder *folder = new Folder(object.value("FolderID").toInt());
        folder->setName(object.value("Name").toString());
        m_folderHash.insert(folder->id(), folder);
    }

    emit status(tr("Folders received."));
    getRundowns();
}
