#ifndef GR_DATA_SOURCE_H
#define GR_DATA_SOURCE_H

#include <QObject>

#include <QtCore>
#include <QObject>
#include <QCoreApplication>

#include <QTcpServer>
#include <QTcpSocket>


#include <QByteArray>
#include <QDataStream>

#include <QDebug>



class gr_data_source: public QObject{
        Q_OBJECT
    public:
        gr_data_source();
        gr_data_source(QTcpSocket *socket);

        QList<QTcpSocket*> socket_listeners;//Массив получателей данных

        void add_socket(QTcpSocket *socket);
        void send_data_to_sockets(QByteArray *data);
        virtual void write_data(QByteArray *data){};
        virtual void socket_added(){};
        virtual void no_more_sockets(){};
    private slots:

};

#endif // GR_DATA_SOURCE_H
