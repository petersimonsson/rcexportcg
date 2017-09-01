#ifndef RUNDOWNCREATORFETCHER_H
#define RUNDOWNCREATORFETCHER_H

#include <QObject>
#include <QUrl>
#include <QList>
#include <QJsonDocument>

class QNetworkAccessManager;
class QNetworkReply;

class Rundown;
class RundownRow;

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
    QList<RundownRow*> rowList() const { return m_rowList; }

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
    QList<RundownRow*> m_rowList;

signals:
    void rundownsReceived();
    void rowsReceived();

    void error(const QString &errorString);
    void status(const QString &statusString);
};

#endif // RUNDOWNCREATORFETCHER_H
