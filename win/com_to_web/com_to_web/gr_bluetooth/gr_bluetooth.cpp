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
            //connect(bt_Socket,          &QBluetoothSocket::error(QBluetoothSocket::SocketError),this,  &gr_bluetooth::bt_socketError());
            connect(bt_Socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error),
                [=](QBluetoothSocket::SocketError error){ bt_socketError(error); });
            // !!!connect(serial, &QSerialPort::readyRead, this, &gr_serial::serial_socketRead);//&gr_serial::serial_socketRead

            //BLE
                //dev
                //connect(ble_control,&QLowEnergyController::serviceDiscovered,this, &gr_bluetooth::ble_serviceDiscovered);
                //connect(ble_control,&QLowEnergyController::connected,this, &gr_bluetooth::ble_dev_connect);
                //srv
                //connect(ble_service,&QLowEnergyService::characteristicChanged,this,&gr_bluetooth::ble_data_read);


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

    void gr_bluetooth::bt_socketWrite(QByteArray data){
        if(ble_valid==1){
            ble_service->writeCharacteristic(ble_service->characteristics().at(0),data);//!!!
        }else{
            bt_Socket->write(data);
        }
    }

//////////////////////////////////////////////
//////////////////////////////////////////////
void gr_bluetooth::bt_deviceDiscovered_finished(){
    qDebug() << "End BT Scann.";
    if(mode==0 || dev_found==0){//!!!
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
        dev_found=1;
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

        if (device.coreConfigurations()& QBluetoothDeviceInfo::LowEnergyCoreConfiguration){//!!!
            ble_valid=1;
            qDebug() <<"Low Energy device found. Scanning more...";
            ble_control = new QLowEnergyController(device.address(), this);
            connect(ble_control, &QLowEnergyController::connected,          this,   &gr_bluetooth::ble_control_connect);
            connect(ble_control, static_cast<void(QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error),
                                                                            this,   &gr_bluetooth::ble_control_error);
            connect(ble_control, &QLowEnergyController::disconnected,       this,   &gr_bluetooth::ble_control_disconnected);
            connect(ble_control, &QLowEnergyController::serviceDiscovered,  this,   &gr_bluetooth::ble_serviceDiscovered);
            ble_control->connectToDevice();
        }else{
            ble_valid=0;
            bt_Socket->connectToService(device.address(),QBluetoothUuid(QBluetoothUuid::SerialPort));
        }
        //ui->label_5->setStyleSheet("color: rgb(253, 233, 16);");
    }
}
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
    void gr_bluetooth::ble_control_connect(){//{0000ffe0-0000-1000-8000-00805f9b34fb}
        ble_control->discoverServices();
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void gr_bluetooth::ble_control_error(QLowEnergyController::Error value){
        qDebug() << value;
        socket->close();
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void gr_bluetooth::ble_control_disconnected(){
        qDebug() << "Disconected";
        socket->close();
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void gr_bluetooth::ble_serviceDiscovered(const QBluetoothUuid &gatt){
        if(gatt.toString()=="{0000ffe0-0000-1000-8000-00805f9b34fb}"){
            ble_service=ble_control->createServiceObject(gatt,this);
            if (ble_service) {
                connect(ble_service,&QLowEnergyService::stateChanged,this,&gr_bluetooth::ble_srv_state_ch);
                connect(ble_service,&QLowEnergyService::characteristicChanged,this,&gr_bluetooth::ble_data_read);
                ble_service->discoverDetails();
                qDebug() << "Service BLE Found.";
            } else {
                qDebug() << "Service BLE not found.";
                socket->close();
            }
        }
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void gr_bluetooth::ble_srv_state_ch(QLowEnergyService::ServiceState s){
       if(s==QLowEnergyService::ServiceDiscovered){
            QList<QLowEnergyCharacteristic> characteristics  = ble_service->characteristics();
            auto hrChar = characteristics[0].descriptors();
            // enable notification
                ble_service->writeDescriptor(hrChar[0], QByteArray::fromHex("0100"));
            //ble_service->writeDescriptor(hrChar[1], QByteArray::fromHex("0100"));
        }
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void gr_bluetooth::ble_data_read(const QLowEnergyCharacteristic &c, const QByteArray &value){
        socket->write(value);
    }
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
void gr_bluetooth::bt_socketConnected(){
   qDebug() << "\r\nСвязь BT установлена\n";
   //ui->label_5->setStyleSheet("color: rgb(0, 200, 0);");
}
void gr_bluetooth::bt_socketDisconnected(){
    qDebug() << "\r\nПотеря BT связи\n";
    socket->close();
    //ui->label_5->setStyleSheet("color: rgb(200, 0, 0);");
}
void gr_bluetooth::bt_socketError(QBluetoothSocket::SocketError error){
    qDebug() << error;
    qDebug() << "\r\nBT ERROR!!!\n";
    socket->close();
    //QString error_qstr="";
    //error_qstr=error_msg;
    //write_log_file(&error_qstr,3);
}
//////////////////////////////////////////////
//////////////////////////////////////////////
void gr_bluetooth::bt_close_all(){
    bt_discoveryAgent->stop();
    bt_Socket->close();
    bt_discoveryAgent->destroyed();
    bt_Socket->destroyed();
    if(ble_valid==1){
        //ble_service->
        ble_control->disconnectFromDevice();
    }
}
//////////////////////////////////////////////
//////////////////////////////////////////////

