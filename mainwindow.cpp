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
#include "rundownrow.h"
#include "settingsdialog.h"
#include "presetstore.h"
#include "logmodel.h"
#include "folder.h"
#include "presetobjectdialog.h"

#include <QDebug>
#include <QJsonDocument>
#include <QFile>
#include <QSettings>
#include <QMessageBox>
#include <QScopedPointer>
#include <QLabel>
#include <QTextCursor>
#include <QSet>
#include <QCollator>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionQuit, &QAction::triggered, QApplication::instance(), &QCoreApplication::quit);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::editSettings);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(ui->actionAbout_Qt, &QAction::triggered, QApplication::instance(), &QApplication::aboutQt);

    connect(ui->rundownReloadButton, &QToolButton::clicked, this, &MainWindow::getRundowns);
    connect(ui->rundownCombo, &QComboBox::currentTextChanged, this, &MainWindow::getRundownRows);

    m_logModel = new LogModel(this);
    ui->logView->setModel(m_logModel);
    ui->logView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    m_rundownCreator = new RundownCreator(this);
    connect(m_rundownCreator, &RundownCreator::rundownsReceived, this, &MainWindow::updateRundowns);
    connect(m_rundownCreator, &RundownCreator::error, this, &MainWindow::appendErrorToLog);
    connect(m_rundownCreator, &RundownCreator::status, this, &MainWindow::appendStatusToLog);
    connect(m_rundownCreator, &RundownCreator::debug, this, &MainWindow::appendDebugToLog);

    ui->rundownRowView->setModel(m_rundownCreator->rundownRowModel());
    ui->rundownRowView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    m_presetStore = new PresetStore(this);

    connect(ui->actionReload, &QAction::triggered, m_presetStore, &PresetStore::loadPresets);
    connect(ui->actionDefault_Object_Map, &QAction::triggered, this, &MainWindow::showPresetObjectDialog);
    connect(m_presetStore, &PresetStore::logMessage, this, &MainWindow::appendStatusToLog);
    connect(m_presetStore, &PresetStore::error, this, &MainWindow::appendErrorToLog);

    m_presetStore->loadPresets();

    connect(m_rundownCreator, &RundownCreator::rundownRowsReceived, this, &MainWindow::validateRundownRows);
    connect(m_presetStore, &PresetStore::presetsLoaded, this, &MainWindow::validateRundownRows);
    connect(m_rundownCreator, &RundownCreator::rundownRowsReceived, this, &MainWindow::generateCasparCG);

    QSettings settings;
    m_rundownCreator->setApiUrl(settings.value("RundownCreator/Url").toString());
    m_rundownCreator->setApiKey(settings.value("RundownCreator/ApiKey").toString());
    m_rundownCreator->setApiToken(settings.value("RundownCreator/ApiToken").toString());

    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, &MainWindow::getRundowns);
    m_updateTimer->setInterval(settings.value("RundownCreator/UpdateInterval", 1).toUInt() * 60000);

    if(settings.value("RundownCreator/AutoUpdate", false).toBool())
        m_updateTimer->start();

    getRundowns();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getRundowns()
{
    if(m_rundownCreator->apiUrl().isValid())
        m_rundownCreator->getFoldersAndRundows();
}

void MainWindow::updateRundowns()
{
    QString oldSelection = ui->rundownCombo->currentText();
    bool block = ui->rundownCombo->blockSignals(true);
    ui->rundownCombo->clear();
    QMap<QString, quint32> sortMap;
    QHash<quint32, Folder*> folderHash = m_rundownCreator->folderHash();
    QString firstRundown;

    foreach(Folder *folder, folderHash)
    {
        sortMap.insert(folder->name(), folder->id());
    }

    foreach(quint32 id, sortMap)
    {
        Folder *folder = folderHash.value(id);
        ui->rundownCombo->addParentItem(folder->name());
        QList<Rundown*> rundowns = folder->rundownList();
        QCollator collator;
        collator.setNumericMode(true);

        std::sort(rundowns.begin(), rundowns.end(), [&collator](Rundown *r1, Rundown *r2) {
            return collator.compare(r1->title(), r2->title()) > 0;
        });

        foreach(Rundown *rundown, rundowns)
        {
            if(!rundown->isArchived() && !rundown->isTemplate() && !rundown->isDeleted())
            {
                ui->rundownCombo->addChildItem(rundown->title(), rundown->id());

                if(firstRundown.isEmpty())
                    firstRundown = rundown->title();
            }
        }
    }

    ui->rundownCombo->blockSignals(block);

    if(ui->rundownCombo->findText(oldSelection) != -1)
    {
        ui->rundownCombo->setCurrentText(oldSelection);
    }
    else
    {
        ui->rundownCombo->setCurrentText(firstRundown);
    }

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
        m_presetStore->loadPresets();

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
    QScopedPointer<SettingsDialog> dialog(new SettingsDialog(this));

    dialog->setRundownCreatorUrl(settings.value("RundownCreator/Url").toString());
    dialog->setRundownCreatorApiKey(settings.value("RundownCreator/ApiKey").toString());
    dialog->setRundownCreatorApiToken(settings.value("RundownCreator/ApiToken").toString());

    dialog->setRundownCreatorAutoUpdate(settings.value("RundownCreator/AutoUpdate", false).toBool());
    dialog->setRundownCreatorUpdateInterval(settings.value("RundownCreator/UpdateInterval", 1).toUInt());

    dialog->setCasparCGRundownLocation(settings.value("CasparCG/RundownLocation").toString());

    if(dialog->exec() == QDialog::Accepted)
    {
        settings.setValue("RundownCreator/Url", dialog->rundownCreatorUrl());
        settings.setValue("RundownCreator/ApiKey", dialog->rundownCreatorApiKey());
        settings.setValue("RundownCreator/ApiToken", dialog->rundownCreatorApiToken());

        settings.setValue("RundownCreator/AutoUpdate", dialog->rundownCreatorAutoUpdate());
        settings.setValue("RundownCreator/UpdateInterval", dialog->rundownCreatorUpdateInterval());

        settings.setValue("CasparCG/RundownLocation", dialog->casparCGRundownLocation());

        m_rundownCreator->setApiUrl(settings.value("RundownCreator/Url").toString());
        m_rundownCreator->setApiKey(settings.value("RundownCreator/ApiKey").toString());
        m_rundownCreator->setApiToken(settings.value("RundownCreator/ApiToken").toString());

        m_updateTimer->setInterval(dialog->rundownCreatorUpdateInterval() * 60000);

        if(dialog->rundownCreatorAutoUpdate())
            m_updateTimer->start();
        else
            m_updateTimer->stop();

        getRundowns();
    }
}

void MainWindow::appendErrorToLog(const QString &errorString)
{
    m_logModel->append(LogModel::Error, errorString);
    ui->logView->scrollToBottom();
}

void MainWindow::appendStatusToLog(const QString &message)
{
    m_logModel->append(LogModel::Info, message);
    ui->logView->scrollToBottom();
}

void MainWindow::appendDebugToLog(const QString &message)
{
    m_logModel->append(LogModel::Debug, message);
    ui->logView->scrollToBottom();
}

void MainWindow::validateRundownRows()
{
    m_presetStore->validateRows(m_rundownCreator->rundownRowModel());
}

void MainWindow::showAboutDialog()
{
    QMessageBox::about(this, tr("About RCExportCG"), tr("RCExportCG version %1").arg(QApplication::instance()->applicationVersion()));
}

void MainWindow::showPresetObjectDialog()
{
    QList<RundownRow*> rows = m_rundownCreator->rundownRowModel()->rowList();
    QSet<QString> objects;

    foreach(RundownRow *row, rows)
    {
        objects.insert(row->type());
    }

    QScopedPointer<PresetObjectDialog> dialog(new PresetObjectDialog(objects.values(), m_presetStore->presets(), this));
    dialog->setObjectPresets(m_presetStore->defaultPresets());

    if(dialog->exec() == QDialog::Accepted)
    {
        m_presetStore->setDefaultPresets(dialog->objectPresets());
    }
}
