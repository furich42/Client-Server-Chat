#include "server.h"

Server::Server() {
    if(this->listen(QHostAddress::Any, 2323)) {
        qDebug() << "start";
    } else {
        qDebug() << "error";
    }
    nextBlockSize = 0;
}

Server::~Server() {
   qDebug() << "server stoped";
}


void Server::incomingConnection(qintptr socketDescriptor) {
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    sockets.push_back(socket);

    qDebug() << "client's socketDescriptor" << socketDescriptor;

    sockets_to_names[socket->socketDescriptor()] = "";

    qDebug() << "client connected" << socketDescriptor;
}


void Server::slotReadyRead() {
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_1);
    if(in.status() == QDataStream::Ok) {
        qDebug() << "read...";
//        QString str;
//        in >> str;
//        qDebug() << str;
//        sendToClient(str);

        while(true) {
            if(nextBlockSize == 0) {
                qDebug() << "nextBlockSize = 0";
                if(socket->bytesAvailable() < 2) {
                    qDebug() << "data < 2, break!";
                    break;
                }
                in >> nextBlockSize;
                qDebug() << "nextBlockSize = " << nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize) {
                qDebug() << "data not full, break";
                break;
            }

            QString str;
            in >> str;
            nextBlockSize = 0;
            qDebug() << "sending: " << str;
            if(sockets_to_names.count(socket->socketDescriptor()) && sockets_to_names[socket->socketDescriptor()] == "") {
                sockets_to_names[socket->socketDescriptor()] = str;
                qDebug() << "user " << socket->socketDescriptor() << " now named as " << str;
                break;
            }
            str = sockets_to_names[socket->socketDescriptor()] + ": " + str;
            sendToClient(str);
            break;
        }

    } else {
        qDebug() << "Data stream error";
    }
}


void Server::sendToClient(QString str) {
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_1);
    out << qint16(0) << str;
    out.device()->seek(0);
    out << qint16(data.size() - sizeof(qint16));
//    socket->write(data);
    for(int i = 0; i < sockets.size(); i++) {
        sockets[i]->write(data);
    }
}

