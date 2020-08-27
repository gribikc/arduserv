#ifndef GR_SOCKET_H
#define GR_SOCKET_H

#include <QObject>

class gr_socket : public QObject
{
    Q_OBJECT
public:
    explicit gr_socket(QObject *parent = nullptr);
    virtual void dev_send_data(QByteArray *data){data->clear();}
signals:
    virtual void sock_readyRead(QByteArray *data){data->clear();}
    virtual void sock_disconnected(QByteArray *data){data->clear();}
};

#endif // GR_SOCKET_H
