#ifndef COM_TO_WEB_H
#define COM_TO_WEB_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QNetworkInterface>
#include <QWebSocketServer>
#include <QWebSocket>

    //EXT
    #include "gr_logger/gr_logger.h"
    //#include "gr_data_source/gr_data_source.h"
    #include "gr_dev_manager/gr_dev_manager.h"
    #include "gr_http_client/gr_http_client.h"
    #include "gr_serial/gr_serial.h"
    #include "gr_bluetooth/gr_bluetooth.h"
    #include "gr_gps/gr_gps.h"
    #include "gr_sensor/gr_sensor.h"
    #include "gr_tcp_client/gr_tcp_client.h"
    #include "gr_udp_client/gr_udp_client.h"
    #include "gr_settings.h"
    #include "gr_socket/gr_socket.h"
    #include "gr_tcpsocket/gr_tcpsocket.h"
    #include "gr_web_socket/gr_web_socket.h"



/*namespace Ui {
class com_to_web;
}*/


class com_to_web : public QObject//QMainWindow
{
    Q_OBJECT
/////////////////////
public slots:
    void onNewWebs_connect();
    //void processTextMessage(QString message);
    //void processBinaryMessage(QByteArray message);
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

    void main_page_request_do(GR_http_client *socket);
    void get_tree_file(QString dir_patch, QString prefix_add, GR_http_client *socket, QString base_dir);
    void htdocs_page_request_do(QStringList list_param, GR_http_client *socket);
    void htdocs_db_write_do(GR_http_client *socket);

    // /storage/sdcard0/
    // /storage/emulated/0/
    //QString android_htdocs_patch="/storage/3262-3934/com_to_web";
    QString android_htdocs_patch="/storage/emulated/0/com_to_web";

    QTcpServer *server; // указатель на сервер
    QWebSocketServer *webs_server;
    //QList<gr_httprqs_parser> httprqs_parser; // получатели данных

    QList<void*> test;

    gr_dev_manager dev_manager;

    GR_settings settings;

    /*struct {
       QString android_htdocs_patch="/storage/emulated/0/com_to_web";
       QString htdocs_patch="/";
       qint16 tcp_listen_port=3128;
    } conf_var;*/

    QMap<QString, QVariant> conf_var;


    //GPS
    //gr_gps gr_gps_point;
    //ROT_SENS
    //gr_rotation gr_rot_sens_point;
/////////////////////



public:
    explicit com_to_web(QWidget *parent = 0);
    ~com_to_web();

private slots:

/*private:
    Ui::com_to_web *ui;*/
};
/*QString[] sdcommonPaths = {
            "/mnt/Removable/MicroSD",
            "/storage/removable/sdcard1", // !< Sony Xperia Z1
            "/Removable/MicroSD", // Asus ZenPad C
            "/removable/microsd",
            "/external_sd", // Samsung
            "/_ExternalSD", // some LGs
            "/storage/extSdCard", // later Samsung
            "/storage/extsdcard", // Main filesystem is case-sensitive; FAT isn't.
            "/mnt/extsd", // some Chinese tablets, e.g. Zeki
            "/storage/sdcard1", // If this exists it's more likely than sdcard0 to be removable.
            "/mnt/extSdCard",
            "/mnt/sdcard/external_sd",
            "/mnt/external_sd",
            "/storage/external_SD",
            "/storage/ext_sd", // HTC One Max
            "/mnt/sdcard/_ExternalSD",
            "/mnt/sdcard-ext",

            "/sdcard2", // HTC One M8s
            "/sdcard1", // Sony Xperia Z
            "/mnt/media_rw/sdcard1",   // 4.4.2 on CyanogenMod S3
            "/mnt/sdcard", // This can be built-in storage (non-removable).
            "/sdcard",
            "/storage/sdcard0",
            "/emmc",
            "/mnt/emmc",
            "/sdcard/sd",
            "/mnt/sdcard/bpemmctest",
            "/mnt/external1",
            "/data/sdext4",
            "/data/sdext3",
            "/data/sdext2",
            "/data/sdext",
            "/storage/microsd" //ASUS ZenFone 2
    };*/
#endif // COM_TO_WEB_H
