#ifndef GR_HTTP_CLIENT_H
#define GR_HTTP_CLIENT_H

#include <QtCore>
#include <QObject>
#include <QCoreApplication>

#include <QTcpServer>
#include <QTcpSocket>

#include <QByteArray>
#include <QDataStream>

#include <QDebug>

#include "gr_socket/gr_socket.h"
#include "gr_tcpsocket/gr_tcpsocket.h"


//class GR_http_client  : public QObject
//{
//    Q_OBJECT

//class GR_http_client  : public QTcpSocket{
class GR_http_client  : public QObject{
    Q_OBJECT
public:
    explicit GR_http_client(int sdscrp);
    //explicit GR_http_client(QTcpSocket  *socket):QTcpSocket(this);
    gr_socket *socket;
    //QTcpSocket  *socket=nullptr;
    QByteArray  indata="";
    int contentlength=0;
    //http_request_parsing
        int hrp_del=0;//\r\n\r\n -position
        QMap<QByteArray, QByteArray> hrp_headers;
        bool hrp_headers_valid=0;
        QStringList list_param;
        QString ip_addr=0;
    //http_request_parsing

        int is_rsw(QString name);
        QStringList get_list_param();
        void send_html_header();
        void send_data_header();
        void send_neutral_header();
        void send_css_header();
        void send_js_header();
public slots:
    void readyRead(); // обработчик входящих данных
    void disconnected(); // обработчик изменения состояния вещающего

    void http_request_parsing();

signals:
    void requestComplete(GR_http_client *gr_http_client);
    void dataComplete(GR_http_client *gr_http_client);

};

#endif // GR_HTTP_CLIENT_H
