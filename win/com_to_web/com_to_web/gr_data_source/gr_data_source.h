#include <QtCore>
#include <QObject>
#include <QCoreApplication>

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>

#include <QDebug>



class gr_data_source: public QObject{
        //Q_OBJECT
    public:
        QList<QTcpSocket*> socket_listeners;//Массив получателей данных

        void gr_data_source(){}
        void add_listener(QTcpSocket *socket);
        void send_data_to_listeners(QByteArray *data);
        virtual void listener_added()=0;
    private slots:

};
