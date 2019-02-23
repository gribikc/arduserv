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
        QTcpSocket  *socket;
        QByteArray  InData;
        bool com_parser_valid=0;
        int com_num;
        int com_speed;
        int com_bits;
        int com_par;

        gr_serial *com_port;
        gr_bluetooth *gr_bt;
    } gr_httprqs_parser;

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
