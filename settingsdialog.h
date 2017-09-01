#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    void setRundownCreatorUrl(const QString &url);
    QString rundownCreatorUrl() const;
    void setRundownCreatorApiKey(const QString &key);
    QString rundownCreatorApiKey() const;
    void setRundownCreatorApiToken(const QString &token);
    QString rundownCreatorApiToken() const;

    void setCasparCGServerName(const QString &name);
    QString casparCGServerName() const;
    void setCasparCGRundownLocation(const QString &location);
    QString casparCGRundownLocation() const;

    void setCasparCGChannel(const QString &channel);
    QString casparCGChannel() const;
    void setCasparCGVideoLayer(const QString &layer);
    QString casparCGVideoLayer() const;
    void setCasparCGDelay(const QString &delay);
    QString casparCGDelay() const;
    void setCasparCGDuration(const QString &duration);
    QString casparCGDuration() const;
    void setCasparCGAllowGpi(bool allow);
    bool casparCGAllowGpi() const;
    void setCasparCGAllowRemoteTriggering(bool allow);
    bool casparCGAllowRemoteTriggering() const;
    void setCasparCGRemoteTriggerId(const QString &id);
    QString casparCGRemoteTriggerId() const;
    void setCasparCGStoryId(const QString &id);
    QString casparCGStoryId() const;
    void setCasparCGTransition(const QString &transition);
    QString casparCGTransition() const;
    void setCasparCGTransitionDuration(const QString &duration);
    QString casparCGTransitionDuration() const;
    void setCasparCGTween(const QString &tween);
    QString casparCGTween() const;
    void setCasparCGDirection(const QString &direction);
    QString casparCGDirection() const;
    void setCasparCGSeek(const QString &seek);
    QString casparCGSeek() const;
    void setCasparCGLength(const QString &length);
    QString casparCGLength() const;
    void setCasparCGLoop(bool loop);
    bool casparCGLoop() const;
    void setCasparCGFreezeOnLoad(bool freeze);
    bool casparCGFreezeOnLoad() const;
    void setCasparCGAutoPlay(bool aplay);
    bool casparCGAutoPlay() const;
    void setCasparCGUseAuto(bool useAuto);
    bool casparCGUseAuto() const;
    void setCasparCGTriggerOnNext(bool trigger);
    bool casparCGTriggerOnNext() const;
    void setCasparCGColor(const QString &color);
    QString casparCGColor() const;

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
