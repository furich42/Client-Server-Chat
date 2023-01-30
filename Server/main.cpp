#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    Server server;
    //qDebug() << "MAIN::check";
    a.exec();
    return 0;
}
