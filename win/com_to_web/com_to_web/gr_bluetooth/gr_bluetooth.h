#include <QtCore>
#include <QObject>
#include <QCoreApplication>

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>

#include <QtBluetooth>
#include <QBluetoothServer>
#include <QBluetoothServiceInfo>
#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothglobal.h>
#include <QLowEnergyController>
#include <QLowEnergyService>

#include <QDebug>



class gr_bluetooth: public QObject{
    //Q_OBJECT
public:
    gr_bluetooth(){}

public:
    void bt_open(QString dev_name, int mode, QTcpSocket *socket_point);
    QTcpSocket *socket=nullptr;
    int mode=0;
    int ble_valid=0;
    QString dev_name=nullptr;
    bool dev_found=0;

    QBluetoothDeviceDiscoveryAgent *bt_discoveryAgent=nullptr;
    QBluetoothSocket *bt_Socket=nullptr;
    QBluetoothLocalDevice bt_localDevice;
    QBluetoothDeviceInfo bt_deviceinfo;
    QLowEnergyController *ble_control;
    QLowEnergyService *ble_service;

public slots:
        void bt_socketError(QBluetoothSocket::SocketError error);
        void bt_socketWrite(QByteArray data);
        void bt_close_all();
private slots:
    void bt_deviceDiscovered(const QBluetoothDeviceInfo &device);
    void bt_deviceDiscovered_finished();

    void ble_serviceDiscovered(const QBluetoothUuid &gatt);
    void ble_control_connect();
    void ble_data_read(const QLowEnergyCharacteristic &c,const QByteArray &value);
    void ble_data_read2(const QLowEnergyDescriptor &c,const QByteArray &value);
    void ble_srv_state_ch(QLowEnergyService::ServiceState s);
    void ble_control_error(QLowEnergyController::Error value);
    void ble_control_disconnected();

    void bt_socketConnected();
    void bt_socketDisconnected();
    void bt_socketRead();

};
