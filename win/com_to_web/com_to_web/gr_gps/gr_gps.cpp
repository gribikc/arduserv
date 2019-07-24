#include "gr_gps.h"

//
//
////////////////////////////////////////////////////////////////////////////
void gr_gps::gps_add_listener(QTcpSocket *socket_point){
    socket=socket_point;
    socket_listener.append(socket_point);

    if (!gps_source) {
        gps_source=QGeoPositionInfoSource::createDefaultSource(this);
        if (gps_source) {
            gps_source->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
            connect( gps_source, &QGeoPositionInfoSource::positionUpdated, this,&gr_gps::gps_positionnew);
            gps_source->startUpdates();
        }else{
            socket_point->close();
        }
    }else{
        gps_source->startUpdates();
    }
}
///////////////////////////////////////////////////////////
void gr_gps::gps_positionnew(const QGeoPositionInfo &info){
    //qDebug() << &info;
    //socket->write(QString::number(info.coordinate().altitude()).toLocal8Bit());
    //socket->write(", ");
    QByteArray data;
    QByteArray send_data="";

    if(socket_listener.size()==0){
        gps_source->stopUpdates();
    }

    send_data+="xdstartjson:{";//info.coordinate().altitude();
        send_data+="\n   \"altitude\":";
        data=QString::number(info.coordinate().altitude()).toLocal8Bit();
        data= (data!="nan") ? data : "0";
        send_data+=data;

        send_data+=",\n  \"isValid\":";
        data=QString::number(info.coordinate().isValid()).toLocal8Bit();
        data= (data!="nan") ? data : "0";
        send_data+=data;

        send_data+=",\n  \"latitude\":";
        data=QString::number(info.coordinate().latitude(),'g',10).toLocal8Bit();
        data= (data!="nan") ? data : "0";
        send_data+=data;

        send_data+=",\n  \"longitude\":";
        data=QString::number(info.coordinate().longitude(),'g',10).toLocal8Bit();
        data= (data!="nan") ? data : "0";
        send_data+=data;

        send_data+=",\n  \"GroundSpeed\":";
        data=QString::number(info.attribute(QGeoPositionInfo::GroundSpeed)).toLocal8Bit();
        data= (data!="nan") ? data : "0";
        send_data+=data;

        send_data+=",\n  \"Direction\":";
        data=QString::number(info.attribute(QGeoPositionInfo::Direction)).toLocal8Bit();
        data= (data!="nan") ? data : "0";
        send_data+=data;

        send_data+=",\n  \"VerticalSpeed\":";
        data=QString::number(info.attribute(QGeoPositionInfo::VerticalSpeed)).toLocal8Bit();
        data= (data!="nan") ? data : "0";
        send_data+=data;

        send_data+=",\n  \"MagneticVariation\":";
        data=QString::number(info.attribute(QGeoPositionInfo::MagneticVariation)).toLocal8Bit();
        data= (data!="nan") ? data : "0";
        send_data+=data;

        send_data+=",\n  \"HorizontalAccuracy\":";
        data=QString::number(info.attribute(QGeoPositionInfo::HorizontalAccuracy)).toLocal8Bit();
        data= (data!="nan") ? data : "0";
        send_data+=data;

        send_data+=",\n  \"VerticalAccuracy\":";
        data=QString::number(info.attribute(QGeoPositionInfo::VerticalAccuracy)).toLocal8Bit();
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

        /*socket->write("xdstartjson:{");//info.coordinate().altitude();
            socket->write("\n   \"altitude\":");
            data=QString::number(info.coordinate().altitude()).toLocal8Bit();
            data= (data!="nan") ? data : "0";
            socket->write(data);

            socket->write(",\n  \"isValid\":");
            data=QString::number(info.coordinate().isValid()).toLocal8Bit();
            data= (data!="nan") ? data : "0";
            socket->write(data);

            socket->write(",\n  \"latitude\":");
            data=QString::number(info.coordinate().latitude(),'g',10).toLocal8Bit();
            data= (data!="nan") ? data : "0";
            socket->write(data);

            socket->write(",\n  \"longitude\":");
            data=QString::number(info.coordinate().longitude(),'g',10).toLocal8Bit();
            data= (data!="nan") ? data : "0";
            socket->write(data);

            socket->write(",\n  \"GroundSpeed\":");
            data=QString::number(info.attribute(QGeoPositionInfo::GroundSpeed)).toLocal8Bit();
            data= (data!="nan") ? data : "0";
            socket->write(data);

            socket->write(",\n  \"Direction\":");
            data=QString::number(info.attribute(QGeoPositionInfo::Direction)).toLocal8Bit();
            data= (data!="nan") ? data : "0";
            socket->write(data);

            socket->write(",\n  \"VerticalSpeed\":");
            data=QString::number(info.attribute(QGeoPositionInfo::VerticalSpeed)).toLocal8Bit();
            data= (data!="nan") ? data : "0";
            socket->write(data);

            socket->write(",\n  \"MagneticVariation\":");
            data=QString::number(info.attribute(QGeoPositionInfo::MagneticVariation)).toLocal8Bit();
            data= (data!="nan") ? data : "0";
            socket->write(data);

            socket->write(",\n  \"HorizontalAccuracy\":");
            data=QString::number(info.attribute(QGeoPositionInfo::HorizontalAccuracy)).toLocal8Bit();
            data= (data!="nan") ? data : "0";
            socket->write(data);

            socket->write(",\n  \"VerticalAccuracy\":");
            data=QString::number(info.attribute(QGeoPositionInfo::VerticalAccuracy)).toLocal8Bit();
            data= (data!="nan") ? data : "0";
            socket->write(data);
        socket->write("\n}:xdstopjson\n");*/
}
//
//
//
