#include "Server.h"
#include "ui_Server.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);
//    QString str_01 = ui->lineEdit_IP->text();
//    quint16 str_02 = ui->lineEdit_port->text().toShort();
    tcpServer->listen(QHostAddress::Any,8080);
    connect(tcpServer,&QTcpServer::newConnection,[=](){
        tcpSocket = tcpServer->nextPendingConnection();
        ui->textEdit->setText("连接成功");

        connect(tcpSocket,&QTcpSocket::readyRead,[=](){
            QByteArray array = tcpSocket->readAll();
            ui->textEdit->append(array);
        });
    });

}

MainWindow::~MainWindow()
{
    delete ui;
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket = nullptr;

}


void MainWindow::on_pushButton_send_clicked()
{
    QString str_03 = ui->textEdit_2->toPlainText();
    tcpSocket->write(str_03.toUtf8().data());
}

