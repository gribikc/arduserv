#include <gr_data_source/gr_data_source.h>

#include <QGeoSatelliteInfo>
#include <QGeoCoordinate>
#include <QGeoPositionInfo>
#include <QtPositioning>
#include <QGeoPositionInfoSource>
#include <QNmeaPositionInfoSource>


class gr_gps: public QObject,public gr_data_source{
        //Q_OBJECT
    public:
        //gr_gps(QTcpSocket socket):gr_data_source(socket);
        gr_gps(){}
        QGeoPositionInfoSource *gps_source;

        void virtual listener_added();
    private slots:
        void gps_positionnew(const QGeoPositionInfo &info);
};
