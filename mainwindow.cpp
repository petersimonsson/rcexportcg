#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rundowncreator.h"
#include "rundown.h"
#include "rundownrow.h"
#include "casparcggenerator.h"
#include "settingsdialog.h"

#include <QDebug>
#include <QJsonDocument>
#include <QFile>
#include <QSettings>
#include <QMessageBox>
#include <QScopedPointer>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionQuit, &QAction::triggered, QApplication::instance(), &QCoreApplication::quit);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::editSettings);

    connect(ui->rundownRefreshButton, &QToolButton::clicked, this, &MainWindow::getRundowns);
    connect(ui->fetchRundowButton, &QPushButton::clicked, this, &MainWindow::getRundownRows);
    connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::generateCasparCG);

    m_statusLabel = new QLabel (ui->statusBar);
    ui->statusBar->addPermanentWidget(m_statusLabel);

    m_rundownCreator = new RundownCreator(this);
    connect(m_rundownCreator, &RundownCreator::rundownsReceived, this, &MainWindow::updateRundowns);
    connect(m_rundownCreator, &RundownCreator::rowsReceived, this, &MainWindow::updateRows);
    connect(m_rundownCreator, &RundownCreator::error, this, &MainWindow::showRundownCreatorError);
    connect(m_rundownCreator, &RundownCreator::status, m_statusLabel, &QLabel::setText);

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
    ui->rundownCombo->clear();

    foreach(Rundown *rundown, m_rundownCreator->rundownList())
    {
        if(!rundown->isArchived() && !rundown->isTemplate() && !rundown->isDeleted())
        {
            ui->rundownCombo->addItem(rundown->title(), rundown->id());
        }
    }
}

void MainWindow::getRundownRows()
{
    if(ui->rundownCombo->count() > 0)
    {
        m_rundownCreator->fetchRows(ui->rundownCombo->itemData(ui->rundownCombo->currentIndex()).toUInt());
    }
}

void MainWindow::updateRows()
{
    QString text;

    foreach(RundownRow *row, m_rundownCreator->rowList())
    {
        text += QString("RundowID: %1 RowID: %2 PageNumber: %3 StorySlug: %4\n").arg(QString::number(row->rundownId()), QString::number(row->rowId()),
                                                                                     row->pageNumber(), row->storySlug());

        foreach(const RundownRow::Object &object, row->objects())
        {
            text += QString("\tOBJECT = Type: %1 File: %2\n").arg(object.type, object.file);
        }
    }

    ui->rowBrowser->clear();
    ui->rowBrowser->setPlainText(text);
}

void MainWindow::generateCasparCG()
{
    QSettings settings;
    QString filename = settings.value("CasparCG/RundownLocation").toString();

    if(!filename.isEmpty())
    {
        QScopedPointer<CasparCGGenerator> generator(new CasparCGGenerator(this));
        QFile file(filename);
        if(file.open(QFile::WriteOnly))
        {
            generator->setDevice(settings.value("CasparCG/ServerName").toString());
            generator->setChannel(settings.value("CasparCG/Channel", "1").toString());
            generator->setVideoLayer(settings.value("CasparCG/VideoLayer", "10").toString());
            generator->setDelay(settings.value("CasparCG/Delay", "0").toString());
            generator->setDuration(settings.value("CasparCG/Duration", "0").toString());
            generator->setAllowGpi(settings.value("CasparCG/AllowGPI", false).toBool());
            generator->setAllowRemoteTriggering(settings.value("CasparCG/AllowRemoteTriggering", false).toBool());
            generator->setRemoteTriggeringId(settings.value("CasparCG/RemoteTriggeringID", "").toString());
            generator->setStoryId(settings.value("CasparCG/StoryID", "").toString());
            generator->setTransition(settings.value("CasparCG/Transition", "CUT").toString());
            generator->setTransitionDuration(settings.value("CasparCG/TransitionDuration", "1").toString());
            generator->setTween(settings.value("CasparCG/Tween", "Linear").toString());
            generator->setDirection(settings.value("CasparCG/Direction", "RIGHT").toString());
            generator->setSeek(settings.value("CasparCG/Seek", "0").toString());
            generator->setLength(settings.value("CasparCG/Length", "0").toString());
            generator->setLoop(settings.value("CasparCG/Loop", false).toBool());
            generator->setFreezeOnLoad(settings.value("CasparCG/FreezeOnLoad", false).toBool());
            generator->setAutoPlay(settings.value("CasparCG/AutoPlay", false).toBool());
            generator->setUseAuto(settings.value("CasparCG/UseAuto", false).toBool());
            generator->setTriggerOnNext(settings.value("CasparCG/TriggerOnNext", false).toBool());
            generator->setColor(settings.value("CasparCG/Color", "Transparent").toString());
            generator->convert(m_rundownCreator->rowList(), &file);
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

    dialog->setCasparCGServerName(settings.value("CasparCG/ServerName").toString());
    dialog->setCasparCGRundownLocation(settings.value("CasparCG/RundownLocation").toString());

    dialog->setCasparCGChannel(settings.value("CasparCG/Channel", "1").toString());
    dialog->setCasparCGVideoLayer(settings.value("CasparCG/VideoLayer", "10").toString());
    dialog->setCasparCGDelay(settings.value("CasparCG/Delay", "0").toString());
    dialog->setCasparCGDuration(settings.value("CasparCG/Duration", "0").toString());
    dialog->setCasparCGAllowGpi(settings.value("CasparCG/AllowGPI", false).toBool());
    dialog->setCasparCGAllowRemoteTriggering(settings.value("CasparCG/AllowRemoteTriggering", false).toBool());
    dialog->setCasparCGRemoteTriggerId(settings.value("CasparCG/RemoteTriggeringID", "").toString());
    dialog->setCasparCGStoryId(settings.value("CasparCG/StoryID", "").toString());
    dialog->setCasparCGTransition(settings.value("CasparCG/Transition", "CUT").toString());
    dialog->setCasparCGTransitionDuration(settings.value("CasparCG/TransitionDuration", "1").toString());
    dialog->setCasparCGTween(settings.value("CasparCG/Tween", "Linear").toString());
    dialog->setCasparCGDirection(settings.value("CasparCG/Direction", "RIGHT").toString());
    dialog->setCasparCGSeek(settings.value("CasparCG/Seek", "0").toString());
    dialog->setCasparCGLength(settings.value("CasparCG/Length", "0").toString());
    dialog->setCasparCGLoop(settings.value("CasparCG/Loop", false).toBool());
    dialog->setCasparCGFreezeOnLoad(settings.value("CasparCG/FreezeOnLoad", false).toBool());
    dialog->setCasparCGAutoPlay(settings.value("CasparCG/AutoPlay", false).toBool());
    dialog->setCasparCGUseAuto(settings.value("CasparCG/UseAuto", false).toBool());
    dialog->setCasparCGTriggerOnNext(settings.value("CasparCG/TriggerOnNext", false).toBool());
    dialog->setCasparCGColor(settings.value("CasparCG/Color", "Transparent").toString());

    if(dialog->exec() == QDialog::Accepted)
    {
        settings.setValue("RundownCreator/Url", dialog->rundownCreatorUrl());
        settings.setValue("RundownCreator/ApiKey", dialog->rundownCreatorApiKey());
        settings.setValue("RundownCreator/ApiToken", dialog->rundownCreatorApiToken());

        settings.setValue("CasparCG/ServerName", dialog->casparCGServerName());
        settings.setValue("CasparCG/RundownLocation", dialog->casparCGRundownLocation());

        settings.setValue("CasparCG/Channel", dialog->casparCGChannel());
        settings.setValue("CasparCG/VideoLayer", dialog->casparCGVideoLayer());
        settings.setValue("CasparCG/Delay", dialog->casparCGDelay());
        settings.setValue("CasparCG/Duration", dialog->casparCGDuration());
        settings.setValue("CasparCG/AllowGPI", dialog->casparCGAllowGpi());
        settings.setValue("CasparCG/AllowRemoteTriggering", dialog->casparCGAllowRemoteTriggering());
        settings.setValue("CasparCG/RemoteTriggeringID", dialog->casparCGRemoteTriggerId());
        settings.setValue("CasparCG/StoryID", dialog->casparCGStoryId());
        settings.setValue("CasparCG/Transition", dialog->casparCGTransition());
        settings.setValue("CasparCG/TransitionDuration", dialog->casparCGTransitionDuration());
        settings.setValue("CasparCG/Tween", dialog->casparCGTween());
        settings.setValue("CasparCG/Direction", dialog->casparCGDirection());
        settings.setValue("CasparCG/Seek", dialog->casparCGSeek());
        settings.setValue("CasparCG/Length", dialog->casparCGLength());
        settings.setValue("CasparCG/Loop", dialog->casparCGLoop());
        settings.setValue("CasparCG/FreezeOnLoad", dialog->casparCGFreezeOnLoad());
        settings.setValue("CasparCG/AutoPlay", dialog->casparCGAutoPlay());
        settings.setValue("CasparCG/UseAuto", dialog->casparCGUseAuto());
        settings.setValue("CasparCG/TriggerOnNext", dialog->casparCGTriggerOnNext());
        settings.setValue("CasparCG/Color", dialog->casparCGColor());

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
