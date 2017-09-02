#include "rundowncreator.h"
#include "rundown.h"
#include "rundownrow.h"
#include "rundownrowmodel.h"

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
    qDeleteAll(m_rundownList);
    m_rundownList.clear();
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
        else
            qDebug() << data;
        break;
    case 400:
        emit error(tr("Bad request: %1").arg(QString::fromUtf8(data)));
        break;
    case 401:
        emit error(tr("Authentication failed!"));
        break;
    case 500:
        emit error(tr("Internal server error."));
        break;
    default:
        qDebug() << "Status:" << statusCode << "Data:" << data;
        break;
    }

    reply->deleteLater();
    emit status(tr("Ready."));
}

void RundownCreator::handleRundowns(const QByteArray &data)
{
    // Remove old list
    qDeleteAll(m_rundownList);
    m_rundownList.clear();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonArray array = doc.array();

    foreach(const QJsonValue &value, array)
    {
        QJsonObject object = value.toObject();
        Rundown *rundown = new Rundown(object.value("RundownID").toInt(),
                                       object.value("Title").toString());
        rundown->setFrozen(object.value("Frozen").toInt());
        rundown->setLocked(object.value("Locked").toInt());
        rundown->setArchived(object.value("Archived").toInt());
        rundown->setTemplate(object.value("Template").toInt());
        rundown->setDeleted(object.value("Deleted").toInt());
        m_rundownList.append(rundown);
    }

    emit rundownsReceived();
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
            QString file = payloadObject.value("file").toString();

            if(!file.isEmpty() && (type == "video" || type == "image"))
            {
                RundownRow *row = new RundownRow(type, file);
                row->setRundownId(rundownId);
                row->setRowId(rowId);
                row->setPageNumber(object.value("PageNumber").toString());
                row->setStorySlug(object.value("StorySlug").toString());
                m_rundownRowModel->appendRow(row);
            }
        }
    }
}
