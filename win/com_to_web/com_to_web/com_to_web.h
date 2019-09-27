#ifndef COM_TO_WEB_H
#define COM_TO_WEB_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QNetworkInterface>

    //EXT
    #include "gr_logger/gr_logger.h"
    //#include "gr_data_source/gr_data_source.h"
    #include "gr_dev_manager/gr_dev_manager.h"
    #include "gr_http_client/gr_http_client.h"
    #include "gr_serial/gr_serial.h"
    #include "gr_bluetooth/gr_bluetooth.h"
    #include "gr_gps/gr_gps.h"
    #include "gr_sensor/gr_sensor.h"




namespace Ui {
class com_to_web;
}


class com_to_web : public QMainWindow
{
    Q_OBJECT
/////////////////////
public slots:
    void incommingConnection(); // обработчик входящего подключения
    //void readyRead(); // обработчик входящих данных
    //void stateChanged(); // обработчик изменения состояния вещающего
    void client_requestComplete(GR_http_client *http_client);//QMap<QByteArray, QByteArray> *hrp_headers,
public:
    void gr_sock_srv_start();


    //void http_request_parsing(gr_httprqs_parser *parser_data);
    //void parser_rqst(gr_httprqs_parser *parser_data);
    //void postget_request_parsing(gr_httprqs_parser *parser_data);
    //void find_device_and_do(gr_httprqs_parser *parser_data);

    void main_page_request_do(QTcpSocket *socket);
    void get_tree_file(QString dir_patch, QString prefix_add, QTcpSocket *socket, QString base_dir);
    void htdocs_page_request_do(QStringList list_param, QTcpSocket *socket);
    void htdocs_db_write_do(QStringList list_param, QTcpSocket *socket);


    QString android_htdocs_patch="/storage/3262-3934/com_to_web";

    QTcpServer *server; // указатель на сервер
    //QList<gr_httprqs_parser> httprqs_parser; // получатели данных

    QList<void*> test;

    gr_dev_manager dev_manager;

    //GPS
    //gr_gps gr_gps_point;
    //ROT_SENS
    //gr_rotation gr_rot_sens_point;
/////////////////////



public:
    explicit com_to_web(QWidget *parent = 0);
    ~com_to_web();

private slots:
    void on_pushButton_clicked();

private:
    Ui::com_to_web *ui;
};

#endif // COM_TO_WEB_H
