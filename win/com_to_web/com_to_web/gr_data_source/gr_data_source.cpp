#include "gr_data_source.h"

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/// CONSTRUCTOR
    gr_data_source::gr_data_source(QString type, QString dev_name){
        this->type=type;
        this->dev_name=dev_name;
    }
    ////////////////////////////////////////////////////////////////////////////
    gr_data_source::gr_data_source(QString type, QString dev_name, QTcpSocket *socket){
        this->type=type;
        this->dev_name=dev_name;
        add_socket(socket);
    }
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/// ADD/SUB SOCKET
    void gr_data_source::add_socket(QTcpSocket *socket){
        sockets_list.append(socket);
        connect(socket, &QTcpSocket::stateChanged, this, &gr_data_source::socket_stateChanged);
        connect(socket, &QTcpSocket::readyRead, this, &gr_data_source::socket_readyRead);
        socket_added();
    }
    void gr_data_source::sub_socket(QTcpSocket *socket){
        sockets_list.removeOne(socket);
        if(sockets_list.size()==0){
            no_more_sockets();
        }
    }
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/// SEND TO ALL
    void gr_data_source::send_data_to_sockets(QByteArray *data){
        for(int i=0;i<sockets_list.size();i++){
            if( sockets_list.at(i)->state() != QAbstractSocket::UnconnectedState ){
                sockets_list.at(i)->write(*data);
            }else{
                sockets_list.removeAt(i);
                i--;
            }
        }
        if(sockets_list.size()==0){
            no_more_sockets();
        }
    }
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/// SOCKET EVENT
    void gr_data_source::socket_readyRead(){
        QObject * object = QObject::sender();
        QTcpSocket *socket = static_cast<QTcpSocket *>(object);
        qDebug()<<"New Data from Socket;";//!!!
    }
    ////////////////////////////////////
    ////////////////////////////////////
    ////////////////////////////////////
    void gr_data_source::socket_stateChanged(){
        QObject * object = QObject::sender();
        QTcpSocket *socket = static_cast<QTcpSocket *>(object);
        if (socket->state() == QAbstractSocket::UnconnectedState){
           qDebug()<<"Socket Disconnected;";
           sub_socket(socket);
        }
    }
////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
