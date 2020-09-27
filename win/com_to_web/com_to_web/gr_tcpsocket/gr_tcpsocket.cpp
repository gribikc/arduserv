#include "gr_tcpsocket.h"

/*gr_TcpSocket::gr_TcpSocket(QObject *parent) : gr_socket(parent)
{

}*/

void gr_TcpSocket::setSocketDescriptor(qintptr sdscrp){
     type_of_socket=1;
     socket.setSocketDescriptor(sdscrp);
     connect(&socket, &QTcpSocket::disconnected, this, &gr_TcpSocket::disconnected_s);
     connect(&socket, &QTcpSocket::readyRead, this, &gr_TcpSocket::readyRead_s);
     emit this->readyRead();
     //Ex
     //QMetaMethod readyRead = QMetaMethod::fromSignal(&QTcpSocket::readyRead);
     //connect(this, readyRead,this, [=](){ qDebug()<<"DADADA!!!";}     );
     //disconnect(this,QMetaMethod::fromSignal(&gr_TcpSocket::readyRead),nullptr,nullptr);
}

void gr_TcpSocket::readyRead_s(){
    emit this->readyRead();
}

void gr_TcpSocket::disconnected_s(){
    emit disconnected();
}

QByteArray gr_TcpSocket::readAll(){
    return socket.readAll();
}

void gr_TcpSocket::write(QByteArray *data){
    socket.write(*data);
}

void gr_TcpSocket::write(QString *data){
    QByteArray a;
    a.append(*data);
    socket.write(a);
}

void gr_TcpSocket::write(const char *data){
    socket.write(data);
}

QAbstractSocket::SocketState gr_TcpSocket::state(){
    return socket.state();
}

void gr_TcpSocket::close(){
    socket.close();
}

void gr_TcpSocket::flush(){
    socket.flush();
}
