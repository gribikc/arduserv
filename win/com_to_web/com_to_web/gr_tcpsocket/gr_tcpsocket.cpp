#include "gr_tcpsocket.h"

/*gr_TcpSocket::gr_TcpSocket(QObject *parent) : gr_socket(parent)
{

}*/

void gr_TcpSocket::setSocketDescriptor(int sdscrp){
     socket.setSocketDescriptor(sdscrp);
     connect(&socket, &QTcpSocket::disconnected, this, &gr_TcpSocket::disconnected_s);
     connect(&socket, &QTcpSocket::readyRead, this, &gr_TcpSocket::readyRead_s);
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