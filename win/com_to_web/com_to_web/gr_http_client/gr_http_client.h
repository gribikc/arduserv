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

class gr_http_client : public QObject
{
    Q_OBJECT
public:
    explicit gr_http_client(QTcpSocket  *socket);

    QTcpSocket  *socket=0;
    QByteArray  indata=0;
    //http_request_parsing
        int hrp_del=0;//\r\n\r\n -position
        QMap<QByteArray, QByteArray> hrp_headers;
        bool hrp_headers_valid=0;
    //http_request_parsing

        int is_rsw(QString name);
        QStringList get_list_param();
public slots:
    void readyRead(); // обработчик входящих данных
    void stateChanged(); // обработчик изменения состояния вещающего

    void http_request_parsing();

signals:
    void requestComplete(gr_http_client *gr_http_client);//QMap<QByteArray, QByteArray> *hrp_headers,


};

#endif // GR_HTTP_CLIENT_H
