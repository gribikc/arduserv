#ifndef GR_WEB_SOCKET_H
#define GR_WEB_SOCKET_H


#include <QWebSocket>
#include "gr_socket/gr_socket.h"

class gr_web_socket : public gr_socket{
    Q_OBJECT
public:
    gr_web_socket(QObject *parent = nullptr):gr_socket(parent){

    }

    QWebSocket *socket;
    QByteArray indata_s;
    void write(QByteArray *data);//данные из устройства отправляем в сокет
    void write(const char *data);
    void write(QString *data);
    QByteArray readAll();
    void setSocketDescriptor(qintptr sdscrp){}
    void setSocketDescriptor(QWebSocket *sdscrp);
    QAbstractSocket::SocketState state();
    void close();
    void flush();
    void readyRead_s_txt(QString message);
    void readyRead_s_bin(QByteArray message);
    void disconnected_s();

    void connected_s();
    bool chek_valid();
};

#endif // GR_WEB_SOCKET_H
