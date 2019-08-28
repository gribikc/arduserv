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
        gr_data_source(QString type,QString dev_name,void *client);

        QList<QTcpSocket*> client_list;//Массив получателей данных

        QString type="";    //COM   //BT    //GPS   //SENSOR
        QString dev_name="";//7     //HC-05 //      //ROT
        QByteArray indata;

        void add_client(QTcpSocket *client);
        void sub_client(QTcpSocket *client);
        void send_data_to_client(QByteArray *data);
        virtual void write_data(QByteArray *data){}
        virtual void client_added(){}
        virtual void no_more_client(){}

public slots:
        void client_readyRead(); // обработчик входящих данных
        void client_stateChanged(); // обработчик изменения состояния вещающего
    private slots:

};

#endif // GR_DATA_SOURCE_H
