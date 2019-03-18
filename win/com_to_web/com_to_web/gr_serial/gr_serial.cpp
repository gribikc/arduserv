#include "gr_serial.h"

//
//
//
void gr_serial::serial_open(int num, int speed, QTcpSocket *socket_point){
    socket=socket_point;

    QString name="COM"+QString::number(num);
    qDebug() << name;
    serial=new QSerialPort();//this
    serial->setPortName(name);//78

    /*serial->setBaudRate(115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setDirection(QSerialPort::AllDirections);//!!!
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);*/
    if(serial->open(QIODevice::ReadWrite)){
        printf("COMport OPEN\n");
        //serial->setPortName("COM5");//78
        serial->setBaudRate(speed);//115200
        serial->setDataBits(QSerialPort::Data8);
        //serial->setDirection(QSerialPort::AllDirections);//!!!
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
    }
    if(!serial->isReadable()){
        socket->close();
    }
    //connect(serial, SIGNAL(readyRead()), this, SLOT(serial_socketRead()));
    serial->flush();
    serial->write("D");
    serial->readAll();
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
