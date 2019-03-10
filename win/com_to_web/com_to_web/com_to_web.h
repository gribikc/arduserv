#ifndef COM_TO_WEB_H
#define COM_TO_WEB_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>

#include "gr_serial/gr_serial.h"
#include "gr_bluetooth/gr_bluetooth.h"




namespace Ui {
class com_to_web;
}


class com_to_web : public QMainWindow
{
    Q_OBJECT
/////////////////////
public slots:
    void incommingConnection(); // обработчик входящего подключения
    void readyRead(); // обработчик входящих данных
    void stateChanged(); // обработчик изменения состояния вещающего
public:
    void gr_sock_srv_start();

    typedef struct {
        QTcpSocket  *socket=0;
        QByteArray  InData=0;
        QTimer *timer=0;

        bool data_wr=0;

        bool com_parser_valid=0;
        int com_num=0;
        int com_speed=0;
        int com_bits=0;
        int com_par=0;

        bool bt_parser_valid=0;//QString dev_name, int mode
        QString bt_dev_name="";
        int bt_mode=0;

        //http_request_parsing
            int hrp_del=0;//\r\n\r\n -position
            QMap<QByteArray, QByteArray> hrp_headers;
            bool hrp_headers_valid=0;
        //http_request_parsing

        gr_serial *com_port=0;
        gr_bluetooth *gr_bt=0;
    } gr_httprqs_parser;

    void http_request_parsing(gr_httprqs_parser *parser_data);
    void parser_rqst(gr_httprqs_parser *parser_data);

    QTcpServer *server; // указатель на сервер
    QList<gr_httprqs_parser> httprqs_parser; // получатели данных
/////////////////////



public:
    explicit com_to_web(QWidget *parent = 0);
    ~com_to_web();

private:
    Ui::com_to_web *ui;
};

#endif // COM_TO_WEB_H
