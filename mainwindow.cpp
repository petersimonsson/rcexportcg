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

    m_rundownCreator = new RundownCreator(this);
    connect(m_rundownCreator, &RundownCreator::rundownsReceived, this, &MainWindow::updateRundowns);
    connect(m_rundownCreator, &RundownCreator::rowsReceived, this, &MainWindow::updateRows);

    QSettings settings;
    m_rundownCreator->setApiUrl(settings.value("RundownCreator/Url").toString());
    m_rundownCreator->setApiKey(settings.value("RundownCreator/ApiKey").toString());
    m_rundownCreator->setApiToken(settings.value("RundownCreator/ApiToken").toString());
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
        CasparCGGenerator *generator = new CasparCGGenerator(this);
        generator->setDevice(settings.value("CasparCG/ServerName").toString());
        QFile file(filename);
        if(file.open(QFile::WriteOnly))
        {
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

    if(dialog->exec() == QDialog::Accepted)
    {
        settings.setValue("RundownCreator/Url", dialog->rundownCreatorUrl());
        settings.setValue("RundownCreator/ApiKey", dialog->rundownCreatorApiKey());
        settings.setValue("RundownCreator/ApiToken", dialog->rundownCreatorApiToken());
        settings.setValue("CasparCG/ServerName", dialog->casparCGServerName());
        settings.setValue("CasparCG/RundownLocation", dialog->casparCGRundownLocation());

        m_rundownCreator->setApiUrl(settings.value("RundownCreator/Url").toString());
        m_rundownCreator->setApiKey(settings.value("RundownCreator/ApiKey").toString());
        m_rundownCreator->setApiToken(settings.value("RundownCreator/ApiToken").toString());
    }
}
