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
#ifndef RUNDOWN_H
#define RUNDOWN_H

#include <QString>

class Rundown
{
public:
    Rundown(quint32 id, const QString &title);

    quint32 id() const { return m_id; }
    QString title() const { return m_title; }

    void setFrozen(bool state) { m_frozen = state; }
    bool isFrozen() const { return m_frozen; }
    void setLocked(bool state) { m_locked = state; }
    bool isLocked() const { return m_locked; }
    void setArchived(bool state) { m_archived = state; }
    bool isArchived() const { return m_archived; }
    void setTemplate(bool state) { m_template = state; }
    bool isTemplate() const { return m_template; }
    void setDeleted(bool state) { m_deleted = state; }
    bool isDeleted () const { return m_deleted; }

private:
    quint32 m_id;
    QString m_title;

    bool m_frozen;
    bool m_locked;
    bool m_archived;
    bool m_template;
    bool m_deleted;
};

#endif // RUNDOWN_H
