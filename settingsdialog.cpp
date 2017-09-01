#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setRundownCreatorUrl(const QString &url)
{
    ui->rcUrlEdit->setText(url);
}

QString SettingsDialog::rundownCreatorUrl() const
{
    return ui->rcUrlEdit->text();
}

void SettingsDialog::setRundownCreatorApiKey(const QString &key)
{
    ui->rcApiKeyEdit->setText(key);
}

QString SettingsDialog::rundownCreatorApiKey() const
{
    return ui->rcApiKeyEdit->text();
}

void SettingsDialog::setRundownCreatorApiToken(const QString &token)
{
    ui->rcApiTokenEdit->setText(token);
}

QString SettingsDialog::rundownCreatorApiToken() const
{
    return ui->rcApiTokenEdit->text();
}

void SettingsDialog::setCasparCGServerName(const QString &name)
{
    ui->ccgServerNameEdit->setText(name);
}

QString SettingsDialog::casparCGServerName() const
{
    return ui->ccgServerNameEdit->text();
}

void SettingsDialog::setCasparCGRundownLocation(const QString &location)
{
    ui->ccgRundownLocationEdit->setText(location);
}

QString SettingsDialog::casparCGRundownLocation() const
{
    return ui->ccgRundownLocationEdit->text();
}

void SettingsDialog::setCasparCGChannel(const QString &channel)
{
    ui->channelEdit->setText(channel);
}

QString SettingsDialog::casparCGChannel() const
{
    return ui->channelEdit->text();
}

void SettingsDialog::setCasparCGVideoLayer(const QString &layer)
{
    ui->videoLayerEdit->setText(layer);
}

QString SettingsDialog::casparCGVideoLayer() const
{
    return ui->videoLayerEdit->text();
}

void SettingsDialog::setCasparCGDelay(const QString &delay)
{
    ui->delayEdit->setText(delay);
}

QString SettingsDialog::casparCGDelay() const
{
    return ui->delayEdit->text();
}

void SettingsDialog::setCasparCGDuration(const QString &duration)
{
    ui->durationEdit->setText(duration);
}

QString SettingsDialog::casparCGDuration() const
{
    return ui->durationEdit->text();
}

void SettingsDialog::setCasparCGAllowGpi(bool allow)
{
    ui->allowGpiCheck->setChecked(allow);
}

bool SettingsDialog::casparCGAllowGpi() const
{
    return ui->allowGpiCheck->isChecked();
}

void SettingsDialog::setCasparCGAllowRemoteTriggering(bool allow)
{
    ui->remotetriggeringCheck->setChecked(allow);
}

bool SettingsDialog::casparCGAllowRemoteTriggering() const
{
    return ui->remotetriggeringCheck->isChecked();
}

void SettingsDialog::setCasparCGRemoteTriggerId(const QString &id)
{
    ui->remoteTriggeringId->setText(id);
}

QString SettingsDialog::casparCGRemoteTriggerId() const
{
    return ui->remoteTriggeringId->text();
}

void SettingsDialog::setCasparCGStoryId(const QString &id)
{
    ui->storyIdEdit->setText(id);
}

QString SettingsDialog::casparCGStoryId() const
{
    return ui->storyIdEdit->text();
}

void SettingsDialog::setCasparCGTransition(const QString &transition)
{
    ui->transitionCombo->setCurrentText(transition);
}

QString SettingsDialog::casparCGTransition() const
{
    return ui->transitionCombo->currentText();
}

void SettingsDialog::setCasparCGTransitionDuration(const QString &duration)
{
    ui->transitionDurationEdit->setText(duration);
}

QString SettingsDialog::casparCGTransitionDuration() const
{
    return ui->transitionDurationEdit->text();
}

void SettingsDialog::setCasparCGTween(const QString &tween)
{
    ui->tweenEdit->setText(tween);
}

QString SettingsDialog::casparCGTween() const
{
    return ui->tweenEdit->text();
}

void SettingsDialog::setCasparCGDirection(const QString &direction)
{
    ui->directionCombo->setCurrentText(direction);
}

QString SettingsDialog::casparCGDirection() const
{
    return ui->directionCombo->currentText();
}

void SettingsDialog::setCasparCGSeek(const QString &seek)
{
    ui->seekEdit->setText(seek);
}

QString SettingsDialog::casparCGSeek() const
{
    return ui->seekEdit->text();
}

void SettingsDialog::setCasparCGLength(const QString &length)
{
    ui->lengthEdit->setText(length);
}

QString SettingsDialog::casparCGLength() const
{
    return ui->lengthEdit->text();
}

void SettingsDialog::setCasparCGLoop(bool loop)
{
    ui->loopCheck->setChecked(loop);
}

bool SettingsDialog::casparCGLoop() const
{
    return ui->loopCheck->isChecked();
}

void SettingsDialog::setCasparCGFreezeOnLoad(bool freeze)
{
    ui->freezeOnLoadCheck->setChecked(freeze);
}

bool SettingsDialog::casparCGFreezeOnLoad() const
{
    return ui->freezeOnLoadCheck->isChecked();
}

void SettingsDialog::setCasparCGAutoPlay(bool aplay)
{
    ui->autoPlayCheck->setChecked(aplay);
}

bool SettingsDialog::casparCGAutoPlay() const
{
    return ui->autoPlayCheck->isChecked();
}

void SettingsDialog::setCasparCGUseAuto(bool useAuto)
{
    ui->useAutoCheck->setChecked(useAuto);
}

bool SettingsDialog::casparCGUseAuto() const
{
    return ui->useAutoCheck->isChecked();
}

void SettingsDialog::setCasparCGTriggerOnNext(bool trigger)
{
    ui->triggerOnNextCheck->setChecked(trigger);
}

bool SettingsDialog::casparCGTriggerOnNext() const
{
    return ui->triggerOnNextCheck->isChecked();
}

void SettingsDialog::setCasparCGColor(const QString &color)
{
    ui->colorEdit->setText(color);
}

QString SettingsDialog::casparCGColor() const
{
    return ui->colorEdit->text();
}
