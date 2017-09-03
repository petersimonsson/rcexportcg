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

    void setCasparCGRundownLocation(const QString &location);
    QString casparCGRundownLocation() const;

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
