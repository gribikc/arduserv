#include "gr_gps.h"
#include "gr_logger/gr_logger.h"
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void gr_gps::init_gps(){
    gps_source=QGeoPositionInfoSource::createDefaultSource(this);
    if (gps_source) {
        gps_source->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
        connect( gps_source, &QGeoPositionInfoSource::positionUpdated, this,&gr_gps::gps_positionnew);
        gps_source->setUpdateInterval(1000);
        gps_source->startUpdates();
        GR_logger::log(this,"GPS Init");
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
        GR_logger::log(this,"GPS Close");
    }
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
QString gr_gps::gps_adder_par(QString addr,QString name, QString param){
    QString ret="";
    QString temp="";
    ret+=addr+"\n  \""+name+"\":";
    ret+=(param!="nan") ? param : "0";
    return ret;//str_data+=gps_adder_par(",","",);
}

void gr_gps::gps_positionnew(const QGeoPositionInfo &info){
    QByteArray send_data="";
    QString str_data="";

    send_data+=static_cast<QString>("xdstartjson:").toUtf8();
    send_data_to_client(&send_data);

    str_data="{";
        str_data+=gps_adder_par("",     "altitude",             QString::number(info.coordinate().altitude()));
        str_data+=gps_adder_par(",",    "isValid",              QString::number(info.coordinate().isValid()));
        str_data+=gps_adder_par(",",    "latitude",             QString::number(info.coordinate().latitude(),'g',10));
        str_data+=gps_adder_par(",",    "longitude",            QString::number(info.coordinate().longitude(),'g',10));
        str_data+=gps_adder_par(",",    "GroundSpeed",          QString::number(info.attribute(QGeoPositionInfo::GroundSpeed)));
        str_data+=gps_adder_par(",",    "Direction",            QString::number(info.attribute(QGeoPositionInfo::Direction)));
        str_data+=gps_adder_par(",",    "VerticalSpeed",        QString::number(info.attribute(QGeoPositionInfo::VerticalSpeed)));
        str_data+=gps_adder_par(",",    "MagneticVariation",    QString::number(info.attribute(QGeoPositionInfo::MagneticVariation)));
        str_data+=gps_adder_par(",",    "HorizontalAccuracy",   QString::number(info.attribute(QGeoPositionInfo::HorizontalAccuracy)));
        str_data+=gps_adder_par(",",    "VerticalAccuracy",     QString::number(info.attribute(QGeoPositionInfo::VerticalAccuracy)));
        str_data+=gps_adder_par(",",    "Timestamp",                       "\""+info.timestamp().toString("dd.MM.yyyy;hh:mm:ss.zzz")+"\"");
    str_data+="\n}";
    send_data=str_data.toUtf8();
    send_data_to_client(&send_data);

    send_data=static_cast<QString>(":xdstopjson\n").toUtf8();
    send_data_to_client(&send_data);
}
//
//
//
