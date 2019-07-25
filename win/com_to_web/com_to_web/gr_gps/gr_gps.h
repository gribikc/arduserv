#include <QtCore>
#include <QObject>
#include <QCoreApplication>

#include <QGeoSatelliteInfo>
#include <QGeoCoordinate>
#include <QGeoPositionInfo>
#include <QtPositioning>
#include <QGeoPositionInfoSource>
#include <QNmeaPositionInfoSource>

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>

#include <QDebug>



class gr_gps: public QObject{
        //Q_OBJECT
    public:

        QTcpSocket *socket=0;
        QList<QTcpSocket*> socket_listener;
        gr_gps(){}
        QGeoPositionInfoSource *gps_source;
        void gps_add_listener(QTcpSocket *socket_point);
    private slots:
        void gps_positionnew(const QGeoPositionInfo &info);
};
