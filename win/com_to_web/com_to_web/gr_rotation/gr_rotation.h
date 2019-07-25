#include <QtCore>
#include <QObject>
#include <QCoreApplication>

#include <QSensor>
#include <QRotationSensor>
#include <QRotationReading>

#include <QAccelerometer>
#include <QAccelerometerReading>

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>

#include <QDebug>



class gr_rotation: public QObject{
        //Q_OBJECT
    public:

        QTcpSocket *socket=0;
        QList<QTcpSocket*> socket_listener;
        QRotationSensor *sensor=new QRotationSensor(this);
        //QAccelerometer *sensor=new QAccelerometer;
        gr_rotation(){}

        void add_listener(QTcpSocket *socket_point);
    private slots:
        void read_changed();
    protected:
        bool filter(QRotationReading *reading);
};
