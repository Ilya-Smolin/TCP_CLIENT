#include "receive_tcp.h"

receive_tcp::receive_tcp(QObject *parent) : QObject(parent){
    qDebug() << "   Tcp Recieve SETUP...";

    tcpClient = new QTcpSocket (this);

    bool success = connect(tcpClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                           this, SLOT(HandleStateChange(QAbstractSocket::SocketState)));
    Q_ASSERT(success);

    success = connect(tcpClient, SIGNAL(readyRead()), this, SLOT(recieved_msg_handler()));
    Q_ASSERT(success);

    qDebug() << "       SETUP FINISHED";
}

void receive_tcp::HandleStateChange(QAbstractSocket::SocketState socketState){
    qDebug() << "Changed Socket state:" <<socketState;
}

void receive_tcp::recieved_msg_handler(){
    QByteArray recieved = tcpClient->readAll();
    if(recieved.size() == 31) emit recieved_to_ui(recieved);
}

void receive_tcp::connect_to_tcp(QString IP, quint16 port){
    tcpClient->connectToHost(IP, port);
    tcpClient->flush();
}

