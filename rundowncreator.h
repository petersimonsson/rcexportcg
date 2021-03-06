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
#ifndef RUNDOWNCREATORFETCHER_H
#define RUNDOWNCREATORFETCHER_H

#include <QObject>
#include <QUrl>
#include <QList>
#include <QJsonDocument>

class QNetworkAccessManager;
class QNetworkReply;

class Rundown;
class RundownRowModel;
class Folder;

class RundownCreator : public QObject
{
    Q_OBJECT
public:
    explicit RundownCreator(QObject *parent = nullptr);
    ~RundownCreator();

    void setApiUrl(const QUrl &url) { m_apiUrl = url; }
    QUrl apiUrl() const { return m_apiUrl; }
    void setApiKey(const QString &key) { m_apiKey = key; }
    void setApiToken(const QString &token) { m_apiToken = token; }

    RundownRowModel *rundownRowModel() const { return m_rundownRowModel; }
    QHash<quint32, Folder*> folderHash() const { return m_folderHash; }

public slots:
    void getFoldersAndRundows();
    void fetchRows(quint32 rundownId);

private slots:
    void handleFinished(QNetworkReply *reply);
    void handleRundowns(const QByteArray &data);
    void handleRows(const QByteArray &data);
    void handleFolders(const QByteArray &data);

private:
    typedef QPair<QString, QString> QueryItem;
    QUrlQuery createRequestQuery(const QString &action, const QList<QueryItem> &extraItems = QList<QueryItem>()) const;
    void getRundowns();

    QUrl m_apiUrl;
    QString m_apiKey;
    QString m_apiToken;

    QNetworkAccessManager *m_netManager;

    QHash<quint32, Folder*> m_folderHash;
    RundownRowModel *m_rundownRowModel;

signals:
    void rundownsReceived();
    void rundownRowsReceived();

    void error(const QString &errorString);
    void status(const QString &statusString);
    void debug(const QString &message);
};

#endif // RUNDOWNCREATORFETCHER_H
