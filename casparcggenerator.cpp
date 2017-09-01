#include "casparcggenerator.h"
#include "rundownrow.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QXmlStreamWriter>
#include <QIODevice>

CasparCGGenerator::CasparCGGenerator(QObject *parent) : QObject(parent)
{

}

void CasparCGGenerator::convert(const QList<RundownRow*> &rowList, QIODevice *output)
{
    QHash<QString, QString> translationHash;
    translationHash.insert("video", "MOVIE");
    translationHash.insert("image", "STILL");

    QXmlStreamWriter writer;
    writer.setAutoFormatting(true);

    writer.setDevice(output);

    writer.writeStartDocument();
    writer.writeStartElement("items");
    writer.writeTextElement("allowremotetriggering", "false");

    foreach(RundownRow *row, rowList)
    {
        foreach(const RundownRow::Object &object, row->objects())
        {
            if(!object.file.isEmpty() && (object.type == "video" || object.type == "image"))
            {
                writer.writeStartElement("item");
                writer.writeTextElement("type", translationHash.value(object.type));
                writer.writeTextElement("devicename", m_deviceName);
                writer.writeTextElement("label", object.file);
                writer.writeTextElement("name", object.file);
                writer.writeTextElement("channel", "1");
                writer.writeTextElement("videolayer", "10");
                writer.writeTextElement("delay", "0");
                writer.writeTextElement("duration", "0");
                writer.writeTextElement("allowgpi", "false");
                writer.writeTextElement("allowremotetriggering", "false");
                writer.writeTextElement("remotetriggerid", "");
                writer.writeTextElement("storyid", "");
                writer.writeTextElement("transition", "CUT");
                writer.writeTextElement("transitionDuration", "1");
                writer.writeTextElement("tween", "Linear");
                writer.writeTextElement("direction", "RIGHT");
                if(object.type == "video")
                {
                    writer.writeTextElement("seek", "0");
                    writer.writeTextElement("length", "0");
                    writer.writeTextElement("loop", "false");
                    writer.writeTextElement("freezeonload", "false");
                    writer.writeTextElement("autoplay", "false");
                }
                else if(object.type == "image")
                {
                    writer.writeTextElement("useauto", "false");
                }
                writer.writeTextElement("triggeronnext", "false");
                writer.writeTextElement("color", "Transparent");
                writer.writeEndElement();
            }
        }
    }

    writer.writeEndElement();
    writer.writeEndDocument();
}
