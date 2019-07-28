#include <QtCore>
#include <QObject>
#include <QCoreApplication>

#include <QtSerialPort/QtSerialPort>
#include <QSerialPortInfo>

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>

#include <QNetworkInterface>



class gr_serial: public QObject{
    //Q_OBJECT
public:
    gr_serial(){}

public:
    void serial_socketRead();
public:
    QSerialPort *serial=0;
    void serial_open(int num,int speed,QTcpSocket *socket_point);

    QTcpSocket *socket=0;
};
