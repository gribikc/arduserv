#include "gr_web_server.h"
#include "gr_web_server_file_system.h"

GR_web_server::GR_web_server(QWidget *parent) : QObject(parent){

}

GR_web_server::~GR_web_server(){
    this->deleteLater();
    qDebug() << "CTW off";
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///
void GR_web_server::init(){
    //!!!ui->setupUi(this);
    emit info(0,"Start...\n");
    ///////
        //auto a=settings.get_list("GR_web_server");//!!! HZ CZ
        if(settings.load_settings("GR_web_server",&conf_var)){
            emit info(0,"Setting is valid...\n");
        }else {
            emit info(0,"Setting is Invalid...Load Default!\n");
            conf_var["tcp_listen_port"]=3128;
            conf_var["wbs_listen_port"]=3129;
            conf_var["save_db_change"]=0;

            QDir dir;
            if(QSysInfo::productType()=="android"){
                conf_var["htdocs_patch"]="/storage/emulated/0/com_to_web/htdocs";
                QStringList sdcommonPaths = {
                    "/storage/86BB-1D02",
                    "/storage/emulated/0",
                    "/storage/sdcard0/",
                    "/mnt/sdcard",
                    "/storage/extSdCard",
                    "/storage/UsbDriveA",
                    "/storage/UsbDriveB"
                };

                for(int i=0;i<sdcommonPaths.count();i++){
                    dir.setPath(sdcommonPaths.at(i));
                    if (!dir.exists()){continue;}else{//SD find.
                        emit info(0,"Find SD:");
                        emit info(0,sdcommonPaths.at(i));
                        emit info(0,"\n");
                        if(!dir.exists(sdcommonPaths.at(i)+"/com_to_web")){
                            dir.mkdir("com_to_web");
                            emit info(0,"Create com_to_web/\n");
                        }else{
                            emit info(0,"Find com_to_web/\n");
                        }
                        dir.setPath(sdcommonPaths[i]+"/com_to_web");
                        if(!dir.exists()){continue;}else{
                            if(!dir.exists(sdcommonPaths.at(i)+"/com_to_web/htdocs")){
                                emit info(0,"Create com_to_web/htdocs\n");
                                dir.mkdir("htdocs");
                            }else {
                                emit info(0,"Find com_to_web/htdocs\n");
                            }
                            dir.setPath(sdcommonPaths[i]+"/com_to_web/htdocs");
                            if(!dir.exists()){continue;}else{
                                if(!dir.exists(sdcommonPaths.at(i)+"/com_to_web/htdocs/db")){
                                    emit info(0,"Create com_to_web/htdocs/db\n");
                                    dir.mkdir("db");
                                }else{
                                    emit info(0,"Find com_to_web/htdocs/db\n");
                                }
                                dir.setPath(sdcommonPaths[i]+"/com_to_web/htdocs/db");
                                if(!dir.exists()){continue;}else{
                                    emit info(0,"Find SD, htdocs and db\n");
                                    conf_var["htdocs_patch"]=sdcommonPaths[i]+"/com_to_web";
                                    break;
                                }
                            }
                        }
                    }
                }
            }else{
                conf_var["htdocs_patch"]=dir.currentPath();//conf_var["htdocs_patch"]="/storage/emulated/0/com_to_web";///htdocs/
                //emit info(0,"Dir patch error;\n");
                //emit info(0,conf_var["htdocs_patch"].toString());
                //emit info(0,"\n |- ");
            }
        }
    /////
    registaration_sys();
    gr_sock_srv_start();
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///
void GR_web_server::gr_sock_srv_start(){
    qDebug() << "Server start";
    emit info(0,"Server start\n");
    server = new QTcpServer();//this
    server->listen(QHostAddress::Any, conf_var["tcp_listen_port"].toInt());//3128

    webs_server=new QWebSocketServer("CTW", QWebSocketServer::NonSecureMode, this);
    webs_server->listen(QHostAddress::Any, conf_var["wbs_listen_port"].toInt());
    connect(webs_server, &QWebSocketServer::newConnection,this, &GR_web_server::onNewWebs_connect);

    emit info(0,"WebSocket Port: ");
    emit info(0,conf_var["wbs_listen_port"].toString());
    emit info(0,"\n");

    if(server->isListening()){
        qDebug() << "Server is open";
        emit info(0,"HttpSocket start Port: ");
        emit info(0,conf_var["tcp_listen_port"].toString());
        emit info(0,"\n");

        emit info(0,"HTDocsPatch: ");
        emit info(0,conf_var["htdocs_patch"].toString());
        emit info(0,"\n |- ");

        QDir dir(conf_var["htdocs_patch"].toString()+"/htdocs");//!!!&db
        if (!dir.exists()){
            QDir dir(conf_var["htdocs_patch"].toString());
            if (!dir.exists()){
                emit info(0,"Invalid");
            }else{
                emit info(0,"Need to Create htdocs dir in patch");
            }
        }else{
            emit info(0,"Valid");
        }
        emit info(0,"\n");

        emit info(0,"IP:\n");
        QList<QHostAddress> addr = QNetworkInterface::allAddresses();
        for(int i=0;i<addr.size();i++){
            emit info(0," |- ");
            emit info(0,addr.at(i).toString());
            emit info(0,"\n");
        }

        server->setMaxPendingConnections(9999);
        connect(server, &QTcpServer::newConnection, this, &GR_web_server::incommingConnection);
    }else {
        emit info(0,"Socket not Start :(\n");
    }
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///
void GR_web_server::onNewWebs_connect(){
    qDebug() << "WBS new";
    QWebSocket *socket = webs_server->nextPendingConnection();
    disconnect(socket,nullptr,nullptr,nullptr);

    GR_http_client *abv=new GR_http_client();
    connect(abv,&GR_http_client::dataComplete, this,&GR_web_server::client_requestComplete);
    abv->init(socket);

    GR_logger::log(abv,"CtW Client connected;");
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///
void GR_web_server::incommingConnection(){ // обработчик подключений
    qDebug() << "HTTP new";
    QTcpSocket *socket = server->nextPendingConnection();//QTcpSocket
    disconnect(socket,nullptr,nullptr,nullptr);

    GR_http_client *abv=new GR_http_client();
    connect(abv,&GR_http_client::dataComplete, this,&GR_web_server::client_requestComplete);
    abv->init(socket);

    GR_logger::log(abv,"CtW Client connected;");
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///
void GR_web_server::client_requestComplete(GR_http_client *http_client){
    qDebug() << "REQ done";
    QStringList list_param=http_client->get_list_param();
    //////////////////////////       ///////
    for(int i=0;i<sub_requests.size();i++){
        if( (sub_requests[i].type==ComparisonType::StartsWith   && http_client->is_rsw(sub_requests[i].str)>0 ) ||      //!!!???==1?
            (sub_requests[i].type==ComparisonType::Matches      && http_client->is_rsw(sub_requests[i].str)==2)   ){
            switch(sub_requests[i].send_header_type){
                case HeaderType::NoHeader:
                    break;
                case HeaderType::DataHeader:
                    http_client->send_data_header();
                    break;
                case HeaderType::HTMLHeader:
                    http_client->send_html_header();
                    break;
                case HeaderType::NeutralHeader:
                    http_client->send_neutral_header();
                    break;
                case HeaderType::FileHeader:
                    http_client->send_file_header(list_param[list_param.size()-1]);
                    break;
                default:
                    break;
            }

            sub_requests[i].cb(http_client);
            if(sub_requests[i].single_shot==ModeType::SingleShot){
                http_client->socket->close();
            }
            return;
        }
    }
    //надо бы возможность регистрации события 404
    ///////////////
    //тут проверять наличие файла в htdocs и редиректить
    http_client->send_file_header(list_param[list_param.size()-1]);

    if(list_param[0]!="htdocs"){
        QStringList list_param_s=list_param;
        list_param_s.insert(1,"htdocs");
        if(htdocs_page_request_do(list_param_s,http_client)){
            GR_logger::log(this,"CtW end page found");
            http_client->socket->close();
            return;
        }
    }
    ///////////////

    //http_client->send_html_header();
    http_client->socket->write("\r\n\r\n");

    http_client->socket->write("404 Not Found!<br>\n");
    http_client->socket->write("Try:<br>\n");
    http_client->socket->write("/                                   <br>\n");
    http_client->socket->write("/htdocs/(d/i/r/fi.le)               <br>\n");
    http_client->socket->write("/db/(r,w,s)/(name)                  <br>\n");
    http_client->socket->write("<a href=\"/sys/tree\">/sys/tree/(h,j,r,...)</a> -Дерево HtDocs               <br>\n");
    http_client->socket->write("<a href=\"/sys/settings/edit.html\">/sys/settings</a>                       <br>\n");
    http_client->socket->write("<a href=\"/dev/com/l\">/dev/com/(w,r,s,l)/(num)/(speed)/</a>   <br>\n");
    http_client->socket->write("/dev/sens/(w,r,s)/(type)/           <br>\n");
    http_client->socket->write("<a href=\"/dev/bt/l\">/dev/bt/(w,r,s,l)/(name)</a>            <br>\n");
    http_client->socket->write("<a href=\"/dev/gps/r\">/dev/gps/(w,r,s)/</a>                   <br>\n");

    GR_logger::log(this,"CtW Error 404");
    http_client->socket->close();
    ///////////////
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///
void GR_web_server::registaration_sys(){
    reg_on("/sys/tree",StartsWith,SingleShot,HTMLHeader,[&](GR_http_client *http_client){
        QDir dir;
        get_tree_file(conf_var["htdocs_patch"].toString()+"\\htdocs","",http_client,conf_var["htdocs_patch"].toString());
        GR_logger::log(this,"CtW Htdocs Tree");
    });
    reg_on("/sys/settings",StartsWith,SingleShot,HTMLHeader,[&](GR_http_client *http_client){
        if(http_client->is_rsw("/sys/settings/c")>0){
            settings.clear_settings("GR_web_server");
            http_client->socket->write("Ok clear;");
        }else if(http_client->is_rsw("/sys/settings/w/j")>0){
            conf_var.clear();
            conf_var.operator=(settings.create_arr_from_json(http_client->indata));
            settings.save_settings("GR_web_server",&conf_var);
        }else if(http_client->is_rsw("/sys/settings/edit.html")==2){
            //Q_INIT_RESOURCE(resources);
            QFile file(":/settings_editor.html");
            file.open(QIODevice::ReadOnly);
            http_client->socket->write(file.readAll());
            file.close();
        }else{
            http_client->socket->write(settings.create_json_from_arr(conf_var).toLocal8Bit());
        }
        GR_logger::log(this,"CtW GET Log");
    });
    reg_on("/sys/log",StartsWith,SingleShot,HTMLHeader,[&](GR_http_client *http_client){
        if(http_client->is_rsw("/sys/log/c")>0){
            GR_logger::clear();
        }else{
            GR_logger::send_log_to_socket_json(http_client);
        }
        GR_logger::log(this,"CtW GET Log");
    });


    reg_on("/",Matches,SingleShot,FileHeader,[&](GR_http_client *http_client){
        //http_client->socket->write("Main Page!");
        QStringList list_param_s=http_client->get_list_param();
        list_param_s[1]="htdocs";
        list_param_s.insert(2,"index.html");
        if(htdocs_page_request_do(list_param_s,http_client)){
            GR_logger::log(this,"CtW end page found");
            http_client->socket->close();
            return;
        }
        http_client->socket->write("Main Page! out of index.html in htdocs!");
        GR_logger::log(this,"CtW Main Page");
    });
    reg_on("/favicon.ico",Matches,SingleShot,HTMLHeader,[&](GR_http_client *http_client){
        http_client->socket->write("Nice try to get favicon.ico :)))");
        GR_logger::log(this,"CtW TTG favicon.ico");
    });
    reg_on("/htdocs",StartsWith,SingleShot,FileHeader,[&](GR_http_client *http_client){//!!! убрать
        QStringList list_param=http_client->get_list_param();
        if(!htdocs_page_request_do(list_param,http_client)){
            http_client->socket->write("404 File Not Found!!!");
        };
        GR_logger::log(this,"CtW Page Send");
    });
    reg_on("/db/w",StartsWith,SingleShot,HTMLHeader,[&](GR_http_client *http_client){
        htdocs_db_write_do(http_client);
        GR_logger::log(this,"CtW DB Write");
    });
}

