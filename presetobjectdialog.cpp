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
#include "presetobjectdialog.h"
#include "ui_presetobjectdialog.h"
#include "settingsmodel.h"
#include "settingsdelegate.h"

#include <QSettings>

PresetObjectDialog::PresetObjectDialog(const QStringList &objects, const QStringList &presets, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PresetObjectDialog)
{
    ui->setupUi(this);

    ui->objectView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    m_objectModel = new SettingsModel(this);
    ui->objectView->setModel(m_objectModel);

    SettingsDelegate *delegate = new SettingsDelegate(ui->objectView);
    delegate->setPresets(presets);
    delegate->setObjects(objects);
    ui->objectView->setItemDelegate(delegate);

    connect(ui->addObjectButton, &QToolButton::clicked, this, &PresetObjectDialog::addObject);
    connect(ui->removeObjectButton, &QToolButton::clicked, this, &PresetObjectDialog::removeObject);

    QSettings settings;
    restoreGeometry(settings.value("PresetObjectDialog/Geometry").toByteArray());
}

PresetObjectDialog::~PresetObjectDialog()
{
    QSettings settings;
    settings.setValue("PresetObjectDialog/Geometry", saveGeometry());

    delete ui;
}

void PresetObjectDialog::setObjectPresets(const QHash<QString, QString> &presets)
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

QHash<QString, QString> PresetObjectDialog::objectPresets() const
{
    QHash<QString, QString> presets;

    foreach(SettingsModelItem *item, m_objectModel->items())
    {
        presets.insert(item->object(), item->preset());
    }

    return presets;
}

void PresetObjectDialog::addObject()
{
    SettingsModelItem *item = new SettingsModelItem;
    QModelIndex index = m_objectModel->append(item);

    ui->objectView->edit(index);
}

void PresetObjectDialog::removeObject()
{
    QItemSelectionModel *selectionModel = ui->objectView->selectionModel();

    QModelIndex index = selectionModel->selectedIndexes().first();
    m_objectModel->removeRow(index.row());
}
