#include "gr_tcp_client.h"

gr_tcp_client::gr_tcp_client(GR_http_client *partner) : QObject(nullptr){

  gr_tcp_client::partner=partner;
  tcp_s_o=new QTcpSocket(this);
  QString ip=static_cast<GR_http_client *>(partner)->list_param[4].toLocal8Bit();
  int port=static_cast<GR_http_client *>(partner)->list_param[5].toInt();
  tcp_s_o->connectToHost(ip,port,QIODevice::ReadWrite);
  connect(tcp_s_o,&QTcpSocket::readyRead,this,&gr_tcp_client::tcp_readyRead);
  connect(tcp_s_o,&QTcpSocket::bytesWritten,this,&gr_tcp_client::tcp_bytesWritten);
  connect(tcp_s_o,&QTcpSocket::connected,this,&gr_tcp_client::tcp_connected);
  connect(tcp_s_o,&QTcpSocket::disconnected,this,&gr_tcp_client::tcp_disconnected);
  connect(partner->socket,&gr_socket::disconnected,this,&gr_tcp_client::tcp_disconnected);
}
void gr_tcp_client::tcp_connected(){
    //QByteArray data=static_cast<GR_http_client *>(partner)->list_param[6].toLocal8Bit();
    QByteArray data=static_cast<GR_http_client *>(partner)->indata;
    tcp_s_o->write(data);
}

void gr_tcp_client::tcp_bytesWritten(){
    QString mode;
    if(static_cast<GR_http_client *>(partner)->list_param[3]=='w'){
        gr_tcp_client::tcp_disconnected();
    }
}

void gr_tcp_client::tcp_readyRead(){
    partner->socket->write(tcp_s_o->readAll());
}

void gr_tcp_client::tcp_disconnected(){
    partner->socket->deleteLater();
    tcp_s_o->deleteLater();
}

