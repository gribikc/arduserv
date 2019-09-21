#include "gr_sensor.h"

//GR_sensor::GR_sensor(){}

void GR_sensor::no_more_client(){
    rot_sensor->deleteLater();
    acc_sensor->deleteLater();
    mag_sensor->deleteLater();
    ambl_sensor->deleteLater();
    this->deleteLater();
}

void GR_sensor::sensor_start(){
    //QAccelerometer
    init_acc();//+
    //QGyroscope
    //Light Sensor
    //QMagnetometer
    init_mag();//+
    //QPressureFilter
    //QRotationSensor
    //init_rot();//!!!
    //QAmbientLightSensor//!!!
    //init_ambl();//!!!
}

void GR_sensor::read_changed(QString prefix){
    static int signal_cnt=0;
    QByteArray data;
    QByteArray send_data="";
    //qDebug() << "SENS DATA SEND;";

    QSensorReading *read;
    QObject * object = QObject::sender();
    QSensor * sens=static_cast<QSensor *>(object);

    signal_cnt++;
    if(signal_cnt>200){
        signal_cnt=0;
        read=sens->reading();
        qreal x_rot = read->property("x").value<qreal>();
        qreal y_rot = read->property("y").value<qreal>();
        qreal z_rot = read->property("z").value<qreal>();
        //qreal w_rot = read->property("3").value<qreal>();
        //sensor.hasZ();

        send_data+="xdstartjson:{";//info.coordinate().altitude();
            send_data+="\n   \"type\":\"";
            send_data+=prefix;
            send_data+="\",\n   \"X\":";
            data=QString::number(x_rot).toLocal8Bit();
            data= (data!="nan") ? data : "0";
            send_data+=data;
            send_data+=",\n   \"Y\":";
            data=QString::number(y_rot).toLocal8Bit();
            data= (data!="nan") ? data : "0";
            send_data+=data;
            send_data+=",\n   \"Z\":";
            data=QString::number(z_rot).toLocal8Bit();
            data= (data!="nan") ? data : "0";
            send_data+=data;
        send_data+="\n}:xdstopjson\n";
        send_data_to_client(&send_data);
    }
}
void GR_sensor::init_acc(){
    if(acc_sensor){
        qDebug() << "SENS FIND";
    }else{
        qDebug() << "SENS NOT FIND";
    }
    //sensor->stop();
    acc_sensor->setAxesOrientationMode(QSensor::UserOrientation);
    acc_sensor->setUserOrientation(90);
    acc_sensor->setAccelerationMode(QAccelerometer::Combined);
    acc_sensor->setDataRate(1);
    acc_sensor->setBufferSize(1);
    acc_sensor->setSkipDuplicates(0);
    acc_sensor->setAlwaysOn(true);
    acc_sensor->setActive(true);

    connect(acc_sensor,&QAccelerometer::readingChanged,this,[=](){ read_changed("acc"); });
    //connect(sensor,&QRotationSensor::readingChanged,this,&GR_sensor::read_changed);
    acc_sensor->start();

    //qDebug() << "isFeatureSupported " << sensor->isFeatureSupported(QSensor::AxesOrientation);
}
void GR_sensor::init_mag(){
    if(mag_sensor){
        qDebug() << "SENS FIND";
    }else{
        qDebug() << "SENS NOT FIND";
    }
    //sensor->stop();
    mag_sensor->setAxesOrientationMode(QSensor::UserOrientation);
    mag_sensor->setUserOrientation(90);
    mag_sensor->setDataRate(1);
    mag_sensor->setBufferSize(1);
    mag_sensor->setSkipDuplicates(0);
    mag_sensor->setAlwaysOn(true);
    mag_sensor->setActive(true);

    //[=](){ this->someSlot(); }
    connect(mag_sensor,&QMagnetometer::readingChanged,this,[=](){ read_changed("mag"); });
    mag_sensor->start();
}
void GR_sensor::init_ambl(){
    if(ambl_sensor){
        qDebug() << "SENS FIND";
    }else{
        qDebug() << "SENS NOT FIND";
    }
    //sensor->stop();
    ambl_sensor->setAxesOrientationMode(QSensor::UserOrientation);
    ambl_sensor->setUserOrientation(90);
    ambl_sensor->setDataRate(1);
    ambl_sensor->setBufferSize(1);
    ambl_sensor->setSkipDuplicates(0);
    ambl_sensor->setAlwaysOn(true);
    ambl_sensor->setActive(true);

    //[=](){ this->someSlot(); }
    connect(ambl_sensor,&QAmbientLightSensor::readingChanged,this,[=](){ read_changed("ambl"); });
    ambl_sensor->start();
    qDebug()<<"amb:";
    qDebug()<<ambl_sensor->reading()->value(0).value<qreal>();
    qDebug()<<ambl_sensor->reading()->value(1).value<qreal>();
}

void GR_sensor::init_rot(){
    if(rot_sensor){
        qDebug() << "SENS FIND";
    }else{
        qDebug() << "SENS NOT FIND";
    }
    //sensor->stop();
    rot_sensor->setAxesOrientationMode(QSensor::UserOrientation);
    rot_sensor->setUserOrientation(90);
    rot_sensor->setDataRate(1);
    rot_sensor->setBufferSize(1);
    rot_sensor->setSkipDuplicates(0);
    rot_sensor->setAlwaysOn(true);
    rot_sensor->setActive(true);

    connect(rot_sensor,&QRotationSensor::readingChanged,this,[=](){ read_changed("rot"); });
    rot_sensor->start();
    qDebug()<<"rot:";
}
