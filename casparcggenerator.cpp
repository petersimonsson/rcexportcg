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
#include "casparcggenerator.h"
#include "rundownrow.h"
#include "rundownrowmodel.h"
#include "casparcgmetadata.h"
#include "presetstore.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QXmlStreamWriter>
#include <QIODevice>

CasparCGGenerator::CasparCGGenerator(QObject *parent) : QObject(parent)
{

}

void CasparCGGenerator::convert(RundownRowModel *rowModel, QIODevice *output, PresetStore *presetStore)
{
    QXmlStreamWriter writer;
    writer.setAutoFormatting(true);

    writer.setDevice(output);

    writer.writeStartDocument();
    writer.writeStartElement("items");
    writer.writeTextElement("allowremotetriggering", "false");

    foreach(RundownRow *row, rowModel->rowList())
    {
        QString presetName;

        if(row->type() == "video")
            presetName = "Video";
        else
            presetName = "Still";

        QString data = presetStore->createObject(presetName, row->attributes());
        output->write(data.toUtf8());
    }

    writer.writeEndElement();
    writer.writeEndDocument();
}
