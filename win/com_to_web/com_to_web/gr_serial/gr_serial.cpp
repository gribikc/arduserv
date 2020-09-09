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
        serial->setDataTerminalReady(1);
    }else{
       qDebug() << "COMport NOT OPENed\n";
       close_all_client();
    }

    serial->flush();
    //serial->write("D");
    serial->readAll();
    connect(serial, &QSerialPort::readyRead, this, &gr_serial::serial_read);
    connect(serial, &QSerialPort::bytesWritten, this, &gr_serial::bytesWritten);
}

void gr_serial::serial_list(){
    serial=new QSerialPort();
    //qDebug()<<QSerialPortInfo::availablePorts();
    QList<QSerialPortInfo> la=QSerialPortInfo::availablePorts();
    QByteArray data="";
    QString str_data="";
    int is_st=1;
    str_data="[";
    for(int i=0;i<la.size();i++){
        if(is_st==1){
            is_st=0;
        }else {
            str_data+=",";
        }
        str_data+="\n    {";
            str_data+="\n        \"port_name\":\"";
                str_data+=la.at(i).portName();
            str_data+="\",\n        \"is_busy\":";
                str_data+=la.at(i).isBusy() ? QString("1") : QString("0");
            str_data+=",\n        \"description\":\"";
                str_data+=la.at(i).description();
            str_data+="\",\n        \"manufacturer\":\"";
                str_data+=la.at(i).manufacturer();
        str_data+="\"\n    }";
    }
    str_data+="\n]";
    data=str_data.toUtf8();
    send_data_to_client(&data);
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
void gr_serial::bytesWritten(){
    data_was_sended();
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
