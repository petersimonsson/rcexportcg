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
