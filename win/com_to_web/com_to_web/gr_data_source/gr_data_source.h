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
        gr_data_source(QString type,QString dev_name);
        gr_data_source(QString type,QString dev_name,QTcpSocket *socket);

        QList<QTcpSocket*> sockets_list;//Массив получателей данных

        QString type="";    //COM   //BT    //GPS   //SENSOR
        QString dev_name="";//7     //HC-05 //      //ROT

        void add_socket(QTcpSocket *socket);
        void sub_socket(QTcpSocket *socket);
        void send_data_to_sockets(QByteArray *data);
        virtual void write_data(QByteArray *data){};
        virtual void socket_added(){};
        virtual void no_more_sockets(){};

public slots:
        void socket_readyRead(); // обработчик входящих данных
        void socket_stateChanged(); // обработчик изменения состояния вещающего
    private slots:

};

#endif // GR_DATA_SOURCE_H
