#include "gr_dev_manager.h"

gr_dev_manager::gr_dev_manager(QObject *parent) : QObject(parent)
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /* 0      /1      /2          /3          /4      /5
    *--------------------------------------------------------------------------------
    *  ---главная страница(FILE,HTML,AJAX),(htdocs/main.html)||(htdocs/index.html)---
    *+ null   /
    *  ---файловая система(FILE-RAW)-------------------------------------------------
    *+ null   /htdocs /(d/i/r/fi.le)
    *  ---системные инструменты(JSON,HTML,RAW)---------------------------------------
    *+ null   /sys    /tree       /(h,j,r,...)
    *  null   /sys    /log        /(h,j,r,...)
    *  null   /sys    /status     /(h,j,r,...)
    *  null   /sys    /echo       /(h,j,r,...)
    *  null   /sys    /speedtest  /(h,j,r,...)
    *  null   /sys    /mes_hub    /(h,j,r,...)
    *  null   /sys    /ping       /(h,j,r,...)
    *  null   /sys    /sock_conn  /(h,j,r,...)
    *  ---база данных(JSON,RAW)------------------------------------------------------
    *  null   /db     /(r,w,s)    /(name)
    *Устройства(RAW,JSON)-------------------------------------------------------
    *+ null   /dev    /com        /(w,r,s,l)  /(num)  /(speed)/
    *  null   /dev    /sens       /(w,r,s)    /(type) /
    *+ null   /dev    /bt         /(w,r,s,l)  /(name) /(0,1,2,3)
    *+ null   /dev    /gps        /(w,r,s)    /
    *--------------------------------------------------------------------------------
    *  0      /1      /2          /3          /4      /5
    *                 /type       /mode       /name   /params
    */
    void gr_dev_manager::add_client(GR_http_client *http_client){
        QStringList list_param=http_client->get_list_param();

        bool is_dev_find=0;
        gr_data_source *dev=nullptr;
        void *dev_new=nullptr;

        qDebug() << "DevManager add_client";
        for(int i=list_param.size();i<10;i++){
            list_param.append("");
        }

        QString dev_type=list_param.at(2).toUpper();
        QString dev_mode=list_param.at(3).toUpper();
        QString dev_name=list_param.at(4);
        QString dev_param_z=list_param.at(5);
        //
        ////DEV_MOD
        if(dev_mode==""){
            dev_mode="R";
        }

        for (int i = 0; i < gr_devices.size(); i++) {//поиск такогоже устройства
            dev=static_cast <gr_data_source*>(gr_devices.at(i));
            if(dev->type == dev_type && dev->dev_name==dev_name && dev_name!="" && dev_mode!="L"){
                qDebug() << "Device Is opened;";
                dev->add_client(http_client);
                dev->write_data(&http_client->indata);
                is_dev_find=1;
            }
        }

        if(!is_dev_find){//нет такогоже устройства
            if(dev_type=="COM"){
                dev_new=new gr_serial(dev_name.toInt(),dev_param_z.toInt(),dev_mode,http_client);
            }else if (dev_type=="BT") {
                dev_new=new GR_bluetooth(dev_name,0,http_client);
            }else if(dev_type=="GPS"){
                dev_new=new gr_gps(http_client);
            }else{
                http_client->write("404 Device not found.");
                http_client->close();
            }

            if(dev_new!=nullptr){
                qDebug() << "Dev add tolist";
                gr_devices.append(dev_new);
                dev=static_cast <gr_data_source*>(dev_new);
                dev->write_data(&http_client->indata);

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
