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
#include "presetstore.h"
#include "preset.h"

#include <QDir>
#include <QFile>
#include <QDebug>

PresetStore::PresetStore(QObject *parent) : QObject(parent)
{
}

PresetStore::~PresetStore()
{
    clear();
}

void PresetStore::clear()
{
    qDeleteAll(m_presets);
    m_presets.clear();
}

void PresetStore::loadPresets()
{
    clear();

    QDir presetDir(QDir::homePath() + "/.rcexportcg/presets");
    presetDir.setNameFilters(QStringList() << "*.xml");

    if(!presetDir.exists())
        return;

    foreach(const QString &filename, presetDir.entryList())
    {
        QFile file(presetDir.absoluteFilePath(filename));

        if(file.open(QFile::ReadOnly))
        {
            QString data;
            data = QString::fromUtf8(file.readAll());
            //Remove <xml> and <items> elements
            data = data.mid(28, data.count() - 37);
            Preset *preset = new Preset(filename.left(filename.count() - 4), data);
            m_presets.insert(preset->name(), preset);
        }
    }
}

QString PresetStore::createObject(const QString &presetName, const QHash<QString, QString> &attributes)
{
    Preset *preset = m_presets.value(presetName);
    QString data;

    if(preset)
    {
        data = preset->data();

        QRegExp regexp("\\$([^\\$]*)\\$");
        int offset = 0;

        while((offset = regexp.indexIn(data, offset)) != -1)
        {
            QString replace = attributes.value(regexp.cap(1));

            if(!replace.isEmpty())
            {
                data = data.replace(offset, regexp.matchedLength(), replace);
                offset += replace.count();
            }
            else
            {
                offset += regexp.matchedLength();
            }
        }
    }

    return data;
}
