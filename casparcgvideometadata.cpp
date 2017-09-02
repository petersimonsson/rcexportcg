#include "casparcgvideometadata.h"

#include <QXmlStreamWriter>
#include <QSettings>

CasparCGVideoMetaData::CasparCGVideoMetaData() :
    CasparCGMediaMetaData(), m_seek(0), m_length(0),
    m_loop(false), m_freezeOnLoad(false), m_autoPlay(false)
{
}

CasparCGVideoMetaData::CasparCGVideoMetaData(const CasparCGVideoMetaData &other) :
    CasparCGMediaMetaData(other)
{
    m_seek = other.m_seek;
    m_length = other.m_length;
    m_loop = other.m_loop;
    m_freezeOnLoad = other.m_freezeOnLoad;
    m_autoPlay = other.m_autoPlay;
}

void CasparCGVideoMetaData::createItem(QXmlStreamWriter *writer, const QString &label, const QString &name) const
{
    writer->writeStartElement("item");
    writer->writeTextElement("type", type());
    writer->writeTextElement("devicename", serverName());
    writer->writeTextElement("label", label);
    writer->writeTextElement("name", name);
    writer->writeTextElement("channel", QString::number(channel()));
    writer->writeTextElement("videolayer", QString::number(videoLayer()));
    writer->writeTextElement("delay", QString::number(delay()));
    writer->writeTextElement("duration", QString::number(duration()));
    writer->writeTextElement("allowgpi", CasparCGMetaData::boolToString(allowGpi()));
    writer->writeTextElement("allowremotetriggering", CasparCGMetaData::boolToString(allowRemoteTriggering()));
    writer->writeTextElement("remotetriggerid", remoteTriggerId());
    writer->writeTextElement("storyid", "");
    writer->writeTextElement("transition", transition());
    writer->writeTextElement("transitionDuration", QString::number(transitionDuration()));
    writer->writeTextElement("tween", tween());
    writer->writeTextElement("direction", direction());
    writer->writeTextElement("seek", QString::number(seek()));
    writer->writeTextElement("length", QString::number(length()));
    writer->writeTextElement("loop", CasparCGMetaData::boolToString(loop()));
    writer->writeTextElement("freezeonload", CasparCGMetaData::boolToString(freezeOnLoad()));
    writer->writeTextElement("autoplay", CasparCGMetaData::boolToString(autoPlay()));
    writer->writeTextElement("triggeronnext", CasparCGMetaData::boolToString(triggerOnNext()));
    writer->writeTextElement("color", "Transparent");
    writer->writeEndElement();
}

void CasparCGVideoMetaData::readSettings()
{
    QSettings settings;
    settings.beginGroup("CasparCG/Video");
    setServerName(settings.value("ServerName").toString());
    setChannel(settings.value("Channel", 1).toUInt());
    setDelay(settings.value("Delay", 0).toUInt());
    setDuration(settings.value("Duration",0 ).toUInt());
    setAllowGpi(settings.value("AllowGPI", false).toBool());
    setAllowRemoteTriggering(settings.value("AllowRemoteTriggering", false).toBool());
    setRemoteTriggerId(settings.value("RemoteTriggerID").toString());
    setTransition(settings.value("Transition", "CUT").toString());
    setTransitionDuration(settings.value("TransitionDuration", 1).toUInt());
    setTween(settings.value("Tween", "Linear").toString());
    setDirection(settings.value("Direction", "RIGHT").toString());
    setTriggerOnNext(settings.value("TriggerOnNext", false).toBool());
    setSeek(settings.value("Seek", 0).toUInt());
    setLength(settings.value("Length", 0).toUInt());
    setLoop(settings.value("Loop", false).toBool());
    setFreezeOnLoad(settings.value("FreezeOnLoad", false).toBool());
    setAutoPlay(settings.value("AutoPlay", false).toBool());
    settings.endGroup();
}

void CasparCGVideoMetaData::writeSettings() const
{
    QSettings settings;
    settings.beginGroup("CasparCG/Video");
    settings.setValue("ServerName", serverName());
    settings.setValue("Channel", channel());
    settings.setValue("VideoLayer", videoLayer());
    settings.setValue("Delay", delay());
    settings.setValue("Duration", duration());
    settings.setValue("AllowGPI", allowGpi());
    settings.setValue("AllowRemoteTriggering", allowRemoteTriggering());
    settings.setValue("RemoteTriggerID", remoteTriggerId());
    settings.setValue("Transition", transition());
    settings.setValue("TransitionDuration", transitionDuration());
    settings.setValue("Tween", tween());
    settings.setValue("Direction", direction());
    settings.setValue("Seek", seek());
    settings.setValue("Length", length());
    settings.setValue("Loop", loop());
    settings.setValue("FreezeOnLoad", freezeOnLoad());
    settings.setValue("AutoPlay", autoPlay());
    settings.endGroup();
}
