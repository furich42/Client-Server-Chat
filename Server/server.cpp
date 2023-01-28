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
    sockets.insert(socket);

    qDebug() << "client's socketDescriptor" << socketDescriptor;



    qDebug() << "client connected" << socketDescriptor;
}


void Server::slotReadyRead() {
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_1);
    if(in.status() == QDataStream::Ok) {
        qDebug() << "read...";

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

            QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
            QJsonObject json = doc.object();

            if(json["type"] == MessageType::connection) {
                qDebug() << "mt::diagnostic";

                if(!sockets_to_names.contains(socket->socketDescriptor()) ) {
                    sockets_to_names[socket->socketDescriptor()] = json["user"].toString();
                    qDebug() << "send name to clients";
                    sendToClient(str);
                } else {
                    sockets_to_names[socket->socketDescriptor()] = json["user"].toString();
                    qDebug() << "dont send name to clients";
                }


                qDebug() << "stn.size() = " << sockets_to_names.size();
                qDebug() << "user " << socket->socketDescriptor() << " now named as " << sockets_to_names[socket->socketDescriptor()];
                break;
            }

            if(json["type"] == MessageType::disconnection) {
                qDebug() << "disconnection message";
                qDebug() << "socket " << *sockets.find(socket) << " wll be removed";
                qDebug() << sockets.size() << " - sockets.size() ";
                sockets.erase(sockets.find(socket));
                qDebug() << sockets.size() << " - now sockets.size() ";
                sockets_to_names.remove(socket->socketDescriptor());
                sendToClient(str);
                break;

            }


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

    for(QTcpSocket* s : sockets) {
        qDebug() << "message sended to client";

        qDebug() << s;
        s->write(data);
    }
}

