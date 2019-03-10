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

#include <QDebug>



class gr_bluetooth: public QObject{
    //Q_OBJECT
public:
    gr_bluetooth(){}

public:
    void bt_open(QString dev_name, int mode, QTcpSocket *socket_point);
    QTcpSocket *socket=0;
    int mode=0;
    QString dev_name=0;

    QBluetoothDeviceDiscoveryAgent *bt_discoveryAgent=0;
    QBluetoothSocket *bt_Socket=0;
    QBluetoothLocalDevice bt_localDevice;
private slots:
    void bt_deviceDiscovered(const QBluetoothDeviceInfo &device);
    void bt_deviceDiscovered_finished();
    void bt_socketError();
    void bt_socketConnected();
    void bt_socketDisconnected();
    void bt_socketRead();

};
