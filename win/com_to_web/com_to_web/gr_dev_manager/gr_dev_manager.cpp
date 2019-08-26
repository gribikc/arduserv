#include "gr_dev_manager.h"

gr_dev_manager::gr_dev_manager(QObject *parent) : QObject(parent)
{

}
//
//
//
    void gr_dev_manager::add_client(QString type, QStringList list_param, QTcpSocket *socket){
        bool is_dev_find=0;
        gr_data_source *dev;
        for (int i = 0; i < gr_devices.size(); i++) {
            dev=static_cast <gr_data_source*>(gr_devices.at(i));
            if (dev->type == type && dev->dev_name==list_param[4]){
                qDebug() << "Device Is opened;";
                dev->add_client(socket);
                is_dev_find=1;
            }
        }
        if(is_dev_find==0){
            if(type=="COM"){
                gr_serial *dev_new=new gr_serial(QString(list_param.at(4)).toInt(),QString(list_param.at(5)).toInt(),socket);
                gr_devices.append(dev_new);
                connect(dev_new,&QObject::destroyed,this,&gr_dev_manager::dev_was_destroyed);
                qDebug() << "Create New Device;";
            }
        }
    }
//
//
//
    void gr_dev_manager::dev_was_destroyed(){
        QObject * object = QObject::sender();
        //QTcpSocket *socket = static_cast<QTcpSocket *>(object);
        for (int i = 0; i < gr_devices.size(); i++) {
            if(gr_devices.at(i) == static_cast<void*>(object) ){
                gr_devices.removeAt(i);
                qDebug() << "Device Was Removed";
            }
        }
    }
//
//
//
