#ifndef COM_TO_WEB_H
#define COM_TO_WEB_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>


    //GPS
    //#include <QGeoSatelliteInfo>
    //#include <QGeoCoordinate>
    //#include <QGeoPositionInfo>
    //#include <QtPositioning>
    //#include <QGeoPositionInfoSource>

    //EXT
    #include "gr_serial/gr_serial.h"
    #include "gr_bluetooth/gr_bluetooth.h"
    #include "gr_gps/gr_gps.h"




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

        QString htdocs_file_query="";

        bool main_page_parser_valid=0;
        bool htdocs_page_request_do=0;
        bool htdocs_db_write_do=0;

        int is_dev_dublicate_id=-1;

        //http_request_parsing
            int hrp_del=0;//\r\n\r\n -position
            QMap<QByteArray, QByteArray> hrp_headers;
            int hrp_headers_valid=0;
        //http_request_parsing

        //
        int external_write_request=0;

        //GPS
        bool gps_request_do=0;
        //void gps_positionnew(const QGeoPositionInfo &info);
        //QGeoPositionInfoSource *gps_source_pis;

        gr_serial *com_port=0;
        gr_bluetooth *gr_bt=0;
    } gr_httprqs_parser;

    void http_request_parsing(gr_httprqs_parser *parser_data);
    void parser_rqst(gr_httprqs_parser *parser_data);
    void postget_request_parsing(gr_httprqs_parser *parser_data);
    void find_device_and_do(gr_httprqs_parser *parser_data);

    void main_page_request_do(gr_httprqs_parser *parser_data);
    void htdocs_page_request_do(gr_httprqs_parser *parser_data);

    void htdocs_db_write_do(gr_httprqs_parser *parser_data);

    void get_tree_file(QString dir_patch, QString prefix_add, gr_httprqs_parser *parser_data, QString base_dir);

    QString android_htdocs_patch="/storage/3262-3934/com_to_web/";

    QTcpServer *server; // указатель на сервер
    QList<gr_httprqs_parser> httprqs_parser; // получатели данных

    //GPS
    gr_gps gr_gps_point;
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
