#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rundowncreator.h"
#include "rundown.h"
#include "rundownrowmodel.h"
#include "casparcggenerator.h"
#include "settingsdialog.h"
#include "casparcgvideometadata.h"
#include "casparcgstillmetadata.h"

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
    connect(m_rundownCreator, &RundownCreator::error, this, &MainWindow::showRundownCreatorError);
    connect(m_rundownCreator, &RundownCreator::status, m_statusLabel, &QLabel::setText);

    ui->rundownRowView->setModel(m_rundownCreator->rundownRowModel());

    m_videoMetadata = new CasparCGVideoMetaData;
    m_videoMetadata->readSettings();
    m_stillMetadata = new CasparCGStillMetaData;
    m_stillMetadata->readSettings();

    QSettings settings;
    m_rundownCreator->setApiUrl(settings.value("RundownCreator/Url").toString());
    m_rundownCreator->setApiKey(settings.value("RundownCreator/ApiKey").toString());
    m_rundownCreator->setApiToken(settings.value("RundownCreator/ApiToken").toString());

    getRundowns();
}

MainWindow::~MainWindow()
{
    delete ui;

    m_videoMetadata->writeSettings();
    delete m_videoMetadata;
    m_stillMetadata->writeSettings();
    delete m_stillMetadata;
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
            generator->insertMetadata("video", m_videoMetadata);
            generator->insertMetadata("image", m_stillMetadata);
            generator->convert(m_rundownCreator->rundownRowModel(), &file);
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

    dialog->setCasparCGVideoMetadata(*m_videoMetadata);
    dialog->setCasparCGStillMetadata(*m_stillMetadata);

    if(dialog->exec() == QDialog::Accepted)
    {
        settings.setValue("RundownCreator/Url", dialog->rundownCreatorUrl());
        settings.setValue("RundownCreator/ApiKey", dialog->rundownCreatorApiKey());
        settings.setValue("RundownCreator/ApiToken", dialog->rundownCreatorApiToken());

        settings.setValue("CasparCG/RundownLocation", dialog->casparCGRundownLocation());

        *m_videoMetadata = dialog->casparCGVideoMetadata();
        m_videoMetadata->writeSettings();
        *m_stillMetadata = dialog->casparCGStillMetadata();
        m_stillMetadata->writeSettings();

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
