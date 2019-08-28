#ifndef GR_DEV_MANAGER_H
#define GR_DEV_MANAGER_H

#include <QObject>

#include "gr_serial/gr_serial.h"
#include "gr_gps/gr_gps.h"

class gr_dev_manager : public QObject
{
    Q_OBJECT
public:
    explicit gr_dev_manager(QObject *parent = nullptr);

    void add_client(QString type, QStringList list_param,QByteArray *indata,QTcpSocket *socket);

    QList<void*> gr_devices;
signals:

public slots:
    void dev_was_destroyed();
};

#endif // GR_DEV_MANAGER_H
