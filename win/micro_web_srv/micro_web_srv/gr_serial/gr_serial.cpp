#include "gr_serial.h"

//
//
//
void gr_serial::serial_open(int num, int speed, QTcpSocket *socket_point){
    socket=socket_point;

    serial=new QSerialPort();//this
    serial->setPortName("COM27");//78//5
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    //serial->setDirection(QSerialPort::AllDirections);//!!!
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if(serial->open(QIODevice::ReadWrite)){
        printf("COMport OPEN\n");
        //connect(serial, SIGNAL(readyRead()), this, SLOT(serial_socketRead()));
        serial->flush();
        serial->write("D");
        serial->readAll();
        connect(serial, &QSerialPort::readyRead, this, &gr_serial::serial_socketRead);//&gr_serial::serial_socketRead
    }else{
        printf("COMport ERROR\n");
    }
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
