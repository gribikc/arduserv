#include "gr_serial.h"

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void gr_serial::serial_open(int num, int speed){
    QString name="COM"+QString::number(num);
    qDebug() << name;

    serial=new QSerialPort();//this
    serial->setPortName(name);//78

    serial->open(QIODevice::ReadWrite);
    if(serial->isOpen()){
        qDebug() << "COMport OPEN\n";
        serial->setBaudRate(speed);//115200
        serial->setDataBits(QSerialPort::Data8);
        //serial->setDirection(QSerialPort::AllDirections);//!!!
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
    }else{
       qDebug() << "COMport NOT OPENed\n";
       close_all_client();
    }

    serial->flush();
    serial->write("D");
    serial->readAll();
    connect(serial, &QSerialPort::readyRead, this, &gr_serial::serial_read);
}

void gr_serial::serial_list(){
    serial=new QSerialPort();
    //qDebug()<<QSerialPortInfo::availablePorts();
    QList<QSerialPortInfo> la=QSerialPortInfo::availablePorts();
    for(int i=0;i<la.size();i++){
        qDebug() << la.at(i).portName();
        qDebug() << la.at(i).isBusy();
        qDebug() << la.at(i).description();
        qDebug() << la.at(i).manufacturer();

        QByteArray data;
        data=la.at(i).portName().toLocal8Bit();
            send_data_to_client(&data);
        data=la.at(i).isBusy() ? QString("Busy").toLocal8Bit() : QString("free").toLocal8Bit();
            send_data_to_client(&data);
        data=la.at(i).description().toLocal8Bit();
            send_data_to_client(&data);
        data=la.at(i).manufacturer().toLocal8Bit();
            send_data_to_client(&data);
        data="<br>\n\r";
            send_data_to_client(&data);
    }
    close_all_client();
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void gr_serial::no_more_client(){
    serial->close();//!!!
    serial->deleteLater();// deleteLater()
    this->deleteLater();
    qDebug() << "COM Close;";
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void gr_serial::serial_read(){
    QByteArray in_data=serial->readAll();
    send_data_to_client(&in_data);
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void gr_serial::write_data(QByteArray *data){
    if(serial->isOpen() && serial->isWritable()){
        if(indata.size()>0){
            serial->write(indata);
            indata.clear();
        }
        serial->write(*data);
    }else{
        indata.append(*data);
    }
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
