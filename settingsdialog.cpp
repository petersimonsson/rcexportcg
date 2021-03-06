/**************************************************************************
  RCExportCG
  Copyright (C) 2017  Peter Simonsson <peter.simonsson@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QFileDialog>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    connect(ui->browseButton, &QToolButton::clicked, this, &SettingsDialog::browseFiles);
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

void SettingsDialog::setRundownCreatorAutoUpdate(bool update)
{
    ui->autoUpdateCheck->setChecked(update);
}

bool SettingsDialog::rundownCreatorAutoUpdate() const
{
    return ui->autoUpdateCheck->isChecked();
}

void SettingsDialog::setRundownCreatorUpdateInterval(quint8 interval)
{
    ui->updateIntervalSpin->setValue(interval);
}

quint8 SettingsDialog::rundownCreatorUpdateInterval() const
{
    return ui->updateIntervalSpin->value();
}

void SettingsDialog::setCasparCGRundownLocation(const QString &location)
{
    ui->ccgRundownLocationEdit->setText(location);
}

QString SettingsDialog::casparCGRundownLocation() const
{
    return ui->ccgRundownLocationEdit->text();
}

void SettingsDialog::browseFiles()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Choose Rundown File"), ui->ccgRundownLocationEdit->text(),
                                                "*.xml", nullptr, QFileDialog::DontConfirmOverwrite);

    if(!file.isEmpty())
    {
        ui->ccgRundownLocationEdit->setText(file);
    }
}
