#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class RundownCreator;
class CasparCGVideoMetaData;
class CasparCGStillMetaData;
class QLabel;

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

    void showRundownCreatorError(const QString &errorString);

private:
    Ui::MainWindow *ui;

    RundownCreator *m_rundownCreator;

    CasparCGVideoMetaData *m_videoMetadata;
    CasparCGStillMetaData *m_stillMetadata;

    QLabel *m_statusLabel;
};

#endif // MAINWINDOW_H
