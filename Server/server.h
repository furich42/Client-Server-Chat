#ifndef SERVER_H
#define SERVER_H


#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server();
    ~Server();
    QTcpSocket *socket;

private:
    QVector<QTcpSocket*> sockets;
    QByteArray data;
    void sendToClient();

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();

};




#endif // SERVER_H



