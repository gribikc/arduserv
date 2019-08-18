#include "gr_data_source.h"

////////////////////////////////////////////////////////////////////////////
    void gr_data_source::add_listener(QTcpSocket *socket){
        socket_listeners.append(socket);
        listener_added();
    }
///////////////////////////////////////////////////////////
    void gr_data_source::send_data_to_listeners(QByteArray *data){
        if(socket_listeners.size()==0){
            //STOP & CLOSE
            //no mo listeners
        }else{
            for(int i=0;i<socket_listeners.size();i++){
                if( socket_listeners.at(i)->state() != QAbstractSocket::UnconnectedState ){
                    socket_listeners.at(i)->write(data);
                }else{
                    socket_listeners.removeAt(i);
                    i--;
                }
            }
        }
    }
///////////////////////////////////////////////////////////
//
//
