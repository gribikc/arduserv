#include "gr_bluetooth.h"
//
//
//
void GR_bluetooth::bt_open(QString dev_name, int mode, QTcpSocket *socket_point){
    socket=socket_point;
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

}
//////////////////////////////////////////////
//////////////////////////////////////////////
void GR_bluetooth::bt_deviceDiscovered(const QBluetoothDeviceInfo &device){//const QBluetoothDeviceInfo &device
    qDebug() << device.name();
    QString temp_qstring;
    QByteArray temp_qbarray;
    QByteArray data_to_send="";
    if(mode==0 && device.isValid()){
        data_to_send+="Device: ";
            temp_qstring=device.name();
            temp_qbarray=temp_qstring.toUtf8();
            data_to_send+=temp_qbarray;
        data_to_send+=" Rssi: ";
            temp_qbarray=QByteArray::number(device.rssi());
            data_to_send+=temp_qbarray;
        data_to_send+=" Addr: ";
            temp_qstring=device.address().toString();
            temp_qbarray=temp_qstring.toUtf8();
            data_to_send+=temp_qbarray;
        data_to_send+="\r\n";
        send_data_to_client(&data_to_send);
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
    if(mode==0 || dev_found==0){//!!!
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
                ble_service->discoverDetails();
                qDebug() << "Service BLE Found.";
            } else {
                qDebug() << "Service BLE not found.";
                close_all_client();
            }
        }
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void GR_bluetooth::ble_srv_state_ch(QLowEnergyService::ServiceState s){
       if(s==QLowEnergyService::ServiceDiscovered){
            QList<QLowEnergyCharacteristic> characteristics  = ble_service->characteristics();
            auto hrChar = characteristics[0].descriptors();
            ble_service->writeDescriptor(hrChar[0], QByteArray::fromHex("0100"));// enable notification
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
        if(ble_valid==1){
            //ble_service->writeCharacteristic(ble_service->characteristics().at(0),*data);//!!!
        }else{
            //bt_Socket->write(*data);
        }
    }
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
    void GR_bluetooth::bt_socketConnected(){
       qDebug() << "\r\nСвязь BT установлена\n";
    }
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    void GR_bluetooth::bt_socketDisconnected(){
        qDebug() << "\r\nПотеря BT связи\n";
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
