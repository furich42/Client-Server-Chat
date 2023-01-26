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

    ui->ConnectButton->setDisabled(1);
    ui->SendButton->setDisabled(0);
    QString str = ui->NameLine->text();
    qDebug() << "readed name: " << str;

    sendToServer(str, MessageType::diagnostic);




}

void MainWindow::sendToServer(const QString& str, MessageType m_type)
{

//    QJsonObject json;


//    json["type"] = "message";
//    json["receavers"] = "all";
//    json["user"] = ui->NameLine->text();

    qDebug() <<"socket state is " <<  socket->state();
            data.clear();
            QDataStream out(&data, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_1);
            //json["message"] = str;


            QString sen = QJsonDocument(formJson(m_type, str, "all", ui->NameLine->text())).toJson() ;

            out << quint16(0) << sen;
            out.device()->seek(0);
            out << quint16(data.size() - sizeof(quint16));
            socket->write(data);
            ui->InputLine->clear();

            qDebug() << "sended: " << sen;



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

            qDebug() << "incoming message: " << str;

            QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
            QJsonObject json = doc.object();

            QString mes = json["message"].toString();
            qDebug() << "incoming mes: " << mes;


            ui->OutputBrowser->append(QTime::currentTime().toString() + " | " + json["user"].toString() + ": " + mes );
        }

    } else {
        ui->OutputBrowser->append("read error");
    }
}


void MainWindow::on_SendButton_clicked()
{
    sendToServer(ui->InputLine->text(), MessageType::message);
}


void MainWindow::on_InputLine_returnPressed()
{

    sendToServer(ui->InputLine->text(), MessageType::message);
}


QJsonObject MainWindow::formJson(MessageType m_type, const QString &message, const QString &receaver, const QString &user) {

    QJsonObject json;

    json["message"] = message;
    json["user"] = user;
    json["type"] = m_type;
    json["receavers"] = receaver;

    return json;

}

