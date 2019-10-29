#ifndef GR_TCP_CLIENT_H
#define GR_TCP_CLIENT_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <gr_http_client/gr_http_client.h>

class gr_tcp_client : public QObject
{
    Q_OBJECT
public:
    explicit gr_tcp_client(QTcpSocket *partner = nullptr);


    QTcpSocket* tcp_s_o;
    QTcpSocket* partner;

    void tcp_connected();
    void tcp_readyRead();
    void tcp_disconnected();
signals:

public slots:
};

#endif // GR_TCP_CLIENT_H
