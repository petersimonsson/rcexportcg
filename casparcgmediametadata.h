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
#ifndef CASPARCGMEDIAMETADATA_H
#define CASPARCGMEDIAMETADATA_H

#include "casparcgmetadata.h"

class CasparCGMediaMetaData : public CasparCGMetaData
{
public:
    CasparCGMediaMetaData();
    CasparCGMediaMetaData(const CasparCGMediaMetaData &other);

    void setTransition(const QString &transiton) { m_transition = transiton; }
    QString transition() const { return m_transition; }
    void setTransitionDuration(quint32 duration) { m_transitionDuration = duration; }
    quint32 transitionDuration() const { return m_transitionDuration; }
    void setTween(const QString &tween) { m_tween = tween; }
    QString tween() const { return m_tween; }
    void setDirection(const QString &direction) { m_direction = direction; }
    QString direction() const { return m_direction; }
    void setTriggerOnNext(bool trigger) { m_triggerOnNext = trigger; }
    bool triggerOnNext() const { return m_triggerOnNext; }

private:
    QString m_transition;
    quint32 m_transitionDuration;
    QString m_tween;
    QString m_direction;
    bool m_triggerOnNext;
};

#endif // CASPARCGMEDIAMETADATA_H
