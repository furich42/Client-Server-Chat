#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>


#include <unistd.h>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ConnectButton_clicked();

    void on_SendButton_clicked();

    void on_InputLine_returnPressed();

    void closeEvent(QCloseEvent *);



private:

    enum MessageType {
        message,
        file,
        diagnostic,
        connection,
        disconnection
    };

    QString user_name = "";

    Ui::MainWindow *ui;

    QTcpSocket *socket;

    QByteArray data;

    void sendToServer(const QString& str);

    quint16 nextBlockSize;

    bool fcon = true;

    QJsonObject formJson(MessageType m_type, const QString& message, const QString& receaver, const QString& user);

public slots:
    void slotReadyRead();

};
#endif // MAINWINDOW_H
