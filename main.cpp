#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("rcexportcg");
    a.setApplicationVersion("0.1");
    a.setOrganizationDomain("tmro.tv");
    a.setOrganizationName("TMRO");

    MainWindow w;
    w.show();

    return a.exec();
}
