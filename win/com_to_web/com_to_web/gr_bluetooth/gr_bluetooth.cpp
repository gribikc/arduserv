#include "gr_bluetooth.h"
//
//
//
void gr_bluetooth::bt_open(QString dev_name, int mode, QTcpSocket *socket_point){
    socket=socket_point;
    gr_bluetooth::mode=mode;
    gr_bluetooth::dev_name=dev_name;
    //////////////////////////////////
    //Описание секции блютуз
        //if(QSysInfo::productType()=="android"){
            bt_localDevice.powerOn();
            bt_discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
            bt_Socket=new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
            bt_discoveryAgent->stop();

            connect(bt_discoveryAgent,  &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,  this, &gr_bluetooth::bt_deviceDiscovered);//(&QBluetoothDeviceInfo)
            connect(bt_discoveryAgent,  &QBluetoothDeviceDiscoveryAgent::finished,  this, &gr_bluetooth::bt_deviceDiscovered_finished);//(&QBluetoothDeviceInfo)
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
void gr_bluetooth::bt_deviceDiscovered_finished(){
    qDebug() << "End BT Scann.";
    if(mode==0){
        socket->write("\r\n B.B.");
        socket->close();
    }
}
//////////////////////////////////////////////
//////////////////////////////////////////////
void gr_bluetooth::bt_deviceDiscovered(const QBluetoothDeviceInfo &device){//const QBluetoothDeviceInfo &device
    //QObject *object = QObject::sender();
    //QTcpSocket *socket = static_cast<QTcpSocket *>(object);
    //QBluetoothDeviceInfo *device = static_cast<QBluetoothDeviceInfo *>(object);

    qDebug() << device.name();
    QString temp_qstring;
    QByteArray temp_qbarray;
    if(mode==0 && device.isValid()){
        temp_qstring=device.name();
        temp_qbarray=temp_qstring.toUtf8();
        socket->write("Device: ");
        socket->write(temp_qbarray);

        socket->write(" Rssi: ");
        temp_qbarray=QByteArray::number(device.rssi());
        socket->write(temp_qbarray);

        socket->write(" Addr: ");
        temp_qstring=device.address().toString();
        temp_qbarray=temp_qstring.toUtf8();
        socket->write(temp_qbarray);

        socket->write("\r\n");

    }else if(device.name()==dev_name && mode==1){//"HC-06"
        bt_discoveryAgent->stop();
        QString find_dev;
        find_dev="\nНашли:";
        find_dev+=device.name();
        find_dev+="(";
        find_dev+=device.address().toString();
        find_dev+=")\nСоединение...\n";
        //ui->textEdit_error_log->insertPlainText(find_dev);
         qDebug() << find_dev;

        qDebug() << device.rssi();
        qDebug() << device.isValid();

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
