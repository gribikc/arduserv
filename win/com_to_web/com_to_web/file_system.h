#include "com_to_web.h"
#include "ui_com_to_web.h"

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#endif // FILE_SYSTEM_H
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    void com_to_web::main_page_request_do(QTcpSocket *socket){
        QByteArray qbt_temp;
        ui->textEdit->insertPlainText("        Main Page request\n");
        socket->write("Main Page request...\n");

        //qbt_temp=QByteArray::number(httprqs_parser.size());
        socket->write(qbt_temp);

        socket->write("\r\n");
        socket->write("\r\n");
        socket->write("END.\r\n");

        QDir dir;
        socket->write("<br>");
        socket->write("File tree:");
        socket->write("<br>");

        if(QSysInfo::productType()=="android"){
            get_tree_file(android_htdocs_patch+"/htdocs/","",socket,android_htdocs_patch);
        }else{
            get_tree_file(dir.currentPath()+"/htdocs/","",socket,dir.currentPath());
        }

        socket->close();
    }
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    void com_to_web::get_tree_file(QString dir_patch, QString prefix_add, QTcpSocket *socket,QString base_dir){
        QDir dir(dir_patch);
        //QDir::setCurrent(base_dir);
        dir.setFilter(QDir::AllDirs | QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setSorting(QDir::Size | QDir::Reversed);
        QFileInfoList list = dir.entryInfoList();

        //qDebug() << dir.entryInfoList().;

        socket->write("");
        for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
            //socket->write(fileInfo.size() );
            if( fileInfo.isDir() && fileInfo.fileName()!=".." && fileInfo.fileName()!="." ){
                socket->write(prefix_add.toLocal8Bit());

                    //socket->write(fileInfo.absolutePath().toLocal8Bit());
                    socket->write(fileInfo.absolutePath().toLocal8Bit().replace(base_dir,""));
                    socket->write("/");
                        socket->write(fileInfo.fileName().toLocal8Bit());
                    socket->write("/");

                socket->write("\n<br>");
                get_tree_file( dir.absoluteFilePath( fileInfo.fileName()),(prefix_add+"&nbsp;&nbsp;&nbsp;&nbsp;"),socket,base_dir);
            }else if(fileInfo.isFile()){
                socket->write(prefix_add.toLocal8Bit());

                socket->write("<a href='");
                socket->write(fileInfo.absolutePath().toLocal8Bit().replace(base_dir,""));
                socket->write("/");
                socket->write(fileInfo.fileName().toLocal8Bit());
                socket->write("'>");
                socket->write(fileInfo.fileName().toLocal8Bit());
                socket->write("</a>");

                     socket->write("(");
                socket->write(QString::number(fileInfo.size()).toLocal8Bit());
                    socket->write(")");
                socket->write("\n<br>");
            }
        }
    }
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::htdocs_page_request_do(QStringList list_param,QTcpSocket *socket){
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

    socket->write(file_req.readAll());
    file_req.close();

    socket->close();
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::htdocs_db_write_do(QStringList list_param, QTcpSocket *socket){
    /*QDir dir;
    //QString file_str=dir.currentPath()+"/htdocs/db";//+parser_data->htdocs_file_query.toLocal8Bit();
    QString file_str="";
    if(QSysInfo::productType()=="android"){
        file_str=android_htdocs_patch+"/htdocs/db";
    }else{
        file_str=dir.currentPath()+"/htdocs/db";//+parser_data->htdocs_file_query.toLocal8Bit();
    }

    QStringList fpa=list_param->htdocs_file_query.split("/");
    for(int i=3;i<fpa.size();i++){
        file_str=file_str+"/"+fpa[i].toLocal8Bit();
    }
    QFile file_req(file_str);

    file_req.setFileName(file_str);
    QString nfn=file_str+"_"+QDateTime::currentDateTime().toString("ddMMyyyyHHmmss");//QTime::currentTime().toString() ;
    file_req.rename(nfn);
    file_req.setFileName(file_str);

    file_req.open(QIODevice::WriteOnly);
    QByteArray  data_to_send=list_param->InData.right(list_param->InData.size()-list_param->hrp_del);
    file_req.write(data_to_send);
    file_req.close();

    ui->textEdit->insertPlainText("        DB WR complite\n");

    //htdocs_page_request_do(parser_data);
    list_param->socket->write("\r\n");
    list_param->socket->write("\r\n");
    list_param->socket->write("END.\r\n");

    list_param->socket->close();*/
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////