#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>

#include "gr_serial/gr_serial.h"



/*class gr_QTcpSocket : public QTcpSocket{
    Q_OBJECT
public:
    explicit gr_QTcpSocket(){ }
public:
    int myData=0;
    QByteArray arr;
};*/






class gr_sock_srv: public QObject{
    //Q_OBJECT
public:
    gr_sock_srv(){}
public slots:
    void incommingConnection(); // обработчик входящего подключения
    void readyRead(); // обработчик входящих данных
    void stateChanged(); // обработчик изменения состояния вещающего
public:
    void gr_sock_srv_start();

    typedef struct {
        QTcpSocket  *socket;
        QByteArray  InData;
        bool com_parser_valid=0;
        int com_num;
        int com_speed;
        int com_bits;
        int com_par;

        gr_serial *com_port;
    } gr_httprqs_parser;

    void parser_rqst(gr_httprqs_parser *parser_data);

    QTcpServer *server; // указатель на сервер
    QList<gr_httprqs_parser> httprqs_parser; // получатели данных
};
