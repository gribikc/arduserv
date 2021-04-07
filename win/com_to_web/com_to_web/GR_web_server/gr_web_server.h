#ifndef GR_WEB_SERVER_H
#define GR_WEB_SERVER_H

#include <QObject>
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QNetworkInterface>
#include <QWebSocketServer>
#include <QWebSocket>

#include "gr_http_client/gr_http_client.h"
#include "gr_settings.h"
#include "gr_socket/gr_socket.h"
#include "gr_tcpsocket/gr_tcpsocket.h"
#include "gr_web_socket/gr_web_socket.h"
#include "gr_logger/gr_logger.h"

class GR_web_server : public QObject
{
    Q_OBJECT
public slots:
    void onNewWebs_connect();
    void incommingConnection();
    void client_requestComplete(GR_http_client *http_client);
public:
    explicit GR_web_server(QWidget *parent = 0);
    ~GR_web_server();
    void init();

    void gr_sock_srv_start();

    enum HeaderType {
            NoHeader        = 0,
            DataHeader      = 1,
            HTMLHeader      = 2,
            NeutralHeader   = 3,
            CSSHeader       = 4,
            JSHeader        = 5,
            JSONHeader      = 6
    };
    enum ComparisonType {
            StartsWith     = 0,
            Matches        = 1
    };
    enum ModeType {
            Continuous     = 0,
            SingleShot     = 1
    };

    void main_page_request_do(GR_http_client *socket);
    void get_tree_file(QString dir_patch, QString prefix_add, GR_http_client *socket, QString base_dir);
    void htdocs_page_request_do(QStringList list_param, GR_http_client *socket);
    void htdocs_db_write_do(GR_http_client *socket);

    QString android_htdocs_patch="/storage/emulated/0/com_to_web";

    QTcpServer *server; // указатель на сервер
    QWebSocketServer *webs_server;
    GR_settings settings;

    QMap<QString, QVariant> conf_var;

    struct sub_request{
        QString str;
        int type;//0:>0,1:==2
        void (*cb)(GR_http_client *http_client);
        bool single_shot;
        int send_header_type;
    };
    QVector<sub_request> sub_requests;
    //template<typename T>
    //typedef void (*func)(GR_http_client *http_client);
    template<class F>
    void reg_on(QString str,int type,bool single_shot,int send_header_type,const F& cb){//;//void (*cb)(GR_http_client *http_client)
        sub_request temp;
        temp.str=str;
        temp.type=type;
        //temp.cb=cb;//cbt;
        //void (*aaa)(GR_http_client *http_client)=cb;
        temp.single_shot=single_shot;
        temp.send_header_type=send_header_type;
        sub_requests<<temp;
    }

    int reg_off(QString str);
    int reg_off(int num);
    void registaration_sys();

signals:
   void info(int type,QString str);
};

#endif // GR_WEB_SERVER_H
