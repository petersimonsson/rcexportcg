#include "casparcggenerator.h"
#include "rundownrow.h"
#include "rundownrowmodel.h"
#include "casparcgmetadata.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QXmlStreamWriter>
#include <QIODevice>

CasparCGGenerator::CasparCGGenerator(QObject *parent) : QObject(parent)
{

}

void CasparCGGenerator::convert(RundownRowModel *rowModel, QIODevice *output)
{
    QXmlStreamWriter writer;
    writer.setAutoFormatting(true);

    writer.setDevice(output);

    writer.writeStartDocument();
    writer.writeStartElement("items");
    writer.writeTextElement("allowremotetriggering", "false");

    foreach(RundownRow *row, rowModel->rowList())
    {
        CasparCGMetaData *metadata = m_metadata.value(row->type());

        if(metadata)
        {
            metadata->createItem(&writer, row->file(), row->file().toUpper());
        }
    }

    writer.writeEndElement();
    writer.writeEndDocument();
}
