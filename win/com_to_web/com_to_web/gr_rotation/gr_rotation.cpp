#include "gr_rotation.h"

//
//
////////////////////////////////////////////////////////////////////////////
void gr_rotation::add_listener(QTcpSocket *socket_point){
    socket_listener.append(socket_point);

    if(sensor){
        qDebug() << "ROT FIND";
    }else{
        qDebug() << "ROT NOT FIND";
    }
    sensor->stop();
    sensor->setAxesOrientationMode(QSensor::UserOrientation);
    sensor->setUserOrientation(90);
    //sensor->setDataRate(100);
    //sensor->setBufferSize(1000);
    //sensor->setSkipDuplicates(0);
    sensor->setAlwaysOn(true);
    sensor->setActive(true);

    //connect(sensor,&QAccelerometer::readingChanged,this,&gr_rotation::read_changed);
    connect(sensor,&QRotationSensor::readingChanged,this,&gr_rotation::read_changed);
    sensor->start();
    qreal test=sensor->reading()->x();

    qDebug() << "isFeatureSupported " << sensor->isFeatureSupported(QSensor::AxesOrientation);
}
///////////////////////////////////////////////////////////
void gr_rotation::read_changed(){
    QByteArray data;
    QByteArray send_data="";

    //if(socket_listener.size()==0){
    //    gps_source->stopUpdates();
    //}
    QSensorReading *read;

    read=sensor->reading();
    qreal x_rot = read->property("x").value<qreal>();
    qreal y_rot = read->property("y").value<qreal>();
    qreal z_rot = read->property("z").value<qreal>();
    qreal w_rot = read->property("3").value<qreal>();
    //sensor.hasZ();

    send_data+="xdstartjson:{";//info.coordinate().altitude();
        send_data+="\n   \"X\":";
        data=QString::number(x_rot).toLocal8Bit();
        data= (data!="nan") ? data : "0";
        send_data+=data;


    send_data+="\n}:xdstopjson\n";

    for(int i=0;i<socket_listener.size();i++){
        if( socket_listener.at(i)->state() != QAbstractSocket::UnconnectedState ){
            socket_listener.at(i)->write(send_data);
        }else{
            socket_listener.removeAt(i);
            i--;
        }
    }
}
//

