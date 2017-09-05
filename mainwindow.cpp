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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rundowncreator.h"
#include "rundown.h"
#include "rundownrowmodel.h"
#include "settingsdialog.h"
#include "presetstore.h"

#include <QDebug>
#include <QJsonDocument>
#include <QFile>
#include <QSettings>
#include <QMessageBox>
#include <QScopedPointer>
#include <QLabel>
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionQuit, &QAction::triggered, QApplication::instance(), &QCoreApplication::quit);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::editSettings);

    ui->rundownReloadButton->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));

    connect(ui->rundownReloadButton, &QToolButton::clicked, this, &MainWindow::getRundowns);
    connect(ui->rundownCombo, &QComboBox::currentTextChanged, this, &MainWindow::getRundownRows);
    connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::generateCasparCG);

    m_statusLabel = new QLabel (ui->statusBar);
    ui->statusBar->addPermanentWidget(m_statusLabel);

    m_rundownCreator = new RundownCreator(this);
    connect(m_rundownCreator, &RundownCreator::rundownsReceived, this, &MainWindow::updateRundowns);
    connect(m_rundownCreator, &RundownCreator::error, this, &MainWindow::showRundownCreatorError);
    connect(m_rundownCreator, &RundownCreator::status, m_statusLabel, &QLabel::setText);

    ui->rundownRowView->setModel(m_rundownCreator->rundownRowModel());
    ui->rundownRowView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    m_presetStore = new PresetStore(this);

    connect(ui->actionReload, &QAction::triggered, m_presetStore, &PresetStore::loadPresets);
    connect(m_presetStore, &PresetStore::logMessage, this, &MainWindow::appendToLog);

    m_presetStore->loadPresets();

    QSettings settings;
    m_rundownCreator->setApiUrl(settings.value("RundownCreator/Url").toString());
    m_rundownCreator->setApiKey(settings.value("RundownCreator/ApiKey").toString());
    m_rundownCreator->setApiToken(settings.value("RundownCreator/ApiToken").toString());

    getRundowns();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getRundowns()
{
    if(m_rundownCreator->apiUrl().isValid())
        m_rundownCreator->getRundowns();
}

void MainWindow::updateRundowns()
{
    QString oldSelection = ui->rundownCombo->currentText();
    bool block = ui->rundownCombo->blockSignals(true);
    ui->rundownCombo->clear();

    foreach(Rundown *rundown, m_rundownCreator->rundownList())
    {
        if(!rundown->isArchived() && !rundown->isTemplate() && !rundown->isDeleted())
        {
            ui->rundownCombo->addItem(rundown->title(), rundown->id());
        }
    }

    ui->rundownCombo->blockSignals(block);
    ui->rundownCombo->setCurrentText(oldSelection);
    getRundownRows();
}

void MainWindow::getRundownRows()
{
    if(ui->rundownCombo->count() > 0)
    {
        m_rundownCreator->fetchRows(ui->rundownCombo->itemData(ui->rundownCombo->currentIndex()).toUInt());
    }
}

void MainWindow::generateCasparCG()
{
    QSettings settings;
    QString filename = settings.value("CasparCG/RundownLocation").toString();

    if(!filename.isEmpty())
    {
        QFile file(filename);
        if(file.open(QFile::WriteOnly))
        {
            m_presetStore->generateCasparCG(m_rundownCreator->rundownRowModel(), &file);
        }
    }
}

void MainWindow::editSettings()
{
    QSettings settings;
    SettingsDialog *dialog = new SettingsDialog(this);

    dialog->setRundownCreatorUrl(settings.value("RundownCreator/Url").toString());
    dialog->setRundownCreatorApiKey(settings.value("RundownCreator/ApiKey").toString());
    dialog->setRundownCreatorApiToken(settings.value("RundownCreator/ApiToken").toString());

    dialog->setCasparCGRundownLocation(settings.value("CasparCG/RundownLocation").toString());

    dialog->setObjectPresets(m_presetStore->defaultPresets());

    if(dialog->exec() == QDialog::Accepted)
    {
        settings.setValue("RundownCreator/Url", dialog->rundownCreatorUrl());
        settings.setValue("RundownCreator/ApiKey", dialog->rundownCreatorApiKey());
        settings.setValue("RundownCreator/ApiToken", dialog->rundownCreatorApiToken());

        settings.setValue("CasparCG/RundownLocation", dialog->casparCGRundownLocation());

        m_presetStore->setDefaultPresets(dialog->objectPresets());

        m_rundownCreator->setApiUrl(settings.value("RundownCreator/Url").toString());
        m_rundownCreator->setApiKey(settings.value("RundownCreator/ApiKey").toString());
        m_rundownCreator->setApiToken(settings.value("RundownCreator/ApiToken").toString());

        getRundowns();
    }
}

void MainWindow::showRundownCreatorError(const QString &errorString)
{
    QMessageBox::warning(this, tr("RundownCreator Connection Error"), errorString);
}

void MainWindow::appendToLog(const QString &message)
{
    QTextCursor cursor = ui->logView->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(message + "\n");
}
