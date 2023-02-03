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
    connect(socket, &QTcpSocket::disconnected, this, &Server::handleDisc);
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

            qDebug() << "bef stn.size() = " << sockets_to_names.size();
            if(json["type"] == MessageType::connection) {
                qDebug() << "mt::diagnostic";

                if(sockets_to_names.count(socket) == 0 ) {
                    sockets_to_names[socket] = json["user"].toString();
                    qDebug() << "send name to clients";
                    sendToClients(str);
                } else {
                    sockets_to_names[socket] = json["user"].toString();
                    qDebug() << "dont send name to clients";
                }


                qDebug() << "stn.size() = " << sockets_to_names.size();
                qDebug() << "user " << socket->socketDescriptor() << " now named as " << sockets_to_names[socket];
                break;
            }

            if(json["type"] == MessageType::disconnection) {
                qDebug() << "disconnection message";
                qDebug() << "socket " << *sockets.find(socket) << " wll be removed";
                qDebug() << sockets.size() << " - sockets.size() ";


//                sockets.erase(sockets.find(socket));
//                sockets_to_names.remove(socket->socketDescriptor());
//                socket->disconnect();
//                socket->disconnectFromHost();
//                socket->deleteLater();
                p_name = json["user"].toString();
                qDebug() << "user to disconnect - " << p_name;
                handleDisc();
                p_name = "";
                qDebug() << sockets.size() << " - now sockets.size() ";
                //sendToClients(str);
                break;

            }




            sendToClients(str);
            break;
        }

    } else {
        qDebug() << "Data stream error";
    }
}


void Server::sendToClients(QString str) {
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_1);
    out << qint16(0) << str;
    out.device()->seek(0);
    out << qint16(data.size() - sizeof(qint16));

    for(QTcpSocket* s : sockets) {

        if(s->isValid()) {
            qDebug() << "message sended to client";
            qDebug() << s;
            s->write(data);
            continue;
        }

        if(!s->isValid()) {
            qDebug() << "socket not valid";
        }


    }
}

QJsonObject Server::formJson(MessageType m_type, const QString &message, const QString &receaver, const QString &user) {

    QJsonObject json;

    json["text"] = message;
    json["user"] = user;
    json["type"] = m_type;
    json["receavers"] = receaver;

    return json;

}


void Server::handleDisc() {
   // QString name = sockets_to_names[socket->socketDescriptor()];
    qDebug() << socket;
    qDebug() << socket->socketDescriptor();
    qDebug() << "SOCKET DISC";
    qDebug() << sockets_to_names[socket];
    sendToClients(QJsonDocument(formJson(MessageType::disconnection, "", "all", sockets_to_names[socket])).toJson());
    //sockets_to_names.remove(socket->socketDescriptor());
    sockets_to_names.erase(socket);
    sockets.erase(sockets.find(socket));

    socket->disconnect();
    socket->disconnectFromHost();
    socket->deleteLater();
    qDebug() << "??? client deleted";
}


/// TODO - bug with map<ptr, QString>;
///         handleDisc() - didnt delete values from sockets_to_names;
///
/// no name in disck because handleDisc called from connection? and there is no socket or message



