#include "gr_data_source.h"

////////////////////////////////////////////////////////////////////////////
    gr_data_source::gr_data_source(){
        //
    }
////////////////////////////////////////////////////////////////////////////
    gr_data_source::gr_data_source(QTcpSocket *socket){
        add_socket(socket);
    }
////////////////////////////////////////////////////////////////////////////
    void gr_data_source::add_socket(QTcpSocket *socket){
        socket_listeners.append(socket);
        socket_added();
    }
///////////////////////////////////////////////////////////
    void gr_data_source::send_data_to_sockets(QByteArray *data){
        for(int i=0;i<socket_listeners.size();i++){
            if( socket_listeners.at(i)->state() != QAbstractSocket::UnconnectedState ){
                socket_listeners.at(i)->write(*data);
            }else{
                socket_listeners.removeAt(i);
                i--;
            }
        }
        if(socket_listeners.size()==0){
            no_more_sockets();
        }
    }
///////////////////////////////////////////////////////////
//
//
