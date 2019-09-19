#include "gr_sensor.h"

//GR_sensor::GR_sensor(){}

void GR_sensor::no_more_client(){

}

void GR_sensor::sensor_start(){
    if(sensor){
        qDebug() << "SENS FIND";
    }else{
        qDebug() << "SENS NOT FIND";
    }
    sensor->stop();
    sensor->setAxesOrientationMode(QSensor::UserOrientation);
    sensor->setUserOrientation(90);
    ////sensor->setAccelerationMode(QAccelerometer::Combined);
    sensor->setDataRate(100);
    sensor->setBufferSize(1000);
    sensor->setSkipDuplicates(0);
    sensor->setAlwaysOn(true);
    sensor->setActive(true);

    connect(sensor,&QAccelerometer::readingChanged,this,&GR_sensor::read_changed);
    //connect(sensor,&QRotationSensor::readingChanged,this,&GR_sensor::read_changed);
    sensor->start();
    //qreal test=sensor->reading()->x();
    qDebug() << sensor->dataRate();
    qDebug() << sensor->availableDataRates();
    qDebug() << sensor->start();
    qDebug() << sensor->isConnectedToBackend();
    qDebug() << sensor->isActive();
    //qreal test=sensor->reading()->x();

    //qDebug() << "isFeatureSupported " << sensor->isFeatureSupported(QSensor::AxesOrientation);
}

void GR_sensor::read_changed(){
    QByteArray data;
    QByteArray send_data="";
    qDebug() << "SENS DATA SEND;";

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
    send_data_to_client(&send_data);
}
