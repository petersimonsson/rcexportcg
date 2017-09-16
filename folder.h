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
#ifndef FOLDER_H
#define FOLDER_H

#include <QString>
#include <QList>

class Rundown;

class Folder
{
public:
    Folder(quint32 id);
    ~Folder();

    quint32 id() const { return m_id; }

    void setName(const QString &name) { m_name = name; }
    QString name() const { return m_name; }

    void appendRundown(Rundown *rundown);
    QList<Rundown*> rundownList() const { return m_rundownList; }

private:
    quint32 m_id;
    QString m_name;

    QList<Rundown*> m_rundownList;
};

#endif // FOLDER_H
