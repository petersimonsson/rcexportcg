#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "casparcgvideometadata.h"
#include "casparcgstillmetadata.h"

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

void SettingsDialog::setCasparCGRundownLocation(const QString &location)
{
    ui->ccgRundownLocationEdit->setText(location);
}

QString SettingsDialog::casparCGRundownLocation() const
{
    return ui->ccgRundownLocationEdit->text();
}

void SettingsDialog::setCasparCGVideoMetadata(const CasparCGVideoMetaData &metadata)
{
    ui->videoServerNameEdit->setText(metadata.serverName());
    ui->videoChannelSpin->setValue(metadata.channel());
    ui->videoVideoLayerSpin->setValue(metadata.videoLayer());
    ui->videoDelaySpin->setValue(metadata.delay());
    ui->videoDurationSpin->setValue(metadata.duration());
    ui->videoAllowGpiCheck->setChecked(metadata.allowGpi());
    ui->videoAllowRemotetriggeringCheck->setChecked(metadata.allowRemoteTriggering());
    ui->videoRemoteTriggerIdEdit->setText(metadata.remoteTriggerId());
    ui->videoTransitionCombo->setCurrentText(metadata.transition());
    ui->videoTransitionDurationSpin->setValue(metadata.transitionDuration());
    ui->videoTweenEdit->setText(metadata.tween());
    ui->videoDirectionCombo->setCurrentText(metadata.direction());
    ui->videoTriggerOnNextCheck->setChecked(metadata.triggerOnNext());
    ui->videoSeekSpin->setValue(metadata.seek());
    ui->videoLengthSpin->setValue(metadata.length());
    ui->videoLoopCheck->setChecked(metadata.loop());
    ui->videoFreezeOnLoadCheck->setChecked(metadata.freezeOnLoad());
    ui->videoAutoPlayCheck->setChecked(metadata.autoPlay());
}

CasparCGVideoMetaData SettingsDialog::casparCGVideoMetadata() const
{
    CasparCGVideoMetaData metadata;

    metadata.setServerName(ui->videoServerNameEdit->text());
    metadata.setChannel(ui->videoChannelSpin->value());
    metadata.setVideoLayer(ui->videoVideoLayerSpin->value());
    metadata.setDelay(ui->videoDelaySpin->value());
    metadata.setDuration(ui->videoDurationSpin->value());
    metadata.setAllowGpi(ui->videoAllowGpiCheck->isChecked());
    metadata.setAllowRemoteTriggering(ui->videoAllowRemotetriggeringCheck->isChecked());
    metadata.setRemoteTriggerId(ui->videoRemoteTriggerIdEdit->text());
    metadata.setTransition(ui->videoTransitionCombo->currentText());
    metadata.setTransitionDuration(ui->videoTransitionDurationSpin->value());
    metadata.setTween(ui->videoTweenEdit->text());
    metadata.setDirection(ui->videoDirectionCombo->currentText());
    metadata.setTriggerOnNext(ui->videoTriggerOnNextCheck->isChecked());
    metadata.setSeek(ui->videoSeekSpin->value());
    metadata.setLength(ui->videoLengthSpin->value());
    metadata.setLoop(ui->videoLoopCheck->isChecked());
    metadata.setFreezeOnLoad(ui->videoFreezeOnLoadCheck->isChecked());
    metadata.setAutoPlay(ui->videoAutoPlayCheck->isChecked());

    return metadata;
}

void SettingsDialog::setCasparCGStillMetadata(const CasparCGStillMetaData &metadata)
{
    ui->imageServerNameEdit->setText(metadata.serverName());
    ui->imageChannelSpin->setValue(metadata.channel());
    ui->imageVideoLayerSpin->setValue(metadata.videoLayer());
    ui->imageDelaySpin->setValue(metadata.delay());
    ui->imageDurationSpin->setValue(metadata.duration());
    ui->imageAllowGpiCheck->setChecked(metadata.allowGpi());
    ui->imageAllowRemotetriggeringCheck->setChecked(metadata.allowRemoteTriggering());
    ui->imageRemoteTriggerIdEdit->setText(metadata.remoteTriggerId());
    ui->imageTransitionCombo->setCurrentText(metadata.transition());
    ui->imageTransitionDurationSpin->setValue(metadata.transitionDuration());
    ui->imageTweenEdit->setText(metadata.tween());
    ui->imageDirectionCombo->setCurrentText(metadata.direction());
    ui->imageTriggerOnNextCheck->setChecked(metadata.triggerOnNext());
    ui->imageUseAutoCheck->setChecked(metadata.useAuto());
}

CasparCGStillMetaData SettingsDialog::casparCGStillMetadata() const
{
    CasparCGStillMetaData metadata;

    metadata.setServerName(ui->imageServerNameEdit->text());
    metadata.setChannel(ui->imageChannelSpin->value());
    metadata.setVideoLayer(ui->imageVideoLayerSpin->value());
    metadata.setDelay(ui->imageDelaySpin->value());
    metadata.setDuration(ui->imageDurationSpin->value());
    metadata.setAllowGpi(ui->imageAllowGpiCheck->isChecked());
    metadata.setAllowRemoteTriggering(ui->imageAllowRemotetriggeringCheck->isChecked());
    metadata.setRemoteTriggerId(ui->imageRemoteTriggerIdEdit->text());
    metadata.setTransition(ui->imageTransitionCombo->currentText());
    metadata.setTransitionDuration(ui->imageTransitionDurationSpin->value());
    metadata.setTween(ui->imageTweenEdit->text());
    metadata.setDirection(ui->imageDirectionCombo->currentText());
    metadata.setTriggerOnNext(ui->imageTriggerOnNextCheck->isChecked());
    metadata.setUseAuto(ui->imageUseAutoCheck->isChecked());

    return metadata;
}
