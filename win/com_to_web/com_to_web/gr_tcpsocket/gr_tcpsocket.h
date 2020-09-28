#ifndef GR_TCPSOCKET_H
#define GR_TCPSOCKET_H

#include <QTcpSocket>
#include "gr_socket/gr_socket.h"

class gr_TcpSocket : public gr_socket{
    Q_OBJECT
public:
    gr_TcpSocket(QObject *parent = nullptr):gr_socket(parent){

    }

    QTcpSocket *socket;
    void write(QByteArray *data);//данные из устройства отправляем в сокет
    void write(const char *data);
    void write(QString *data);
    QByteArray readAll();
    void setSocketDescriptor(QTcpSocket *sdscrp);
    QAbstractSocket::SocketState state();
    void close();
    void flush();
    void readyRead_s();
    void disconnected_s();
    void connectNotify(const QMetaMethod &signal){
        if (signal == QMetaMethod::fromSignal(&gr_TcpSocket::readyRead)) {
            if(socket->bytesAvailable()>0){
                qDebug()<<"Socket Error!!! bytesAvailable";
                emit readyRead();
            }
        }
    }
};

#endif // GR_TCPSOCKET_H
