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
    //
    disconnect(partner->socket,&gr_socket::disconnected,nullptr,nullptr);
    connect(partner->socket, &gr_socket::disconnected, this, [&](){
        timer->stop();
        timer->deleteLater();
        deleteLater();
    });
    connect(partner->socket, &gr_socket::readyRead, this,  [&](){
        //QByteArray data;//!!!WTF
        //data=partner->socket->readAll();
    });
}

void data_generator::timer_event(){
    QString text;
    if(traffic_type=="cnt"){
        text=type_cnt(traffic_size);
    }else{
        text=type_none(traffic_size);
    }
    partner->socket->write(&text);
    cnt++;
}

QString data_generator::type_none(int size){
    QString text;
    text="Hello world. I am data generator!:"+QString::number(cnt)+"\n\r";
    return text;
}

QString data_generator::type_cnt(int size){
    QString text="";
    for (int i=0;i<size;i++) {
        text+=QString::number(i);
    }
    return text;
}
