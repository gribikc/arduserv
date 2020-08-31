#include "gr_http_client.h"
#include <gr_logger/gr_logger.h>

//GR_http_client::GR_http_client(int sdscrp) : QTcpSocket(){
//GR_http_client::GR_http_client(int sdscrp) : QTcpSocket(){
GR_http_client::GR_http_client(){

}

void GR_http_client::init(int sdscrp){
    //this->socket=this;
    //this->gr_socket::operator=()
    socket=new gr_TcpSocket();
    socket->setSocketDescriptor(sdscrp);
    //setSocketDescriptor(sdscrp);
    //this->setSocketDescriptor(sdscrp);
    //ip_addr=this->peerAddress().toString();
    //connect(this, &QTcpSocket::disconnected, this, &GR_http_client::disconnected);
    //connect(this, &QTcpSocket::readyRead, this, &GR_http_client::readyRead);
    connect(socket, &gr_socket::disconnected, this, &GR_http_client::disconnected);
    connect(socket, &gr_socket::readyRead, this, &GR_http_client::readyRead);
}
void GR_http_client::init(QWebSocket *pSocket){
    socket=new gr_web_socket();
    connect(socket, &gr_socket::disconnected, this, &GR_http_client::disconnected);
    connect(socket, &gr_socket::readyRead, this, &GR_http_client::readyRead);
    socket->setSocketDescriptor(pSocket);
}
////////////////////////////////
////////////////////////////////
////////////////////////////////
void GR_http_client::readyRead(){
    indata.append(socket->readAll());
    if(hrp_headers_valid==0){
        http_request_parsing();
        if(hrp_headers_valid==1){
            GR_logger::log(this,"Http Request Complite");
            emit requestComplete(this);
        }
    }
    if(hrp_headers_valid==1){
        if(indata.size()>=contentlength){
            indata.remove(0,hrp_del);
            list_param=get_list_param();
            GR_logger::log(this,"Http Data Complete");
            emit dataComplete(this);
        }
    }
}
////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
void GR_http_client::disconnected(){
    GR_logger::log(this,"Http Client Disconnected");
    this->deleteLater();
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void GR_http_client::http_request_parsing(){
    QList<QByteArray> header_line = indata.split( 0x0D );
    QList<QByteArray> split_line;
    QString temp;

    int data_size=indata.size();
    if(data_size>=3 && hrp_del==0){//Ищем конец заголовка
        for(int i=3;i<data_size;i++){
            if(indata[i]==(char)0x0A && indata[i-1]==(char)0x0D && indata[i-2]==(char)0x0A && indata[i-3]==(char)0x0D){
                hrp_del=i+1;//\r\n\r\n -position
            }
        }
    }
    if(hrp_del!=0 && hrp_headers_valid==0){//Если есть признак завершонного заголовка и еще не обрабатывали
        //GET /conf-2009.avi HTTP/1.0
        //Host: example.org
        //Accept: */*
        //User-Agent: Mozilla/4.0 (compatible; MSIE 5.0; Windows 98)
        //Range: bytes=88080384-
        //Referer: http://example.org/
        for(int i=0;i<header_line.size();i++){
            temp=header_line[i];
            if((temp.startsWith("GET ") || temp.startsWith("POST ")) && hrp_headers_valid==0){//startsWith
                hrp_headers.insertMulti("Query",header_line[i]);
                hrp_headers_valid=1;//!!!
            }else if(temp.startsWith("\nContent-Length:")){
                split_line=header_line[i].split(':');
                if(split_line.size()==2){
                    hrp_headers.insertMulti("Content-Length",split_line[1]);
                    contentlength=split_line[1].toInt();
                }
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
int GR_http_client::is_rsw(QString name){
    QString temp=hrp_headers["Query"];
    QStringList list_in_line=temp.split(" ");
    temp=list_in_line[1];
    if( temp==name ){
        return 2;
    }else{
        if( temp.startsWith(name,Qt::CaseInsensitive) ){
            return 1;
        }else{
            return 0;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
QStringList GR_http_client::get_list_param(){
    QString temp=hrp_headers["Query"];
    QStringList list_in_line=temp.split(" ");
    temp=list_in_line[1];
    list_in_line=temp.split("/");
    return list_in_line;
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    void GR_http_client::send_data_header(){
        if(socket->type_of_socket!=1){return;}
        socket->write("HTTP/1.1 200 OK\n");
        socket->write("Content-type: text/plan\n");
        socket->write("Connection: keep-alive\n");
        socket->write("Access-Control-Allow-Origin: *\n");
        socket->write("\n");
        GR_logger::log(this,"Http Send Data header");
    }
    void GR_http_client::send_html_header(){
        if(socket->type_of_socket!=1){return;}
        socket->write("HTTP/1.1 200 OK\n");
        socket->write("Content-type: text/html; charset=utf-8\n");
        socket->write("Connection: keep-alive\n");
        socket->write("Access-Control-Allow-Origin: *\n");
        socket->write("\n");
        GR_logger::log(this,"Http Send HTML header");
    }
    void GR_http_client::send_css_header(){
        if(socket->type_of_socket!=1){return;}
        socket->write("HTTP/1.1 200 OK\n");
        socket->write("Content-type: text/css; charset=utf-8\n");
        socket->write("Connection: keep-alive\n");
        socket->write("Access-Control-Allow-Origin: *\n");
        socket->write("\n");
        GR_logger::log(this,"Http Send CSS header");
    }
    void GR_http_client::send_js_header(){
        if(socket->type_of_socket!=1){return;}
        socket->write("HTTP/1.1 200 OK\n");
        socket->write("Content-type: text/javascript; charset=utf-8\n");
        socket->write("Connection: keep-alive\n");
        socket->write("Access-Control-Allow-Origin: *\n");
        socket->write("\n");
        GR_logger::log(this,"Http Send HTML header");
    }

    void GR_http_client::send_neutral_header(){
        if(socket->type_of_socket!=1){return;}
        socket->write("HTTP/1.1 200 OK\n");
        socket->write("Connection: keep-alive\n");
        socket->write("Access-Control-Allow-Origin: *\n");
        socket->write("\n");
        GR_logger::log(this,"Http Send Neutral header");
    }

