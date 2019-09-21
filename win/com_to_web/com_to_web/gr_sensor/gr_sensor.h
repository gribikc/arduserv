#ifndef GR_SENSOR_H
#define GR_SENSOR_H


#include "gr_data_source/gr_data_source.h"
#include <QSensor>

#include <QRotationSensor>
#include <QRotationReading>

#include <QAccelerometer>
#include <QAccelerometerReading>

#include <QMagnetometer>
#include <QAmbientLightSensor>



class GR_sensor: public gr_data_source{
    public:// dev/sens/r/rot
        GR_sensor(QString name, QString mode, void *socket):gr_data_source("SENS",name,static_cast<void*>(socket)){
            //if(mode=="R"){
                sensor_start();
            //}
        }
        virtual void no_more_client();


        QRotationSensor     *rot_sensor=new QRotationSensor(this);
        QAccelerometer      *acc_sensor=new QAccelerometer(this);
        QMagnetometer       *mag_sensor=new QMagnetometer(this);
        QAmbientLightSensor *ambl_sensor=new QAmbientLightSensor(this);

        void sensor_start();
        void read_changed(QString prefix);
        void init_acc();
        void init_mag();
        void init_ambl();
        void init_rot();
};

#endif // GR_SENSOR_H
