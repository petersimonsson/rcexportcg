#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class RundownCreator;

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
    void updateRows();

    void generateCasparCG();

    void editSettings();

    void showRundownCreatorError(const QString &errorString);

private:
    Ui::MainWindow *ui;

    RundownCreator *m_rundownCreator;
};

#endif // MAINWINDOW_H
