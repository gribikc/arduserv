#ifndef GR_LOGGER_H
#define GR_LOGGER_H
#include <QObject>

#include <QtCore>
#include <QObject>
#include <QCoreApplication>

#include <QTcpServer>
#include <QTcpSocket>

#include <gr_http_client/gr_http_client.h>
#include <gr_data_source/gr_data_source.h>

class GR_logger{
    public:
        /*static void log(QString text) {
            m_messages.append(text);
            qDebug() << m_messages.size();
            qDebug() << text;
        }*///Logger::log("Андрюша-хрюшка");

        //static const QVector<QString>& get();
        //static void clear();

        static void clear(){
            log_info.clear();
        }
        static void log(void* pointer,QString text){
            GR_http_client *client;
            gr_data_source* data_src;

            data_log data;
            client=dynamic_cast <GR_http_client*>(static_cast <QObject*>(pointer));
            data_src=dynamic_cast <gr_data_source*>(static_cast <QObject*>(pointer));

            if(client!=nullptr){
                //data.params.append(client->isOpen() ? "Opened" : "Close");
                data.params.append(client->ip_addr);
                data.params.append(client->hrp_headers.contains("Query") ? ("Q:"+client->hrp_headers["Query"]) :
                                                                      ("I:"+client->indata.left(70).replace("\n","").replace("\r","")));
            }else if(data_src!=nullptr){
                data.params.append("Clients:"+QString::number(data_src->client_list.size()));
                data.params.append(data_src->type);
                data.params.append(data_src->dev_name);
            }

            data.date=QDate::currentDate();
            data.time=QTime::currentTime();
            data.pointer=pointer;
            data.text=text;
            log_info.append(data);
            qDebug() << text;
        }
        static void send_log_to_socket_json(GR_http_client* socket){
            QByteArray qba;
            qba+="[\n";
            for(int i=0;i<log_info.size();i++){
                if(i!=0){qba+=",";}else {qba+="    ";}
                qba+="{\n";
                qba+="        \"pointer\":\"";
                qba+=QString::number((int)log_info.at(i).pointer)+"\",\n";
                qba+="        \"date\":\"";
                qba+=log_info.at(i).date.toString("dd.MM.yyyy")+"\",\n";
                qba+="        \"time\":\"";
                qba+=log_info.at(i).time.toString("hh:mm:ss.zzz")+"\",\n";

                qba+="        \"params\":[\n";
                for (int j=0;j<log_info.at(i).params.size();j++) {
                    if(j!=0){qba+=",\n";}else {qba+="";}
                    qba+="            \""+log_info.at(i).params.at(j)+"\"";
                }
                qba+="\n        ],\n";

                qba+="        \"text\":\"";
                qba+=log_info.at(i).text+"\"";
                qba+="\n    }";
            }
            qba+="\n]";
            socket->socket->write(qba);
        }
    private:
        struct data_log{
            QDate date;
            QTime time;
            void* pointer;
            QString text;
            QList<QString> params;
        };
        static QList<QString> m_messages;
        static QList<data_log> log_info;
};

//QList<QString> GR_logger::m_messages = {};


#endif // GR_LOGGER_H
