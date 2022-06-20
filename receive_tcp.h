#ifndef RECEIVE_TCP_H
#define RECEIVE_TCP_H

#include <QObject>
#include "tcp_handler.h"

class receive_tcp : public QObject
{
    Q_OBJECT
public:
    explicit receive_tcp(QObject *parent = nullptr);

signals:
    void recieved_to_ui(const QByteArray ba);

public slots:
    void HandleStateChange(QAbstractSocket::SocketState socketState);

    void recieved_msg_handler();

    void connect_to_tcp(QString IP, quint16 port);

private:
    QTcpSocket *tcpClient;

    QString *text;
};


#endif // RECEIVE_TCP_H
