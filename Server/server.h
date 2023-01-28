#ifndef SERVER_H
#define SERVER_H


#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QSet>
#include <QDataStream>
#include <QMap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>


class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server();
    ~Server();
    QTcpSocket *socket;

private:

    enum MessageType {
        message,
        file,
        diagnostic,
        connection,
        disconnection
    };

    QSet<QTcpSocket*> sockets;
    QMap<qintptr, QString> sockets_to_names;
    QByteArray data;
    void sendToClient(QString str);
    qint16 nextBlockSize;

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();

};




#endif // SERVER_H



