#include "mainwindow.h"
#include <QTcpServer>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exit(a.exec());
    return 0;
}
