#ifndef GR_DEV_MANAGER_H
#define GR_DEV_MANAGER_H

#include <QObject>
#ifdef win32
    #include "gr_serial/gr_serial.h"
#endif
#include "gr_bluetooth/gr_bluetooth.h"
#include "gr_gps/gr_gps.h"
#include "gr_http_client/gr_http_client.h"
#include "gr_sensor/gr_sensor.h"

class gr_dev_manager : public QObject
{
    Q_OBJECT
public:
    explicit gr_dev_manager(QObject *parent = nullptr);

    void add_client(GR_http_client *http_client);

    QList<void*> gr_devices;
signals:

public slots:
    void dev_was_destroyed();
};

#endif // GR_DEV_MANAGER_H
