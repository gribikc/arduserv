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
#include <gr_http_client/gr_http_client.h>
//#include <gr_logger/gr_logger.h>


class gr_data_source: public QObject{
        Q_OBJECT
    public:
        gr_data_source(QString type,QString dev_name);
        gr_data_source(QString type,QString dev_name,void *client);

        //QList<QTcpSocket*> client_list;//Массив получателей данных
        QList<GR_http_client*> client_list;

        QString type="";    //COM   //BT    //GPS   //SENSOR
        QString dev_name="";//7     //HC-05 //      //ROT
        QByteArray indata;
        bool is_writed=0;

        void add_client(void *client);
        void sub_client(void *client);
        void send_data_to_client(QByteArray *data);
        void data_was_sended();
        virtual void write_data(QByteArray *data){data->clear();}
        virtual void client_added(){}
        virtual void no_more_client(){}

        void close_all_client();
public slots:
        void client_readyRead(); // обработчик входящих данных
        void client_stateChanged(); // обработчик изменения состояния вещающего
    private slots:

};

#endif // GR_DATA_SOURCE_H
