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
#ifndef PRESETOBJECTDIALOG_H
#define PRESETOBJECTDIALOG_H

#include <QDialog>

namespace Ui {
class PresetObjectDialog;
}

class SettingsModel;

class PresetObjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PresetObjectDialog(const QStringList &objects, const QStringList &presets, QWidget *parent = nullptr);
    ~PresetObjectDialog();

    void setObjectPresets(const QHash<QString, QString> &presets);
    QHash<QString, QString> objectPresets() const;

private slots:
    void addObject();
    void removeObject();

private:
    Ui::PresetObjectDialog *ui;

    SettingsModel *m_objectModel;
};

#endif // PRESETOBJECTDIALOG_H
