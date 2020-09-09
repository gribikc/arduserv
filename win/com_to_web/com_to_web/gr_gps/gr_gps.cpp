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
    //QByteArray data;
    QByteArray send_data="";
    QString str_data="";

    send_data+="xdstartjson:";//info.coordinate().altitude();
    send_data_to_client(&send_data);

    str_data="{";
        //str_data+="\n  \"altitude\":";
        //str_temp=QString::number(info.coordinate().altitude());
        //data= (data!="nan") ? data : "0";
        //send_data+=data;
        str_data+=gps_adder_par("","altitude",QString::number(info.coordinate().altitude()));

        //send_data+=",\n  \"isValid\":";
        //str_temp=QString::number(info.coordinate().isValid());
        //data= (data!="nan") ? data : "0";
        //send_data+=data;
        str_data+=gps_adder_par(",","isValid",QString::number(info.coordinate().isValid()));

        //send_data+=",\n  \"latitude\":";
        //str_temp=QString::number(info.coordinate().latitude(),'g',10);
        //data= (data!="nan") ? data : "0";
        //send_data+=data;
        str_data+=gps_adder_par(",","latitude",QString::number(info.coordinate().latitude(),'g',10));

        //send_data+=",\n  \"longitude\":";
        //str_temp=QString::number(info.coordinate().longitude(),'g',10);
        //data= (data!="nan") ? data : "0";
        //send_data+=data;
        str_data+=gps_adder_par(",","longitude",QString::number(info.coordinate().longitude(),'g',10));

        //send_data+=",\n  \"GroundSpeed\":";
        //str_temp=QString::number(info.attribute(QGeoPositionInfo::GroundSpeed));
        //data= (data!="nan") ? data : "0";
        //send_data+=data;
        str_data+=gps_adder_par(",","GroundSpeed",QString::number(info.attribute(QGeoPositionInfo::GroundSpeed)));

        //send_data+=",\n  \"Direction\":";
        //str_temp=QString::number(info.attribute(QGeoPositionInfo::Direction));
        //data= (data!="nan") ? data : "0";
        //send_data+=data;
        str_data+=gps_adder_par(",","Direction",QString::number(info.attribute(QGeoPositionInfo::Direction)));

        //send_data+=",\n  \"VerticalSpeed\":";
        //str_temp=QString::number(info.attribute(QGeoPositionInfo::VerticalSpeed));
        //data= (data!="nan") ? data : "0";
        //send_data+=data;
        str_data+=gps_adder_par(",","VerticalSpeed",QString::number(info.attribute(QGeoPositionInfo::VerticalSpeed)));

        //send_data+=",\n  \"MagneticVariation\":";
        //str_temp=QString::number(info.attribute(QGeoPositionInfo::MagneticVariation));
        //data= (data!="nan") ? data : "0";
        //send_data+=data;
        str_data+=gps_adder_par(",","MagneticVariation",QString::number(info.attribute(QGeoPositionInfo::MagneticVariation)));

        //send_data+=",\n  \"HorizontalAccuracy\":";
        //str_temp=QString::number(info.attribute(QGeoPositionInfo::HorizontalAccuracy));
        //data= (data!="nan") ? data : "0";
        //send_data+=data;
        str_data+=gps_adder_par(",","HorizontalAccuracy",QString::number(info.attribute(QGeoPositionInfo::HorizontalAccuracy)));

        //send_data+=",\n  \"VerticalAccuracy\":";
        //str_temp=QString::number(info.attribute(QGeoPositionInfo::VerticalAccuracy));
        //data= (data!="nan") ? data : "0";
        //send_data+=data;
        str_data+=gps_adder_par(",","VerticalAccuracy",QString::number(info.attribute(QGeoPositionInfo::VerticalAccuracy)));

        //send_data+=",\n  \"Timestamp\":";
        ////data=QString::number(info.timestamp().toString());
        ////data= (data!="nan") ? data : "0";
        //send_data+="\""+info.timestamp().toString("dd.MM.yyyy;hh:mm:ss.zzz")+"\"";
        str_data+=gps_adder_par(",","Timestamp",info.timestamp().toString("dd.MM.yyyy;hh:mm:ss.zzz"));

    str_data+="\n}";
    send_data=str_data.toUtf8();
    send_data_to_client(&send_data);

    send_data=":xdstopjson\n";
    send_data_to_client(&send_data);
}
//
//
//
