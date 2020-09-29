#include "data_generator.h"

data_generator::data_generator(GR_http_client *partner) : QObject(nullptr){
    //sys/gen/timer_ms/type/size
    data_generator::partner=partner;
    QStringList list_param=partner->list_param;
    timer_period=(list_param.size() > 3) ? list_param[3].toInt()>0  ? list_param[3].toInt() : 1000      : 1000;
    traffic_type=(list_param.size() > 4) ? list_param[4]!=""        ? list_param[4]         : "none"    : "none";
    traffic_size=(list_param.size() > 5) ? list_param[5].toInt()>0  ? list_param[5].toInt() : 1         : 1;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &data_generator::timer_event);
    timer->start(timer_period);

    disconnect(partner->socket,nullptr,nullptr,nullptr);
    connect(partner->socket, &gr_socket::disconnected, this, [&](){
        timer->stop();
        timer->deleteLater();
        deleteLater();
    });
    connect(partner->socket, &gr_socket::readyRead, this,  [&](){
        partner->socket->readAll();
    });
}

void data_generator::timer_event(){
    static int cnt=0;
    QString text;
    QByteArray ba;
    text="Hello world. I am data generator!:"+QString::number(cnt)+"\n\r";
    ba=text.toUtf8();
    partner->socket->write(&text);
    cnt++;
}
