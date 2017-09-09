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
#include "settingsmodel.h"
#include "settingsdelegate.h"

SettingsDialog::SettingsDialog(const QStringList &presets, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    m_objectModel = new SettingsModel(this);
    ui->objectView->setModel(m_objectModel);

    SettingsDelegate *delegate = new SettingsDelegate(ui->objectView);
    delegate->setPresets(presets);
    ui->objectView->setItemDelegate(delegate);

    connect(ui->addObjectButton, &QToolButton::clicked, this, &SettingsDialog::addObject);
    connect(ui->removeObjectButton, &QToolButton::clicked, this, &SettingsDialog::removeObject);
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

void SettingsDialog::setObjectPresets(const QHash<QString, QString> &presets)
{
    QHash<QString, QString>::const_iterator it = presets.begin();

    for(; it != presets.end(); ++it)
    {
        SettingsModelItem *item = new SettingsModelItem;
        item->setObject(it.key());
        item->setPreset(it.value());
        m_objectModel->append(item);
    }
}

QHash<QString, QString> SettingsDialog::objectPresets() const
{
    QHash<QString, QString> presets;

    foreach(SettingsModelItem *item, m_objectModel->items())
    {
        presets.insert(item->object(), item->preset());
    }

    return presets;
}

void SettingsDialog::addObject()
{
    SettingsModelItem *item = new SettingsModelItem;
    item->setObject("object");
    item->setPreset("preset");
    QModelIndex index = m_objectModel->append(item);

    ui->objectView->edit(index);
}

void SettingsDialog::removeObject()
{
    QItemSelectionModel *selectionModel = ui->objectView->selectionModel();

    QModelIndex index = selectionModel->selectedIndexes().first();
    m_objectModel->removeRow(index.row());
}
