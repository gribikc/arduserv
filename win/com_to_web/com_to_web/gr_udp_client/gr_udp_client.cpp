#include "gr_udp_client.h"

gr_udp_client::gr_udp_client(QTcpSocket *partner) : QObject(partner){
    gr_udp_client::partner=partner;

    /////
        QString query="30 33 02 01 01 04 06 70 75 62 6c 69 63 a0 26 02 04 5d d6 91 4a 02 "
                      "01 00 02 01 00 30 18 30 16 06 12 2b 06 01 04 01 81 b7 58 87 69 70 "
                      "50 bf 10 81 53 01 00 05 00";
        QStringList query_l=query.split(" ");
        QByteArray query_b;
        for(int i=0;i<query_l.length();i++){
            QString temp=query_l.at(i);
            QByteArray temp2=temp.toLocal8Bit();
            query_b.append( QByteArray::fromHex(temp2) );
        }
    /////

    udpSocket = new QUdpSocket(this);
    connect(udpSocket, &QUdpSocket::readyRead,
            this, &gr_udp_client::udp_readyRead);
    udpSocket->writeDatagram(query_b,QHostAddress("172.18.26.107"), 161);
}

void gr_udp_client::udp_readyRead(){
    while (udpSocket->hasPendingDatagrams()) {
        auto datagram = udpSocket->receiveDatagram();
        QString test="Hello World!!!";
        QByteArray test2=test.toLocal8Bit();
        partner->write(test2);//datagram.data());
        partner->deleteLater();
        udpSocket->deleteLater();
    }
}
