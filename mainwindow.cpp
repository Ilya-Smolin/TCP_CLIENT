#include "mainwindow.h"
#include "ui_mainwindow.h"

static bool function_invertor;
static uint timer_value_msec = 1500;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << "SETUP...";
    ui->setupUi(this);

    receive_tcp1 = new receive_tcp;
    thread1 = new QThread;
    receive_tcp1->moveToThread(thread1);

    tcp_handler2 = new tcp_handler;
    thread2 = new QThread;
    tcp_handler2->moveToThread(thread2);


    timer = new QTimer(this);
    elapsed_timer = new QElapsedTimer;

//    bool success = connect(this, SIGNAL(send_tcp(const QByteArray)),
//                           tcp_handler2, SLOT(send_tcp(const QByteArray)));

//    Q_ASSERT(success);

    bool success = connect(timer, SIGNAL(timeout()), this, SLOT(update_timer()));

    Q_ASSERT(success);

    success = connect(receive_tcp1, SIGNAL(recieved_to_ui(const QByteArray)),
                      this, SLOT(recieved_tcp_handler(const QByteArray)));

    Q_ASSERT(success);

    success = connect(this, SIGNAL(connect_to_tcp(QString, quint16)),
                      receive_tcp1, SLOT(connect_to_tcp(QString, quint16)));

    Q_ASSERT(success);

    success = connect(this, SIGNAL(connect_to_tcp_recv(QString, quint16)),
                      tcp_handler2, SLOT(connect_to_tcp(QString, quint16)));


    Q_ASSERT(success);

    log_string = new QString;

//    timer->start(1);
//    timer1->start(1);
    elapsed_timer->start();

    thread1->start();
    thread2->start();

    qDebug() << "SETUP FINISHED";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recieved_tcp_handler(const QByteArray ba){
//    ui->plainTextEdit->insertPlainText(ba);
    QString text = QString(ba);
    QTime ct = QTime::currentTime();
    text.append(QString(", %1\n").arg(ct.toString("hh:mm:ss.zzz")));
    log_string->append(text);
    ui->plainTextEdit->insertPlainText(text);
    ui->plainTextEdit->verticalScrollBar()->setValue(INT_MAX);
}

void MainWindow::update_timer(){
//    QTime ct = QTime::currentTime();
//    QString text = ct.toString("hh:mm:ss.zzz");
//    text.append("\n");
//    emit send_tcp(text.toLatin1());
    if(elapsed_timer->elapsed() >= timer_value_msec){
        function_invertor = !function_invertor;
        qDebug() << elapsed_timer->elapsed()<< function_invertor;
        elapsed_timer->start();
    }
}

void MainWindow::on_pushButton_2_clicked(){
    thread1->start();
    thread2->start();
    emit connect_to_tcp(QString("192.168.1.100"), static_cast<quint16>(22800));
    emit connect_to_tcp_recv(QString("192.168.1.100"), static_cast<quint16>(22801));
}



void MainWindow::on_pushButton_clicked(){
//    QTime ct = QTime::currentTime();
//    QFile file(QString("%1.txt").arg(ct.toString("hh:mm")));
    QFile file("log.txt");
    file.open(QIODevice::WriteOnly);
//    file.write(ui->plainTextEdit->toPlainText().toUtf8());
    file.write(log_string->toUtf8());
    file.close();
    qDebug() << "WRITE TO TXT...";
}

