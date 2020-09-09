#include "gr_bluetooth.h"
//
//
//
void GR_bluetooth::bt_open(QString dev_name, QString mode){
    GR_bluetooth::mode=mode;
    GR_bluetooth::dev_name=dev_name;
    //////////////////////////////////
    //Описание секции блютуз
        bt_localDevice.powerOn();

        bt_discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
        bt_discoveryAgent->stop();

        connect(bt_discoveryAgent,  &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,  this, &GR_bluetooth::bt_deviceDiscovered);//(&QBluetoothDeviceInfo)
        connect(bt_discoveryAgent,  &QBluetoothDeviceDiscoveryAgent::finished,  this, &GR_bluetooth::bt_deviceDiscovered_finished);//(&QBluetoothDeviceInfo)

        bt_discoveryAgent->start();
        if(mode=="L"){
            QByteArray data_to_send=static_cast<QString>("[").toUtf8();
            send_data_to_client(&data_to_send);
        }
}
//////////////////////////////////////////////
//////////////////////////////////////////////
void GR_bluetooth::bt_deviceDiscovered(const QBluetoothDeviceInfo &device){//const QBluetoothDeviceInfo &device
    qDebug() << device.name();
    //QString temp_qstring;
    QString str_data="";
    //QByteArray temp_qbarray;
    QByteArray data_to_send="";
    if(mode=="L" && device.isValid()){
        if(scan_list_st==1){
            scan_list_st=0;
        }else {
            data_to_send=",";//!!!?+
            send_data_to_client(&data_to_send);
            data_to_send="";
        }
        str_data+="\n    {";
        str_data+="\n        \"Device\":\"";
            //temp_qstring=device.name();
            //temp_qbarray=temp_qstring.toUtf8();
            str_data+=device.name();
        str_data+="\",\n        \"Rssi\":";
            //temp_qbarray=QByteArray::number(device.rssi());
            str_data+=QString::number(device.rssi());
        str_data+=",\n        \"Addr\":\"";
            //temp_qstring=device.address().toString();
            //temp_qbarray=temp_qstring.toUtf8();
            str_data+=device.address().toString();
        str_data+="\",\n        \"BLE\":";
            if (device.coreConfigurations()& QBluetoothDeviceInfo::LowEnergyCoreConfiguration){
                 str_data+="1";
            }else {
                str_data+="0";
            }
        str_data+="\n    }";
        data_to_send=str_data.toUtf8();
        send_data_to_client(&data_to_send);
    }else if(device.name()==dev_name && mode!="L"){//"HC-06"
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
            connect(ble_control, &QLowEnergyController::connected,          this,   &GR_bluetooth::ble_control_connect);
            connect(ble_control, static_cast<void(QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error), this,   &GR_bluetooth::ble_control_error);
            connect(ble_control, &QLowEnergyController::disconnected,       this,   &GR_bluetooth::ble_control_disconnected);
            connect(ble_control, &QLowEnergyController::serviceDiscovered,  this,   &GR_bluetooth::ble_serviceDiscovered);

            ble_control->connectToDevice();
        }else{
            ble_valid=0;
            bt_Socket=new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
            connect(bt_Socket,          &QBluetoothSocket::readyRead,                       this, &GR_bluetooth::bt_socketRead);
            connect(bt_Socket,          &QBluetoothSocket::connected,                       this, &GR_bluetooth::bt_socketConnected);
            connect(bt_Socket,          &QBluetoothSocket::disconnected,                    this, &GR_bluetooth::bt_socketDisconnected);
            connect(bt_Socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error), [=](QBluetoothSocket::SocketError error){ bt_socketError(error); });

            bt_Socket->connectToService(device.address(),QBluetoothUuid(QBluetoothUuid::SerialPort));
        }
    }
}
//////////////////////////////////////////////
//////////////////////////////////////////////
void GR_bluetooth::bt_deviceDiscovered_finished(){
    qDebug() << "End BT Scann.";
    if(mode=="L"){
        QByteArray data_to_send=static_cast<QString>("\n]").toUtf8();
        send_data_to_client(&data_to_send);
    }
    if(mode=="L" || dev_found==0){//!!!
        close_all_client();
    }
}
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
    void GR_bluetooth::ble_control_connect(){//{0000ffe0-0000-1000-8000-00805f9b34fb}
        ble_control->discoverServices();
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void GR_bluetooth::ble_serviceDiscovered(const QBluetoothUuid &gatt){
        if(gatt.toString()=="{0000ffe0-0000-1000-8000-00805f9b34fb}"){
            ble_service=ble_control->createServiceObject(gatt,this);
            if (ble_service) {
                connect(ble_service,&QLowEnergyService::stateChanged,this,&GR_bluetooth::ble_srv_state_ch);
                connect(ble_service,&QLowEnergyService::characteristicChanged,this,&GR_bluetooth::ble_data_read);
                connect(ble_service,&QLowEnergyService::characteristicWritten,this,&GR_bluetooth::characteristicWritten);
                //void characteristicWritten(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue)

                ble_service->discoverDetails();
                qDebug() << "Service BLE Found.";
            } else {
                qDebug() << "Service BLE not found.";
                close_all_client();
            }
        }
    }
    void GR_bluetooth::characteristicWritten(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue){
        data_was_sended();
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void GR_bluetooth::ble_srv_state_ch(QLowEnergyService::ServiceState s){
       if(s==QLowEnergyService::ServiceDiscovered){
            QList<QLowEnergyCharacteristic> characteristics  = ble_service->characteristics();
            auto hrChar = characteristics[0].descriptors();
            ble_service->writeDescriptor(hrChar[0], QByteArray::fromHex("0100"));// enable notification
            is_writed=1;
            write_data(nullptr);
        }
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void GR_bluetooth::ble_control_error(QLowEnergyController::Error value){
        qDebug() << value;
        close_all_client();
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void GR_bluetooth::ble_control_disconnected(){
        qDebug() << "Disconected";
        close_all_client();
    }
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
    void GR_bluetooth::ble_data_read(const QLowEnergyCharacteristic &c, const QByteArray &value){
        //socket->write(value);
        QByteArray data=value;
        send_data_to_client(&data);
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void GR_bluetooth::bt_socketRead(){
        //socket->write(bt_Socket->readAll());//!!!
        QByteArray in_data=bt_Socket->readAll();
        send_data_to_client(&in_data);
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void GR_bluetooth::bt_socketWrite(QByteArray data){//!!!убрать
        if(ble_valid==1){
            ble_service->writeCharacteristic(ble_service->characteristics().at(0),data);//!!!
        }else{
            bt_Socket->write(data);
        }
    }
    void GR_bluetooth::write_data(QByteArray *data){
        if(data!=nullptr){
            indata.append(*data);
        }
        if(indata.size()>0){
            if(ble_valid==1 && is_writed){
                //ble_service->writeCharacteristic(ble_service->characteristics().at(0),*data);//!!!
                ble_service->writeCharacteristic(ble_service->characteristics().at(0),indata, QLowEnergyService::WriteWithResponse);
                indata.clear();
            }else if(is_writed){
                bt_Socket->write(indata);
                indata.clear();
            }
        }
    }
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
    void GR_bluetooth::bt_socketConnected(){//!!!
       qDebug() << "\r\nСвязь BT установлена\n";
       is_writed=1;
       write_data(nullptr);
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void GR_bluetooth::bt_socketDisconnected(){
        qDebug() << "\r\nПотеря BT связи\n";
        is_writed=0;
        close_all_client();
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void GR_bluetooth::bt_socketError(QBluetoothSocket::SocketError error){
        qDebug() << error;
        qDebug() << "\r\nBT ERROR!!!\n";
        close_all_client();
    }
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
    void GR_bluetooth::bt_close_all(){
        //close_all_client();
        if(bt_discoveryAgent!=nullptr){
            bt_discoveryAgent->stop();
            bt_discoveryAgent->destroyed();
        }
        qDebug() << "BT DA";
        if(bt_Socket!=nullptr){
            bt_Socket->close();
            bt_Socket->destroyed();
        }
        qDebug() << "BT SO";
        if(ble_valid==1){
            ble_control->disconnectFromDevice();
        }
        qDebug() << "BT BLED";
        this->deleteLater();
        qDebug() << "BT TD";
    }
//////////////////////////////////////////////
//////////////////////////////////////////////
    void GR_bluetooth::no_more_client(){
        qDebug()<<"No More Client";
        bt_close_all();
    }
//////////////////////////////////////////////
//////////////////////////////////////////////
