#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->SendButton->setDisabled(1);
    socket = nullptr;

}

MainWindow::~MainWindow()
{
    //handleDisc();
    delete ui;

}


void MainWindow::on_ConnectButton_clicked()
{

    socket  = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::handleDisc);
    connect(socket, &QAbstractSocket::connected, this, &MainWindow::handleConn);
    nextBlockSize = 0;

    QString ip = ui->IpLine->text();
    socket->connectToHost(ip, 2323);
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("connecting...");

}

void MainWindow::sendToServer(const QString& str)
{

    if(socket->isValid()) {
        qDebug() <<"socket state is " <<  socket->state();
        data.clear();
        QDataStream out(&data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_1);
        out << quint16(0) << str;
        out.device()->seek(0);
        out << quint16(data.size() - sizeof(quint16));
        socket->write(data);


        qDebug() << "sended: " << str;
    }
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_1);
    if(in.status() == QDataStream::Ok) {
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

            qDebug() << "incoming message: " << str;

            QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
            QJsonObject json = doc.object();


            if(json["type"] == MessageType::message) {
                QString mes = json["text"].toString();
                qDebug() << "incoming message: " << mes;
                ui->OutputBrowser->append(QTime::currentTime().toString() + " - " + json["user"].toString() + ": " + mes );
            }

            if(json["type"] == MessageType::connection) {
                QString mes = json["user"].toString();
                qDebug() << "connection: " << mes;
                ui->OutputBrowser->append(QTime::currentTime().toString() + " - " + mes + " has connected" );
            }

            if(json["type"] == MessageType::disconnection) {
                QString mes = json["user"].toString();
                qDebug() << "disconnection: " << mes;
                ui->OutputBrowser->append(QTime::currentTime().toString() + " - " + mes + " has disconnected" );
            }

            if(json["type"] == MessageType::diagnostic) {
                qDebug() << "DIAGNOSTIC";
            }




        }

    } else {
        ui->OutputBrowser->append("read error");
    }
}


void MainWindow::on_SendButton_clicked()
{
    sendToServer(QJsonDocument(formJson(MessageType::message, ui->InputLine->text(), "all", ui->NameLine->text())).toJson());
    ui->InputLine->clear();
}


void MainWindow::on_InputLine_returnPressed()
{
    if(ui->SendButton->isEnabled()) {
        sendToServer(QJsonDocument(formJson(MessageType::message, ui->InputLine->text(), "all", ui->NameLine->text())).toJson());
        ui->InputLine->clear();
    }

}


QJsonObject MainWindow::formJson(MessageType m_type, const QString &message, const QString &receaver, const QString &user) {

    QJsonObject json;

    json["text"] = message;
    json["user"] = user;
    json["type"] = m_type;
    json["receavers"] = receaver;

    return json;

}


void MainWindow::closeEvent(QCloseEvent *)
{
    if(ui->SendButton->isEnabled()) {
        sendToServer(QJsonDocument(formJson(MessageType::disconnection,"" , "all", user_name)).toJson());
    }
    handleDisc();
}


void MainWindow::handleDisc() {

    if(socket != nullptr) {
        ui->statusBar->showMessage("connection lost, try reconnect");
        qDebug() << "CONNECTION LOST";
        ui->SendButton->setDisabled(1);
        ui->ConnectButton->setDisabled(0);
        socket->disconnect();
        socket->disconnectFromHost();
        socket->deleteLater();
    }


}

void MainWindow::handleConn() {
    user_name = ui->NameLine->text();
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("connected to server");
    ui->ConnectButton->setDisabled(1);
    ui->SendButton->setDisabled(0);
    qDebug() << "readed name: " << user_name;

    sendToServer(QJsonDocument(formJson(MessageType::connection, "", "all", ui->NameLine->text())).toJson());
}
