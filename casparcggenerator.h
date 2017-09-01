#ifndef CASPARCGGENERATOR_H
#define CASPARCGGENERATOR_H

#include <QObject>

class RundownRow;

class QIODevice;

class CasparCGGenerator : public QObject
{
    Q_OBJECT
public:
    explicit CasparCGGenerator(QObject *parent = nullptr);

    void setDevice (const QString &device) { m_deviceName = device; }

    void convert(const QList<RundownRow*> &rowList, QIODevice *output);

    void setChannel(const QString &channel) { m_channel = channel; }
    void setVideoLayer(const QString &layer) { m_videoLayer = layer; }
    void setDelay(const QString &delay) { m_delay = delay; }
    void setDuration(const QString &duration) { m_duration = duration; }
    void setAllowGpi(bool allow) { m_allowGpi = allow; }
    void setAllowRemoteTriggering(bool allow) { m_allowRemoteTriggering = allow; }
    void setRemoteTriggeringId(const QString &id) { m_remoteTriggeringId = id; }
    void setStoryId(const QString &id) { m_storyId = id; }
    void setTransition(const QString &transition) { m_transition = transition; }
    void setTransitionDuration(const QString &duration) { m_transitionDuration = duration; }
    void setTween(const QString &tween) { m_tween = tween; }
    void setDirection(const QString &direction) { m_direction = direction; }
    void setSeek(const QString &seek) { m_seek = seek; }
    void setLength(const QString &length) { m_length = length; }
    void setLoop(bool loop) { m_loop = loop; }
    void setFreezeOnLoad(bool freeze) { m_freezeOnLoad = freeze; }
    void setAutoPlay(bool aplay) { m_autoPlay = aplay; }
    void setUseAuto(bool useAuto) { m_useAuto = useAuto; }
    void setTriggerOnNext(bool trigger) { m_triggerOnNext = trigger; }
    void setColor(const QString &color) { m_color = color; }

protected:
    QString boolToString(bool state);

private:
    QString m_deviceName;

    QString m_channel;
    QString m_videoLayer;
    QString m_delay;
    QString m_duration;
    bool m_allowGpi;
    bool m_allowRemoteTriggering;
    QString m_remoteTriggeringId;
    QString m_storyId;
    QString m_transition;
    QString m_transitionDuration;
    QString m_tween;
    QString m_direction;
    QString m_seek;
    QString m_length;
    bool m_loop;
    bool m_freezeOnLoad;
    bool m_autoPlay;
    bool m_useAuto;
    bool m_triggerOnNext;
    QString m_color;
};

#endif // CASPARCGGENERATOR_H
