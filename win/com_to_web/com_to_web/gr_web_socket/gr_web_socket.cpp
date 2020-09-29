#include "gr_web_socket.h"

void gr_web_socket::setSocketDescriptor(QWebSocket *sdscrp){
     type_of_socket=2;
     socket=sdscrp;
     if(!socket->isValid()){
        connect(socket, &QWebSocket::connected, this, &gr_web_socket::connected_s);
     }else{
        connected_s();
     }
}

void gr_web_socket::connected_s(){
    //emit this->readyRead();
    indata_s.clear();
    QString falsh_get=socket->resourceName();
    QStringList falsh_get_list=falsh_get.split("/");
    falsh_get="GET ";
    for (int i=3;i<falsh_get_list.size();i++) {
        falsh_get+="/";
        falsh_get+=falsh_get_list.at(i);
    }
    falsh_get+=0x0D;
    falsh_get+=0x0A;
    falsh_get+=0x0D;
    falsh_get+=0x0A;
    indata_s.append(falsh_get);
    emit this->readyRead();
    connect(socket, &QWebSocket::textMessageReceived, this, &gr_web_socket::readyRead_s_txt);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &gr_web_socket::readyRead_s_bin);
    connect(socket, &QWebSocket::disconnected, this, &gr_web_socket::disconnected_s);
    connect(socket, &QWebSocket::aboutToClose, this, &gr_web_socket::disconnected_s);
    connect(socket, &QWebSocket::destroyed, this, &gr_web_socket::disconnected_s);
    emit this->readyRead();
}

void gr_web_socket::readyRead_s_txt(QString message){
    indata_s.append(message);
    emit this->readyRead();
}
void gr_web_socket::readyRead_s_bin(QByteArray message){
    indata_s.append(message);
    emit this->readyRead();
}

void gr_web_socket::disconnected_s(){
    emit disconnected();
    deleteLater();
}


QByteArray gr_web_socket::readAll(){
    QByteArray data=indata_s;
    indata_s.clear();
    return data;
}


void gr_web_socket::write(QByteArray *data){
    //socket.write(*data);
    //QByteArray data2="";
    //data2.append(*data);
    if(chek_valid()){
        socket->sendBinaryMessage(*data);
    }
}
void gr_web_socket::write(const char *data){
    //socket.write(*data);
    //QByteArray data2="";
    //data2.append(*data);
    if(chek_valid()){
        socket->sendTextMessage(data);
    }
}

void gr_web_socket::write(QString *data){
    //socket.write(data);
    if(chek_valid()){
        socket->sendTextMessage(*data);
    }
}

bool gr_web_socket::chek_valid(){
    if(socket->isValid() && socket->state()==QAbstractSocket::ConnectedState){
        return 1;
    }else {
        qDebug() << "WBS error!!!";
        return 0;
    }
}


QAbstractSocket::SocketState gr_web_socket::state(){
    return socket->state();
}

void gr_web_socket::close(){
    socket->close();
}

void gr_web_socket::flush(){
    socket->flush();
}
