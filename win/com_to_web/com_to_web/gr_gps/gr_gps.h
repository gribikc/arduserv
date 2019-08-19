#include "gr_data_source/gr_data_source.h"
#include <QGeoSatelliteInfo>
#include <QGeoCoordinate>
#include <QGeoPositionInfo>
#include <QtPositioning>
#include <QGeoPositionInfoSource>
#include <QNmeaPositionInfoSource>


class gr_gps: public gr_data_source{
    public:
        gr_gps():gr_data_source(){
            init_gps();
        }

        QGeoPositionInfoSource *gps_source;

        void virtual socket_added();
        void virtual no_more_sockets();
    private slots:
        void init_gps();
        void gps_positionnew(const QGeoPositionInfo &info);
};
