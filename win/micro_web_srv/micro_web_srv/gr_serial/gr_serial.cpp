#include "gr_serial.h"

//
//
//
void gr_serial::serial_open(int num, int speed, QTcpSocket *socket_point){
    socket=socket_point;

    serial=new QSerialPort();//this
    serial->setPortName("COM5");//78
    serial->setBaudRate(115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if(serial->open(QIODevice::ReadWrite)){
        printf("COMport OPEN\n");
    }else{
        printf("COMport ERROR\n");
    }
    //connect(serial, SIGNAL(readyRead()), this, SLOT(serial_socketRead()));
    connect(serial, &QSerialPort::readyRead, this, &gr_serial::serial_socketRead);//&gr_serial::serial_socketRead
}
//
//
//
void gr_serial::serial_socketRead(){
    //QByteArray in_data=serial->readAll();
    //uart_parser_data(in_data);
    socket->write(serial->readAll());
}
//
//
//
