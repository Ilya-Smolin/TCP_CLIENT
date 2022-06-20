#ifndef TCP_HANDLER_H
#define TCP_HANDLER_H

#include <QWidget>
#include <qtimer.h>
#include <QString>
#include <QElapsedTimer>
#include <QTimer>
#include <QThread>
#include <string>
#include <QDebug>
#include <QKeyEvent>
#include <iostream>
#include <QScrollBar>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QTime>

using namespace std;

class tcp_handler : public QObject
{
    Q_OBJECT
public:
    explicit tcp_handler(QObject *parent = nullptr);

signals:

    void send_tcp_signal(const QByteArray ba);

public slots:
    void send_tcp(const QByteArray ba);

    void HandleStateChange(QAbstractSocket::SocketState socketState);

    void timeout_handler();

    void connect_to_tcp(QString IP, quint16 port);

private:
    QTcpSocket *tcpClient;

    QTimer *timer_send, *timer_invert;

    QElapsedTimer *elapsed_timer;

    QString *text;
};

#endif // TCP_HANDLER_H
