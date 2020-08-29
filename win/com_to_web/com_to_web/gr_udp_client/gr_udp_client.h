#ifndef GR_UDP_CLIENT_H
#define GR_UDP_CLIENT_H

#include <QObject>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QByteArray>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
//#include <QNetworkDatagram>//!!!
#include <gr_http_client/gr_http_client.h>

class gr_udp_client : public QObject
{
    Q_OBJECT
public:
    explicit gr_udp_client(GR_http_client *partner = nullptr);

    QUdpSocket *udpSocket;
    GR_http_client* partner;

        void udp_readyRead();

signals:
    //void udp_connected();
    //void udp_readyRead();
    //void udp_disconnected();
};

#endif // GR_UDP_CLIENT_H
