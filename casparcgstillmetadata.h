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
#ifndef CASPARCGSTILLMETADATA_H
#define CASPARCGSTILLMETADATA_H

#include "casparcgmediametadata.h"

class CasparCGStillMetaData : public CasparCGMediaMetaData
{
public:
    CasparCGStillMetaData();
    CasparCGStillMetaData(const CasparCGStillMetaData &other);

    virtual QString type() const override { return "STILL"; }

    void setUseAuto(bool use) { m_useAuto = use; }
    bool useAuto() const { return m_useAuto; }

    virtual void createItem(QXmlStreamWriter *writer, const QString &label, const QString &name) const override;

    virtual void readSettings() override;
    virtual void writeSettings() const override;

private:
    bool m_useAuto;
};

#endif // CASPARCGSTILLMETADATA_H
