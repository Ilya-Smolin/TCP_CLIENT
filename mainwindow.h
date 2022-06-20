#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "receive_tcp.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void send_tcp(const QByteArray ba);

    void connect_to_tcp(QString IP, quint16 port);

    void connect_to_tcp_recv(QString IP, quint16 port);

public slots:
    void recieved_tcp_handler(const QByteArray ba);

    void update_timer();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QThread *thread1, *thread2;

    tcp_handler *tcp_handler2;

    receive_tcp *receive_tcp1;

    QTimer *timer;

    QString *log_string;

    QElapsedTimer *elapsed_timer;
};

#endif // MAINWINDOW_H
