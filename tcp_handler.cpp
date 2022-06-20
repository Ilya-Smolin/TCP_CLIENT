#include "tcp_handler.h"

//static int counter = 0;
//static int lost = 0;

static bool function_invertor;
static uint timer_value_msec = 1500;
static double value_to_send = 0.05;

tcp_handler::tcp_handler(QObject *parent) : QObject(parent){
    qDebug() << "   Tcp Handler SETUP...";
    function_invertor = true;
    tcpClient = new QTcpSocket (this);
    timer_send = new QTimer(this);
    elapsed_timer = new QElapsedTimer;
    elapsed_timer->start();
//    start_time = time_.currentTime().msecsSinceStartOfDay();
//    qDebug() << start_time;

    bool success = connect(tcpClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                           this, SLOT(HandleStateChange(QAbstractSocket::SocketState)));
    Q_ASSERT(success);

    success = connect(timer_send, SIGNAL(timeout()), this, SLOT(timeout_handler()));
    Q_ASSERT(success);

    timer_send->start(1);

    qDebug() << "       SETUP FINISHED";
}

void tcp_handler::send_tcp(const QByteArray ba){
//    qDebug() << "Sending" << ba;
    if(tcpClient->state() == QAbstractSocket::ConnectedState){
        tcpClient->write(ba.constData(), ba.count());
        qDebug() << ba;
    }
    else qDebug() << "Not connected";
    //emit recieved_to_ui(ba);
}

void tcp_handler::HandleStateChange(QAbstractSocket::SocketState socketState){
    qDebug() << "Changed Socket state:" <<socketState;
//    if(socketState == QAbstractSocket::ConnectedState)
//        tcpClient->write("as\n");
}

static int counter = 0;
void tcp_handler::timeout_handler(){
//    text = new QString;
    counter++;
    uint time_ = static_cast<uint>(elapsed_timer->elapsed());
    if(time_ >= timer_value_msec){
        function_invertor = !function_invertor;
        qDebug() << function_invertor <<time_ << counter;
        elapsed_timer->start();
    }
//    else qDebug() << "ELSE" << function_invertor;

//    if(function_invertor)
//        text->append(QString("%1").arg(QString::number(value_to_send)));
//    else
//        text->append(QString("-%1").arg(QString::number(value_to_send)));

//    QTime ct = QTime::currentTime();
//    QString text = ct.toString("hh:mm:ss.zzz\n");
//    QByteArray ba = text->toLatin1();
//    delete(text);
//    qDebug() << ba;
//    send_tcp(ba);
}

void tcp_handler::connect_to_tcp(QString IP, quint16 port){
    tcpClient->connectToHost(IP, port);
    tcpClient->flush();
}

