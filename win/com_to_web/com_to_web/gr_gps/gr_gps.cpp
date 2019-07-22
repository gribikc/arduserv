#include "gr_gps.h"

//
//
////////////////////////////////////////////////////////////////////////////
void gr_gps::gps_add_listener(QTcpSocket *socket_point){
    socket=socket_point;
    gps_source=QGeoPositionInfoSource::createDefaultSource(this);
    if ( gps_source) {
        gps_source->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
        connect( gps_source, &QGeoPositionInfoSource::positionUpdated, this,&gr_gps::gps_positionnew);
        gps_source->startUpdates();
    }
}
///////////////////////////////////////////////////////////
void gr_gps::gps_positionnew(const QGeoPositionInfo &info){
    //qDebug() << &info;
    //socket->write(QString::number(info.coordinate().altitude()).toLocal8Bit());
    //socket->write(", ");
    socket->write("xdstartjson:{");//info.coordinate().altitude();
        socket->write("\n   \"altitude\":");
        socket->write(QString::number(info.coordinate().altitude()).toLocal8Bit());
        socket->write(",\n  \"isValid\":");
        socket->write(QString::number(info.coordinate().isValid()).toLocal8Bit());
        socket->write(",\n  \"latitude\":");
        socket->write(QString::number(info.coordinate().latitude(),'g',10).toLocal8Bit());
        socket->write(",\n  \"longitude\":");
        socket->write(QString::number(info.coordinate().longitude(),'g',10).toLocal8Bit());
        socket->write(",\n  \"GroundSpeed\":");
        socket->write(QString::number(info.attribute(QGeoPositionInfo::GroundSpeed)).toLocal8Bit());
        socket->write(",\n  \"Direction\":");
        socket->write(QString::number(info.attribute(QGeoPositionInfo::Direction)).toLocal8Bit());
        socket->write(",\n  \"VerticalSpeed\":");
        socket->write(QString::number(info.attribute(QGeoPositionInfo::VerticalSpeed)).toLocal8Bit());
        socket->write(",\n  \"MagneticVariation\":");
        socket->write(QString::number(info.attribute(QGeoPositionInfo::MagneticVariation)).toLocal8Bit());
        socket->write(",\n  \"HorizontalAccuracy\":");
        socket->write(QString::number(info.attribute(QGeoPositionInfo::HorizontalAccuracy)).toLocal8Bit());
        socket->write(",\n  \"VerticalAccuracy\":");
        socket->write(QString::number(info.attribute(QGeoPositionInfo::VerticalAccuracy)).toLocal8Bit());
    socket->write("\n}xdstopjson:\n");
}
//
//
//
