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
        GR_http_client *ukz=static_cast<GR_http_client*>(client);
        //write_data(&ukz->indata);
    }
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/// ADD/SUB client
    void gr_data_source::add_client(void *client){
        gr_socket *ukz=static_cast<gr_socket*>(static_cast<GR_http_client*>(client)->socket);
        client_list.append(static_cast<GR_http_client*>(client));
        //connect(static_cast<QTcpSocket*>(client), &QTcpSocket::disconnected, this, &gr_data_source::client_stateChanged);
        //connect(static_cast<QTcpSocket*>(client), &QTcpSocket::readyRead, this, &gr_data_source::client_readyRead);
        disconnect(ukz,&gr_socket::disconnected,nullptr,nullptr);
        disconnect(ukz,&gr_socket::readyRead,nullptr,nullptr);

        connect(ukz, &gr_socket::disconnected, this, &gr_data_source::client_stateChanged);
        connect(ukz, &gr_socket::readyRead, this, &gr_data_source::client_readyRead);
        client_added();
    }
    void gr_data_source::sub_client(void *client){
        //client_list.removeOne(static_cast<GR_http_client*>(client));
        for(int i=0;i<client_list.size();i++){
            if( client_list.at(i)->socket == client  ){
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
/// SEND TO ALL
    void gr_data_source::send_data_to_client(QByteArray *data){
        for(int i=0;i<client_list.size();i++){
            if( client_list.at(i)->socket->state() != QAbstractSocket::UnconnectedState ){
                client_list.at(i)->socket->write(data);
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
        gr_socket *client = static_cast<gr_socket *>(object);
        QByteArray data=client->readAll();
        write_data(&data);
        qDebug()<<"New Data from Client;";//!!!
    }
    ////////////////////////////////////
    ////////////////////////////////////
    ////////////////////////////////////
    void gr_data_source::client_stateChanged(){
        QObject * object = QObject::sender();
        gr_socket *client = static_cast<gr_socket *>(object);
        if (client->state() == QAbstractSocket::UnconnectedState){
           GR_logger::log(this,"DS Client Disconnected");
           sub_client(client);
        }
    }
////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
    void gr_data_source::close_all_client(){
        GR_logger::log(this,"DS Close All Clients");
        for (int i=0;i<client_list.size();i++) {
            client_list.at(i)->socket->close();
        }
    }
////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
void gr_data_source::data_was_sended(){
    GR_logger::log(this,"DS Data Was Send");
    for (int i=0;i<client_list.size();i++) {
        if(client_list.at(i)->list_param[3].toUpper()=="W"){
            client_list.at(i)->socket->close();
        }
    }
}
