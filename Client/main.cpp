#include "mainwindow.h"
#include <QTcpServer>

#include <QApplication>

int main(int argc, char *argv[])
{
    try {

        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        //a.connect(&a, &QApplication::aboutToQuit, &a, &QApplication::quit);

        //return a.exec();
        a.exit(a.exec());
    } catch(const error_t e) {

    }


    return 0;
}
