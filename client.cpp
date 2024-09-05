#include "client.h"
#include "ui_client.h"
#include <qhostaddress.h>
Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    tcpSocket = nullptr;
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,&QTcpSocket::connected,[=](){
        ui->textEdit_text->setText("连接成功");

    });

    connect(tcpSocket,&QTcpSocket::readyRead,[=](){
        QByteArray array = tcpSocket->readAll();
        ui->textEdit_text->append(array);
    });
}

Client::~Client()
{
    delete ui;
}

void Client::on_pushButton_connect_clicked()
{
    QString IP = ui->lineEdit_IP->text();
    quint16 port = ui->lineEdit_port->text().toInt();

    tcpSocket->connectToHost(QHostAddress(IP),port);

}


void Client::on_pushButton_close_clicked()
{   if(nullptr == tcpSocket){
        return;
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket = nullptr;
}

void Client::on_pushButton_send_clicked()
{
    QString str = ui->textEdit_send->toPlainText();
    tcpSocket->write(str.toUtf8().data());
}

