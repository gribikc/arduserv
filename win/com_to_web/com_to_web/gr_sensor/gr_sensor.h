#ifndef GR_SENSOR_H
#define GR_SENSOR_H


#include "gr_data_source/gr_data_source.h"
#include <QSensor>
#include <QRotationSensor>
#include <QRotationReading>

#include <QAccelerometer>
#include <QAccelerometerReading>


class GR_sensor: public gr_data_source{
    public:// dev/sens/r/rot
        GR_sensor(QString name, QString mode, void *socket):gr_data_source("SENS",name,static_cast<void*>(socket)){
            //if(mode=="R"){
                sensor_start();
            //}
        }
        virtual void no_more_client();


        //QRotationSensor *sensor=new QRotationSensor(this);
        QAccelerometer *sensor=new QAccelerometer(this);
        void sensor_start();
        void read_changed();
};

#endif // GR_SENSOR_H
