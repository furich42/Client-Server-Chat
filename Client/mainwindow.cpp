#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket  = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    nextBlockSize = 0;
    ui->SendButton->setDisabled(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ConnectButton_clicked()
{

    QString ip = ui->IpLine->text();
    socket->connectToHost(ip, 2323);

//    int i = 0;
//    while(socket->state() == QAbstractSocket::ConnectingState) {
//        qDebug() << socket->state();
//        if(socket->state() == QAbstractSocket::ConnectedState) {
//            break;
//        }
//        sleep(1);
//        i++;
//        if(i >= 30) {
//            break;
//        }
//    }



    if(socket->state() == QAbstractSocket::ConnectedState || (fcon ? socket->state() == QAbstractSocket::ConnectingState : false)) {

        ui->ConnectButton->setDisabled(1);
        ui->SendButton->setDisabled(0);
        QString str = ui->NameLine->text();
        qDebug() << "readed name: " << str;

        sendToServer(str);

    } else {
        fcon = true;
        qDebug() << "error, can't connect to server\nTry again";
    }



}

void MainWindow::sendToServer(QString str)
{
    qDebug() <<"socket state is " <<  socket->state();
        if(socket->state() == QAbstractSocket::ConnectedState || (fcon ? socket->state() == QAbstractSocket::ConnectingState : false)) {
            data.clear();
            QDataStream out(&data, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_1);
            qDebug() << "sending: " << str;
            out << quint16(0) << str;
            out.device()->seek(0);
            out << quint16(data.size() - sizeof(quint16));
            socket->write(data);
            ui->InputLine->clear();
            fcon = false;

        }

}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_1);
    if(in.status() == QDataStream::Ok) {
//        QString str;
//        in >> str;
//        ui->OutputBrowser->append(str);
        while(true) {
            if(nextBlockSize == 0) {
                if(socket->bytesAvailable() < 2) {
                    break;
                }
                in >> nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize) {
                break;
            }
            QString str;
            in >> str;
            nextBlockSize = 0;
            ui->OutputBrowser->append(QTime::currentTime().toString() + " " + str);
        }

    } else {
        ui->OutputBrowser->append("read error");
    }
}


void MainWindow::on_SendButton_clicked()
{
    sendToServer(ui->InputLine->text());
}


void MainWindow::on_InputLine_returnPressed()
{

    sendToServer(ui->InputLine->text());
}

