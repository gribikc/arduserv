#ifndef GR_GPS_H
#define GR_GPS_H

#include "gr_data_source/gr_data_source.h"
#include <QGeoSatelliteInfo>
#include <QGeoCoordinate>
#include <QGeoPositionInfo>
#include <QtPositioning>
#include <QGeoPositionInfoSource>
#include <QNmeaPositionInfoSource>


class gr_gps: public gr_data_source{
    public:
        gr_gps(QTcpSocket *socket):gr_data_source("GPS","GPS",static_cast<void*>(socket)){
            init_gps();
        }

        QGeoPositionInfoSource *gps_source;

        void virtual no_more_client();
    private slots:
        void init_gps();
        void gps_positionnew(const QGeoPositionInfo &info);
};

#endif //
