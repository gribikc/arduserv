#include "gr_dev_manager.h"

gr_dev_manager::gr_dev_manager(QObject *parent) : QObject(parent)
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*  0      /1      /2          /3          /4      /5
    *--------------------------------------------------------------------------------
    *  ---главная страница(FILE,HTML,AJAX),(htdocs/main.html)||(htdocs/index.html)---
    *  null   /
    *  ---файловая система(FILE-RAW)-------------------------------------------------
    *  null   /htdocs /(d/i/r/fi.le)
    *  ---системные инструменты(JSON,HTML,RAW)---------------------------------------
    *  null   /sys    /tree       /(h,j,r,...)
    *  null   /sys    /tree       /(h,j,r,...)
    *  ---база данных(JSON,RAW)------------------------------------------------------
    *  null   /db     /(r,w,s)    /(name)
    *  ---устройства(RAW,JSON)-------------------------------------------------------
    *  null   /dev    /com        /(w,r,s,l)  /(num)  /(speed)/
    *  null   /dev    /sens       /(w,r,s)    /(type) /
    *  null   /dev    /bt         /(w,r,s,l)  /(name)
    *  null   /dev    /gps        /(w,r,s)    /
    *--------------------------------------------------------------------------------
    *
    *
    */
    void gr_dev_manager::add_client(QString type, QStringList list_param,QByteArray *indata,QTcpSocket *socket){
        bool is_dev_find=0;
        gr_data_source *dev=nullptr;
        void *dev_new=nullptr;

        for (int i = 0; i < gr_devices.size(); i++) {//поиск такогоже устройства
            dev=static_cast <gr_data_source*>(gr_devices.at(i));
            if (dev->type == type && dev->dev_name==list_param[4]){
                qDebug() << "Device Is opened;";
                dev->add_client(socket);
                dev->write_data(indata);
                is_dev_find=1;
            }
        }
        if(!is_dev_find){//нет такогоже устройства
            if(type=="COM"){
                dev_new=new gr_serial(QString(list_param.at(4)).toInt(),QString(list_param.at(5)).toInt(),socket);
            }//else if(type=="GPS"){
            //
            //}else if (typy=="BT") {
            //
            //}

            if(dev_new!=nullptr){
                gr_devices.append(dev_new);
                dev=static_cast <gr_data_source*>(dev_new);
                dev->write_data(indata);

                connect(dev,&QObject::destroyed,this,&gr_dev_manager::dev_was_destroyed);
                qDebug() << "Create New Device;";
            }
        }
    }
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
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
