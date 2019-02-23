#include "gr_bluetooth.h"
//
//
//
void gr_bluetooth::bt_open(int num, int speed, QTcpSocket *socket_point){
    socket=socket_point;
    //////////////////////////////////
    //Описание секции блютуз
        //if(QSysInfo::productType()=="android"){
            bt_localDevice.powerOn();
            bt_discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
            bt_Socket=new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
            bt_discoveryAgent->stop();

            connect(bt_discoveryAgent,  &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,  this, &gr_bluetooth::bt_deviceDiscovered);//(&QBluetoothDeviceInfo)
            connect(bt_Socket,          &QBluetoothSocket::readyRead,                       this, &gr_bluetooth::bt_socketRead);
            //connect(bt_Socket,          &QBluetoothSocket::readyRead,                           this, &gr_bluetooth::bt_socketRead);
            connect(bt_Socket,          &QBluetoothSocket::connected,                       this, &gr_bluetooth::bt_socketConnected);
            connect(bt_Socket,          &QBluetoothSocket::disconnected,                    this, &gr_bluetooth::bt_socketDisconnected);
            // !!!connect(serial, &QSerialPort::readyRead, this, &gr_serial::serial_socketRead);//&gr_serial::serial_socketRead

            bt_discoveryAgent->start();
        //}
    /////////////////////////////////


}
//////////////////////////////////////////////
//////////////////////////////////////////////
void gr_bluetooth::bt_socketRead(){
    //QByteArray in_data=bt_Socket->readAll();
    //QByteArray test="123";
    //if(gr_bluetooth::socket->isWritable()){
    //    gr_bluetooth::socket->write("123");// socket->write(test);
    //}
    socket->write(bt_Socket->readAll());
}
//////////////////////////////////////////////
//////////////////////////////////////////////
void gr_bluetooth::bt_deviceDiscovered(const QBluetoothDeviceInfo &device){//const QBluetoothDeviceInfo &device
    //QObject *object = QObject::sender();
    //QTcpSocket *socket = static_cast<QTcpSocket *>(object);
    //QBluetoothDeviceInfo *device = static_cast<QBluetoothDeviceInfo *>(object);

    if(device.name()=="HC-06"){
        bt_discoveryAgent->stop();
        QString find_dev;
        find_dev="\nНашли:";
        find_dev+=device.name();
        find_dev+="(";
        find_dev+=device.address().toString();
        find_dev+=")\nСоединение...\n";
        //ui->textEdit_error_log->insertPlainText(find_dev);
         qDebug() << find_dev;

        bt_Socket->connectToService(device.address(),QBluetoothUuid(QBluetoothUuid::SerialPort));
        //ui->label_5->setStyleSheet("color: rgb(253, 233, 16);");
    }
}
//////////////////////////////////////////////
//////////////////////////////////////////////
void gr_bluetooth::bt_socketConnected(){
   qDebug() << "\r\nСвязь BT установлена\n";
   //ui->label_5->setStyleSheet("color: rgb(0, 200, 0);");
}
void gr_bluetooth::bt_socketDisconnected(){
    qDebug() << "\r\nПотеря BT связи\n";
    //ui->label_5->setStyleSheet("color: rgb(200, 0, 0);");
}
void gr_bluetooth::bt_socketError(){
    //QString error_qstr="";
    //error_qstr=error_msg;
    //write_log_file(&error_qstr,3);
}
//////////////////////////////////////////////
//////////////////////////////////////////////
