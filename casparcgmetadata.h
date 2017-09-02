#ifndef CASPARCGMETADATA_H
#define CASPARCGMETADATA_H

#include <QString>

class QXmlStreamWriter;

class CasparCGMetaData
{
public:
    CasparCGMetaData();
    CasparCGMetaData(const CasparCGMetaData &other);

    virtual QString type() const = 0;

    void setServerName(const QString &name) { m_serverName = name; }
    QString serverName() const { return m_serverName; }
    void setChannel(quint32 channel) { m_channel = channel; }
    quint32 channel() const { return m_channel; }
    void setVideoLayer(quint32 layer) { m_videoLayer = layer; }
    quint32 videoLayer() const { return m_videoLayer; }
    void setDelay(quint32 delay) { m_delay = delay; }
    quint32 delay() const { return m_delay; }
    void setDuration(quint32 duration) { m_duration = duration; }
    quint32 duration() const { return m_duration; }
    void setAllowGpi(bool allow) { m_allowGpi = allow; }
    bool allowGpi() const { return m_allowGpi; }
    void setAllowRemoteTriggering(bool allow) { m_allowRemoteTriggering = allow; }
    bool allowRemoteTriggering() const { return m_allowRemoteTriggering; }
    void setRemoteTriggerId(const QString &id) { m_remoteTriggerId = id; }
    QString remoteTriggerId() const { return m_remoteTriggerId; }

    virtual void createItem(QXmlStreamWriter *writer, const QString &label, const QString &name) const = 0;

    static QString boolToString(bool state);

    virtual void readSettings() = 0;
    virtual void writeSettings() const = 0;

private:
    QString m_serverName;
    quint32 m_channel;
    quint32 m_videoLayer;
    quint32 m_delay;
    quint32 m_duration;
    bool m_allowGpi;
    bool m_allowRemoteTriggering;
    QString m_remoteTriggerId;
};

#endif // CASPARCGMETADATA_H
