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

    QString p_name = "";
    QSet<QTcpSocket*> sockets;
    //QMap<qintptr, QString> sockets_to_names;
    std::map</*qintptr*/ QAbstractSocket*, QString> sockets_to_names;
    QByteArray data;
    void sendToClients(QString str);
    qint16 nextBlockSize;
    QJsonObject formJson(MessageType m_type, const QString &message, const QString &receaver, const QString &user);

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
    void handleDisc();

};




#endif // SERVER_H



