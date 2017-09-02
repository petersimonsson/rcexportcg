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
