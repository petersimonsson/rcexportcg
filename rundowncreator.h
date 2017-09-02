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

    void getRundowns();
    void fetchRows(quint32 rundownId);

    QList<Rundown*> rundownList() const { return m_rundownList; }
    RundownRowModel *rundownRowModel() const { return m_rundownRowModel; }

private slots:
    void handleFinished(QNetworkReply *reply);
    void handleRundowns(const QByteArray &data);
    void handleRows(const QByteArray &data);

private:
    QUrlQuery createRequestQuery(const QString &action, const QList<QPair<QString, QString> > &extraItems = QList<QPair<QString, QString> >()) const;

    QUrl m_apiUrl;
    QString m_apiKey;
    QString m_apiToken;

    QNetworkAccessManager *m_netManager;

    QList<Rundown*> m_rundownList;
    RundownRowModel *m_rundownRowModel;

signals:
    void rundownsReceived();

    void error(const QString &errorString);
    void status(const QString &statusString);
};

#endif // RUNDOWNCREATORFETCHER_H
