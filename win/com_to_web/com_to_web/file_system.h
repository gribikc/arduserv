#include "com_to_web.h"
#include "ui_com_to_web.h"

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#endif // FILE_SYSTEM_H
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    void com_to_web::main_page_request_do(GR_http_client *socket){
        QByteArray qbt_temp;
        ui->textEdit->insertPlainText("        Main Page request\n");
        socket->socket->write("Main Page request...\n");

        //qbt_temp=QByteArray::number(httprqs_parser.size());
        socket->socket->write(qbt_temp);

        socket->socket->write("\r\n");
        socket->socket->write("\r\n");
        socket->socket->write("END.\r\n");

        QDir dir;
        socket->socket->write("<br>");
        socket->socket->write("File tree:");
        socket->socket->write("<br>");

        if(QSysInfo::productType()=="android"){
            get_tree_file(android_htdocs_patch+"/htdocs/","",socket,android_htdocs_patch);
        }else{
            get_tree_file(dir.currentPath()+"/htdocs/","",socket,dir.currentPath());
        }

        socket->socket->close();
    }
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    void com_to_web::get_tree_file(QString dir_patch, QString prefix_add, GR_http_client *socket,QString base_dir){
        QDir dir(dir_patch);
        if (!dir.exists()){
            socket->socket->write("Dir not found<br>\n");
            socket->socket->write(dir_patch.toLocal8Bit());
        }

        dir.setFilter(QDir::AllDirs | QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setSorting(QDir::Size | QDir::Reversed);
        QFileInfoList list = dir.entryInfoList();

        socket->socket->write("");
        for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
            //socket->write(fileInfo.size() );
            if( fileInfo.isDir() && fileInfo.fileName()!=".." && fileInfo.fileName()!="." ){
                socket->socket->write(prefix_add.toLocal8Bit());

                    //socket->write(fileInfo.absolutePath().toLocal8Bit());
                    socket->socket->write(fileInfo.absolutePath().toLocal8Bit().replace(base_dir,""));
                    socket->socket->write("/");
                        socket->socket->write(fileInfo.fileName().toLocal8Bit());
                    socket->socket->write("/");

                socket->socket->write("\n<br>");
                get_tree_file( dir.absoluteFilePath( fileInfo.fileName()),(prefix_add+"&nbsp;&nbsp;&nbsp;&nbsp;"),socket,base_dir);
            }else if(fileInfo.isFile()){
                socket->socket->write(prefix_add.toLocal8Bit());

                socket->socket->write("<a href='");
                socket->socket->write(fileInfo.absolutePath().toLocal8Bit().replace(base_dir,""));
                socket->socket->write("/");
                socket->socket->write(fileInfo.fileName().toLocal8Bit());
                socket->socket->write("'>");
                socket->socket->write(fileInfo.fileName().toLocal8Bit());
                socket->socket->write("</a>");

                     socket->socket->write("(");
                socket->socket->write(QString::number(fileInfo.size()).toLocal8Bit());
                    socket->socket->write(")");
                socket->socket->write("\n<br>");
            }
        }
    }
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::htdocs_page_request_do(QStringList list_param,GR_http_client *socket){
    QByteArray qbt_temp;
    QString file="";
    ui->textEdit->insertPlainText("        HtDocs Page request\n");

    for(int i=1;i<list_param.size();i++){
        file+="/"+list_param.at(i);
    }

    QDir dir;
    //dir.currentPath()+"/htdocs/";
    QString file_str="";
    if(QSysInfo::productType()=="android"){
        file_str=android_htdocs_patch+file.toLocal8Bit();
    }else{
        file_str=dir.currentPath()+file.toLocal8Bit();
    }
    //QString file_str=dir.currentPath()+parser_data->htdocs_file_query.toLocal8Bit();
    QFile file_req(file_str);///dir.currentPath()+parser_data->htdocs_file_query.toLocal8Bit());
    file_req.open(QIODevice::ReadOnly);

    socket->socket->write(file_req.readAll());
    file_req.close();
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::htdocs_db_write_do(GR_http_client *socket){
    QDir dir;
    //QString file_str=dir.currentPath()+"/htdocs/db";//+parser_data->htdocs_file_query.toLocal8Bit();
    QString file_str="";
    if(QSysInfo::productType()=="android"){
        file_str=android_htdocs_patch+"/htdocs/db";
    }else{
        file_str=dir.currentPath()+"/htdocs/db";//+parser_data->htdocs_file_query.toLocal8Bit();
    }

    //QStringList fpa=list_param->htdocs_file_query.split("/");
    //static_cast<GR_http_client*>(socket);
    QStringList fpa=static_cast<GR_http_client*>(socket)->list_param;//  .htdocs_file_query.split("/");
    for(int i=3;i<fpa.size();i++){
        file_str=file_str+"/"+fpa[i].toLocal8Bit();
    }

    QFile(file_str).setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOther);
    QFile file_req(file_str);
    file_req.setPermissions(file_str,QFileDevice::WriteOther);
    //Если такойфайлужеесть сохраняем копию
        file_req.setFileName(file_str);
        QString nfn=file_str+"_"+QDateTime::currentDateTime().toString("ddMMyyyyHHmmss");//QTime::currentTime().toString() ;
        file_req.rename(nfn);
    //Сохраняем данные в фал
        //file_req.open(QIODevice::ReadOnly);
        //socket->write(file_req.readAll());
        //QFileDevice::WriteOther

        file_req.setFileName(file_str);
        file_req.open(QIODevice::ReadWrite);
        file_req.setPermissions(file_str,QFileDevice::WriteOther);
        if(file_req.exists()){qDebug() << "существует_1";}else{qDebug() << "нет файла_0";}
        if(file_req.isWritable()){qDebug() << "записываемый_1";}else{qDebug() << "не открыть для записи_0";}
        qDebug() << file_req.permissions(file_str);
        qDebug() << file_req.errorString();

        QByteArray  data_to_send=static_cast<GR_http_client*>(socket)->indata;
        file_req.write(data_to_send);
        file_req.close();

    ui->textEdit->insertPlainText("        DB WR complite\n");

    //Отчет
        socket->socket->write("\r\n");
        socket->socket->write("\r\n");
        socket->socket->write("END.\r\n");
    //Завершаем
        socket->socket->close();
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
