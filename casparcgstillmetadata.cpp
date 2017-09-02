#include "casparcgstillmetadata.h"

#include <QXmlStreamWriter>
#include <QSettings>
#include <QDebug>

CasparCGStillMetaData::CasparCGStillMetaData() :
    CasparCGMediaMetaData(), m_useAuto(false)
{
}

CasparCGStillMetaData::CasparCGStillMetaData(const CasparCGStillMetaData &other) :
    CasparCGMediaMetaData(other)
{
    m_useAuto = other.m_useAuto;
}

void CasparCGStillMetaData::createItem(QXmlStreamWriter *writer, const QString &label, const QString &name) const
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
    writer->writeTextElement("useauto", CasparCGMetaData::boolToString(useAuto()));
    writer->writeTextElement("triggeronnext", CasparCGMetaData::boolToString(triggerOnNext()));
    writer->writeTextElement("color", "Transparent");
    writer->writeEndElement();
}

void CasparCGStillMetaData::readSettings()
{
    QSettings settings;
    settings.beginGroup("CasparCG/Still");
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
    setUseAuto(settings.value("UseAuto", false).toBool());
    settings.endGroup();
}

void CasparCGStillMetaData::writeSettings() const
{
    QSettings settings;
    settings.beginGroup("CasparCG/Still");
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
    settings.setValue("TriggerOnNext", triggerOnNext());
    settings.setValue("UseAuto", useAuto());
    settings.endGroup();
}
