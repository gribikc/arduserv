#ifndef GR_bluetooth_H
#define GR_bluetooth_H
#include "gr_data_source/gr_data_source.h"

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
//#include <qbluetoothglobal.h>
//<QtBluetooth/qtbluetoothglobal.h>
#include <QLowEnergyController>
#include <QLowEnergyService>

#include <QDebug>



class GR_bluetooth:public gr_data_source{
    Q_OBJECT
public:
    GR_bluetooth(QString name, QString mode, void *socket):gr_data_source("BT",name,static_cast<void*>(socket)){
        bt_open(name,mode);//mode
    }
    virtual void no_more_client();//no_more_sockets()
    virtual void write_data(QByteArray *data);

public:
    void bt_open(QString dev_name, QString mode);
    QTcpSocket *socket=nullptr;
    QString mode="";
    int ble_valid=0;
    QString dev_name="";
    bool dev_found=0;

    QBluetoothDeviceDiscoveryAgent *bt_discoveryAgent=nullptr;
    QBluetoothSocket *bt_Socket=nullptr;
    QBluetoothLocalDevice bt_localDevice;
    QBluetoothDeviceInfo bt_deviceinfo;
    QLowEnergyController *ble_control;
    QLowEnergyService *ble_service;

    void characteristicWritten(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
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
    //void ble_data_read2(const QLowEnergyDescriptor &c,const QByteArray &value);
    void ble_srv_state_ch(QLowEnergyService::ServiceState s);
    void ble_control_error(QLowEnergyController::Error value);
    void ble_control_disconnected();

    void bt_socketConnected();
    void bt_socketDisconnected();
    void bt_socketRead();

};

#endif //
