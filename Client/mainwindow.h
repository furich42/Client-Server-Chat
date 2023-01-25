#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>


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

private:
    Ui::MainWindow *ui;

    QTcpSocket *socket;

    QByteArray data;
    void sendToServer(QString str);

    quint16 nextBlockSize;

public slots:
    void slotReadyRead();

};
#endif // MAINWINDOW_H
