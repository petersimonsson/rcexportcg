#include "casparcggenerator.h"
#include "rundownrow.h"
#include "rundownrowmodel.h"

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
    QHash<QString, QString> translationHash;
    translationHash.insert("video", "MOVIE");
    translationHash.insert("image", "STILL");

    QXmlStreamWriter writer;
    writer.setAutoFormatting(true);

    writer.setDevice(output);

    writer.writeStartDocument();
    writer.writeStartElement("items");
    writer.writeTextElement("allowremotetriggering", "false");

    foreach(RundownRow *row, rowModel->rowList())
    {
        writer.writeStartElement("item");
        writer.writeTextElement("type", translationHash.value(row->type()));
        writer.writeTextElement("devicename", m_deviceName);
        writer.writeTextElement("label", row->file());
        writer.writeTextElement("name", row->file().toUpper());
        writer.writeTextElement("channel", m_channel);
        writer.writeTextElement("videolayer", m_videoLayer);
        writer.writeTextElement("delay", m_delay);
        writer.writeTextElement("duration", m_duration);
        writer.writeTextElement("allowgpi", boolToString(m_allowGpi));
        writer.writeTextElement("allowremotetriggering", boolToString(m_allowRemoteTriggering));
        writer.writeTextElement("remotetriggerid", m_remoteTriggeringId);
        writer.writeTextElement("storyid", m_storyId);
        writer.writeTextElement("transition", m_transition);
        writer.writeTextElement("transitionDuration", m_transitionDuration);
        writer.writeTextElement("tween", m_tween);
        writer.writeTextElement("direction", m_direction);
        if(row->type() == "video")
        {
            writer.writeTextElement("seek", m_seek);
            writer.writeTextElement("length", m_length);
            writer.writeTextElement("loop", boolToString(m_loop));
            writer.writeTextElement("freezeonload", boolToString(m_freezeOnLoad));
            writer.writeTextElement("autoplay", boolToString(m_autoPlay));
        }
        else if(row->type() == "image")
        {
            writer.writeTextElement("useauto", boolToString(m_useAuto));
        }
        writer.writeTextElement("triggeronnext", boolToString(m_triggerOnNext));
        writer.writeTextElement("color", m_color);
        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.writeEndDocument();
}

QString CasparCGGenerator::boolToString(bool state)
{
    if(state)
        return QString("true");

    return QString("false");
}
