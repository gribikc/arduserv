#ifndef GR_SOCKET_H
#define GR_SOCKET_H

#include <QObject>
#include <QtCore>
#include <QCoreApplication>
#include <QDebug>
#include <QAbstractSocket>
#include <QtWebSockets>

class gr_socket : public QObject{
    Q_OBJECT
public:
    explicit gr_socket(QObject *parent = nullptr);
    virtual void write(QByteArray *data){}
    virtual void write(const char *data){}
    virtual void write(QString *data){}
    virtual QByteArray readAll(){}
    virtual void setSocketDescriptor(int sdscrp){}
    virtual void setSocketDescriptor(QWebSocket *sdscrp){};
    virtual QAbstractSocket::SocketState state(){}
    virtual void close(){}
    virtual void flush(){}
signals:
    void readyRead();
    void disconnected();
};

#endif // GR_SOCKET_H
