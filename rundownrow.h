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
#ifndef RUNDOWNROW_H
#define RUNDOWNROW_H

#include <QString>
#include <QVariantHash>

class RundownRow
{
public:
    RundownRow(const QString &type);

    QString type() const { return m_type; }

    void setRundownId(quint32 id) { m_rundownId = id; }
    quint32 rundownId() const { return m_rundownId; }
    void setRowId(quint32 id) { m_rowId = id; }
    quint32 rowId() const { return m_rowId; }

    void setPageNumber(const QString &number) { m_pageNumber = number; }
    QString pageNumber() const { return m_pageNumber; }

    void setStorySlug(const QString &slug) { m_storySlug = slug; }
    QString storySlug () const { return m_storySlug; }

    void setAttributes(const QVariantHash &attributes) { m_attributes = attributes; }
    QVariantHash attributes() const { return m_attributes; }

private:
    QString m_type;

    quint32 m_rundownId;
    quint32 m_rowId;
    QString m_pageNumber;
    QString m_storySlug;

    QVariantHash m_attributes;
};

#endif // RUNDOWNROW_H
