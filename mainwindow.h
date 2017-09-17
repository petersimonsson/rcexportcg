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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class RundownCreator;
class PresetStore;
class LogModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void getRundowns();

    void updateRundowns();
    void getRundownRows();

    void generateCasparCG();

    void editSettings();

    void appendErrorToLog(const QString &errorString);
    void appendStatusToLog(const QString &message);
    void appendDebugToLog(const QString &message);

    void validateRundownRows();

private:
    Ui::MainWindow *ui;

    RundownCreator *m_rundownCreator;
    PresetStore *m_presetStore;

    LogModel *m_logModel;
};

#endif // MAINWINDOW_H
