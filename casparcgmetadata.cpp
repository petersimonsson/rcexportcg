#include "casparcgmetadata.h"

CasparCGMetaData::CasparCGMetaData() :
    m_channel(1), m_videoLayer(10), m_delay(0),
    m_duration(0), m_allowGpi(false), m_allowRemoteTriggering(false)
{
}

CasparCGMetaData::CasparCGMetaData(const CasparCGMetaData &other)
{
    m_serverName = other.m_serverName;
    m_channel = other.m_channel;
    m_videoLayer = other.m_videoLayer;
    m_delay = other.m_delay;
    m_duration = other.m_duration;
    m_allowGpi = other.m_allowGpi;
    m_allowRemoteTriggering = other.m_allowRemoteTriggering;
    m_remoteTriggerId = other.m_remoteTriggerId;
}

QString CasparCGMetaData::boolToString(bool state)
{
    if(state)
        return "true";

    return "false";
}
