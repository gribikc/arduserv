#include "gr_data_source.h"
#include <gr_logger/gr_logger.h>

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/// CONSTRUCTOR
    gr_data_source::gr_data_source(QString type, QString dev_name){
        this->type=type;
        this->dev_name=dev_name;
    }
    ////////////////////////////////////////////////////////////////////////////
    gr_data_source::gr_data_source(QString type, QString dev_name, void *client){
        this->type=type;
        this->dev_name=dev_name;

        add_client(client);
    }
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/// ADD/SUB client
    void gr_data_source::add_client(void *client){
        client_list.append(static_cast<GR_http_client*>(client));
        connect(static_cast<QTcpSocket*>(client), &QTcpSocket::stateChanged, this, &gr_data_source::client_stateChanged);
        connect(static_cast<QTcpSocket*>(client), &QTcpSocket::readyRead, this, &gr_data_source::client_readyRead);
        client_added();
    }
    void gr_data_source::sub_client(void *client){
        client_list.removeOne(static_cast<GR_http_client*>(client));
        if(client_list.size()==0){
            no_more_client();
        }
    }
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/// SEND TO ALL
    void gr_data_source::send_data_to_client(QByteArray *data){
        for(int i=0;i<client_list.size();i++){
            if( client_list.at(i)->state() != QAbstractSocket::UnconnectedState ){
                client_list.at(i)->write(*data);
            }else{
                client_list.removeAt(i);
                i--;
            }
        }
        if(client_list.size()==0){
            no_more_client();
        }
    }
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/// client EVENT
    void gr_data_source::client_readyRead(){
        QObject * object = QObject::sender();
        QTcpSocket *client = static_cast<QTcpSocket *>(object);
        qDebug()<<"New Data from Client;";//!!!
    }
    ////////////////////////////////////
    ////////////////////////////////////
    ////////////////////////////////////
    void gr_data_source::client_stateChanged(){
        QObject * object = QObject::sender();
        QTcpSocket *client = static_cast<QTcpSocket *>(object);
        if (client->state() == QAbstractSocket::UnconnectedState){
           GR_logger::log(this,"DS Client Disconnected");
           sub_client(client);
        }
    }
////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
    void gr_data_source::close_all_client(){
        for (int i=0;i<client_list.size();i++) {
            client_list.at(i)->close();
        }
    }
////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
void gr_data_source::data_was_sended(){
    for (int i=0;i<client_list.size();i++) {
        if(client_list.at(i)->list_param[3].toUpper()=="W"){
            client_list.at(i)->close();
        }
    }
}
