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
#ifndef CASPARCGVIDEOMETADATA_H
#define CASPARCGVIDEOMETADATA_H

#include "casparcgmediametadata.h"

class CasparCGVideoMetaData : public CasparCGMediaMetaData
{
public:
    CasparCGVideoMetaData();
    CasparCGVideoMetaData(const CasparCGVideoMetaData &other);

    virtual QString type() const override { return "MOVIE"; }

    void setSeek(quint32 frames) { m_seek = frames; }
    quint32 seek() const { return m_seek; }
    void setLength(quint32 frames) { m_length = frames; }
    quint32 length() const { return m_length; }
    void setLoop(bool loop) { m_loop = loop; }
    bool loop() const { return m_loop; }
    void setFreezeOnLoad(bool freeze) { m_freezeOnLoad = freeze; }
    bool freezeOnLoad() const { return m_freezeOnLoad; }
    void setAutoPlay(bool autoPlay) { m_autoPlay = autoPlay; }
    bool autoPlay() const { return m_autoPlay; }

    virtual void createItem(QXmlStreamWriter *writer, const QString &label, const QString &name) const override;

    virtual void readSettings() override;
    virtual void writeSettings() const override;

private:
    quint32 m_seek;
    quint32 m_length;
    bool m_loop;
    bool m_freezeOnLoad;
    bool m_autoPlay;
};

#endif // CASPARCGVIDEOMETADATA_H
