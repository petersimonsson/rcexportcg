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
