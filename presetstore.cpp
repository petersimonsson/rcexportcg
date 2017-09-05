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
#include "rundownrowmodel.h"
#include "rundownrow.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QIODevice>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>

PresetStore::PresetStore(QObject *parent) : QObject(parent)
{
    QSettings settings;
    settings.beginGroup("CasparCG/DefaultPresets");

    foreach(const QString &key, settings.childKeys())
    {
        m_defaultPresets.insert(key, settings.value(key).toString());
    }

    settings.endGroup();
}

PresetStore::~PresetStore()
{
    QSettings settings;
    settings.beginGroup("CasparCG/DefaultPresets");

    QHash<QString, QString>::iterator it = m_defaultPresets.begin();
    for(; it != m_defaultPresets.end(); ++it)
    {
        settings.setValue(it.key(), it.value());
    }

    settings.endGroup();

    clear();
}

void PresetStore::clear()
{
    qDeleteAll(m_presets);
    m_presets.clear();
}

void PresetStore::loadPresets()
{
    emit logMessage(tr("Loading presets from CasparCG Client database..."));
    clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + "/.CasparCG/Client/Database.s3db");

    if(!db.open())
    {
        emit logMessage(tr("Failed to open CasparCG Client database."));
        return;
    }

    QSqlQuery query("SELECT * FROM Preset");
    QStringList logList;

    while(query.next())
    {
        QString data = query.value(2).toString();
        //Remove <xml> and <items> elements
        data = data.mid(28, data.count() - 37);
        Preset *preset = new Preset(query.value(1).toString(), data);
        m_presets.insert(preset->name(), preset);
        logList.append(preset->name());
    }

    emit logMessage(tr("Found: %1").arg(logList.join(", ")));

    db.close();
}

QString PresetStore::createObject(const QString &presetName, const QVariantHash &attributes)
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
            QString replace = attributes.value(regexp.cap(1)).toString();

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

void PresetStore::generateCasparCG(RundownRowModel *rowModel, QIODevice *output)
{
    emit logMessage(tr("Generating CasparCG rundown..."));
    QXmlStreamWriter writer;
    writer.setAutoFormatting(true);

    writer.setDevice(output);

    writer.writeStartDocument();
    writer.writeStartElement("items");
    writer.writeTextElement("allowremotetriggering", "false");

    foreach(RundownRow *row, rowModel->rowList())
    {
        QString presetName = m_defaultPresets.value(row->type());

        if(!row->attributes().value("preset").toString().isEmpty())
            presetName = row->attributes().value("preset").toString();

        if(presetName.isEmpty())
        {
            QStringList attrString;
            QVariantHash attrHash = row->attributes();
            QVariantHash::iterator it = attrHash.begin();
            for(; it != attrHash.end(); ++it)
                attrString.append(tr("%1 = %2").arg(it.key(), it.value().toString()));
            emit logMessage(tr("Did not find a preset for %1 (%2)").arg(row->type(), attrString.join(", ")));
        }

        QString data = createObject(presetName, row->attributes());
        output->write(data.toUtf8());
    }

    writer.writeEndElement();
    writer.writeEndDocument();
    emit logMessage(tr("Done."));
}
