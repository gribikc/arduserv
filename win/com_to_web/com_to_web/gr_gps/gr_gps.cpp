#include "gr_gps.h"

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void gr_gps::init_gps(){
    gps_source=QGeoPositionInfoSource::createDefaultSource(this);
    if (gps_source) {
        gps_source->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
        connect( gps_source, &QGeoPositionInfoSource::positionUpdated, this,&gr_gps::gps_positionnew);
        gps_source->startUpdates();
    }
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/// Virtual ///
   void gr_gps::no_more_client(){
        if (gps_source) {
            gps_source->stopUpdates();
        }
        gps_source->deleteLater();
        this->deleteLater();
        qDebug() << "GPS Close;";
    }
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void gr_gps::gps_positionnew(const QGeoPositionInfo &info){
    QByteArray data;
    QByteArray send_data="";

    send_data+="xdstartjson:{";//info.coordinate().altitude();
        send_data+="\n  \"altitude\":";
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

        send_data+=",\n  \"Timestamp\":";
        //data=QString::number(info.timestamp().toString());
        //data= (data!="nan") ? data : "0";
        send_data+="\""+info.timestamp().toString("dd.MM.yyyy;hh:mm:ss.zzz")+"\"";

    send_data+="\n}:xdstopjson\n";
    send_data_to_client(&send_data);
}
//
//
//
