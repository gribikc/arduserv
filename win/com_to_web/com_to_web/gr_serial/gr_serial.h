#ifndef GR_SERIAL_H
#define GR_SERIAL_H

#include "gr_data_source/gr_data_source.h"
#include <QtSerialPort/QtSerialPort>
#include <QSerialPortInfo>

class gr_serial:public gr_data_source{
        Q_OBJECT
    public:
        gr_serial(int num,int speed,QTcpSocket *socket):gr_data_source("COM",QString::number(num),static_cast<void*>(socket)){
            serial_open(num,speed);
        }

        QSerialPort *serial=0;

        virtual void no_more_client();//no_more_sockets()
        virtual void write_data(QByteArray *data);
    private slots:
        void serial_open(int num,int speed);
        void serial_read();
};

#endif //
