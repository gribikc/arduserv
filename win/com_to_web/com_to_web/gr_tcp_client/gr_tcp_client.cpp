#include "gr_tcp_client.h"

gr_tcp_client::gr_tcp_client(QTcpSocket *partner) : QObject(partner){

  gr_tcp_client::partner=partner;
  tcp_s_o=new QTcpSocket(this);
  QString ip=static_cast<GR_http_client *>(partner)->list_param[3].toLocal8Bit();
  int port=static_cast<GR_http_client *>(partner)->list_param[4].toInt();
  tcp_s_o->connectToHost(ip,port,QIODevice::ReadWrite);
  connect(tcp_s_o,&QTcpSocket::readyRead,this,&gr_tcp_client::tcp_readyRead);
  connect(tcp_s_o,&QTcpSocket::connected,this,&gr_tcp_client::tcp_connected);
  connect(tcp_s_o,&QTcpSocket::disconnected,this,&gr_tcp_client::tcp_disconnected);
  connect(partner,&QTcpSocket::disconnected,this,&gr_tcp_client::tcp_disconnected);
}
void gr_tcp_client::tcp_connected(){
    //QByteArray data=static_cast<GR_http_client *>(partner)->list_param[6].toLocal8Bit();
    QByteArray data=static_cast<GR_http_client *>(partner)->indata;
    tcp_s_o->write(data);
}

void gr_tcp_client::tcp_readyRead(){
    partner->write(tcp_s_o->readAll());
}

void gr_tcp_client::tcp_disconnected(){
    partner->deleteLater();
    tcp_s_o->deleteLater();
}
