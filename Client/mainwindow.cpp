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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ConnectButton_clicked()
{
    socket->connectToHost("127.0.0.1", 2323);
}

void MainWindow::sendToServer(QString str)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_1);
    out << str;
    socket->write(data);
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_1);
    if(in.status() == QDataStream::Ok) {
        QString str;
        in >> str;
        ui->OutputBrowser->append(str);
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

