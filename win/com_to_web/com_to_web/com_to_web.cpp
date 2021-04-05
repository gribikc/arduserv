#include "com_to_web.h"
#include "file_system.h"
//#include "ui_com_to_web.h"


QList<QString> GR_logger::m_messages = {};
QList<GR_logger::data_log> GR_logger::log_info = {};

com_to_web::com_to_web(QWidget *parent) :
    QObject(parent)//,
    //ui(new Ui::com_to_web)
{

}
void com_to_web::init(){
    //!!!ui->setupUi(this);

    //!!!ui->textEdit->insertPlainText("Start...\n");
    emit info(0,"Start...\n");

    ///////
        if(settings.load_settings(&conf_var)){
            //!!!ui->textEdit->insertPlainText("Setting is valid...\n");
            emit info(0,"Setting is valid...\n");
        }else {
            //!!!ui->textEdit->insertPlainText("Setting is Invalid...Load Default!\n");
            emit info(0,"Setting is Invalid...Load Default!\n");
            conf_var["tcp_listen_port"]=3128;
            conf_var["wbs_listen_port"]=3129;

            conf_var["htdocs_patch"]="/storage/emulated/0/com_to_web";
            QDir dir;
            if(QSysInfo::productType()=="android"){
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
                        //!!!ui->textEdit->insertPlainText("Find SD:");
                        //!!!ui->textEdit->insertPlainText(sdcommonPaths.at(i));
                        //!!!ui->textEdit->insertPlainText("\n");
                        emit info(0,"Find SD:");
                        emit info(0,sdcommonPaths.at(i));
                        emit info(0,"\n");
                        if(!dir.exists(sdcommonPaths.at(i)+"/com_to_web")){
                            dir.mkdir("com_to_web");
                            //!!!ui->textEdit->insertPlainText("Create com_to_web/\n");
                            emit info(0,"Create com_to_web/\n");
                        }else{
                            //!!!ui->textEdit->insertPlainText("Find com_to_web/\n");
                            emit info(0,"Find com_to_web/\n");
                        }
                        dir.setPath(sdcommonPaths[i]+"/com_to_web");
                        if(!dir.exists()){continue;}else{
                            if(!dir.exists(sdcommonPaths.at(i)+"/com_to_web/htdocs")){
                                //!!!ui->textEdit->insertPlainText("Create com_to_web/htdocs\n");
                                emit info(0,"Create com_to_web/htdocs\n");
                                dir.mkdir("htdocs");
                            }else {
                                //!!!ui->textEdit->insertPlainText("Find com_to_web/htdocs\n");
                                emit info(0,"Find com_to_web/htdocs\n");
                            }
                            dir.setPath(sdcommonPaths[i]+"/com_to_web/htdocs");
                            if(!dir.exists()){continue;}else{
                                if(!dir.exists(sdcommonPaths.at(i)+"/com_to_web/htdocs/db")){
                                    //!!!ui->textEdit->insertPlainText("Create com_to_web/htdocs/db\n");
                                    emit info(0,"Create com_to_web/htdocs/db\n");
                                    dir.mkdir("db");
                                }else{
                                    //!!!ui->textEdit->insertPlainText("Find com_to_web/htdocs/db\n");
                                    emit info(0,"Find com_to_web/htdocs/db\n");
                                }
                                dir.setPath(sdcommonPaths[i]+"/com_to_web/htdocs/db");
                                if(!dir.exists()){continue;}else{
                                    //!!!ui->textEdit->insertPlainText("Find SD, htdocs and db");
                                    //!!!ui->textEdit->insertPlainText("\n");
                                    emit info(0,"Find SD, htdocs and db\n");
                                    conf_var["htdocs_patch"]=sdcommonPaths[i]+"/com_to_web/";
                                    break;
                                }
                            }
                        }
                    }
                }
            }else{
                conf_var["htdocs_patch"]=dir.currentPath();
                emit info(0,"Dir patch error;\n");
                emit info(0,conf_var["htdocs_patch"].toString());
                emit info(0,"\n |- ");
            }
        }
    /////

        reg_on("/reg_on",0,1,HeaderType::HTMLHeader,[](GR_http_client *http_client){
            http_client->socket->write("reg_on");
            qDebug() << "reg_on";
        });

    gr_sock_srv_start();
}

com_to_web::~com_to_web()
{
    this->deleteLater();
    qDebug() << "CTW off";
    //!!!delete ui;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void com_to_web::gr_sock_srv_start(){
    qDebug() << "Server start";
    emit info(0,"Server start\n");
    server = new QTcpServer();//this
    server->listen(QHostAddress::Any, conf_var["tcp_listen_port"].toInt());//3128

    webs_server=new QWebSocketServer("CTW", QWebSocketServer::NonSecureMode, this);
    webs_server->listen(QHostAddress::Any, conf_var["wbs_listen_port"].toInt());
    connect(webs_server, &QWebSocketServer::newConnection,this, &com_to_web::onNewWebs_connect);

    emit info(0,"WebSocket Port: 3129\n");

    if(server->isListening()){
        qDebug() << "Server is open";
        //!!!ui->textEdit->insertPlainText("Socket start PORT: ");
        //!!!ui->textEdit->insertPlainText(conf_var["tcp_listen_port"].toString());
        //!!!ui->textEdit->insertPlainText("\n");
        emit info(0,"HttpSocket start Port: ");
        emit info(0,conf_var["tcp_listen_port"].toString());
        emit info(0,"\n");


        //!!!ui->textEdit->insertPlainText("HTDocsPatch: ");
        //!!!ui->textEdit->insertPlainText(conf_var["htdocs_patch"].toString());
        //!!!ui->textEdit->insertPlainText("\n |- ");
        emit info(0,"HTDocsPatch: ");
        emit info(0,conf_var["htdocs_patch"].toString());
        emit info(0,"\n |- ");

        QDir dir(conf_var["htdocs_patch"].toString()+"/htdocs");//!!!&db
        if (!dir.exists()){
            QDir dir(conf_var["htdocs_patch"].toString());
            if (!dir.exists()){
                //!!!ui->textEdit->insertPlainText("Invalid");
                emit info(0,"Invalid");
            }else{
                //!!!ui->textEdit->insertPlainText("Need to Create htdocs dir in patch");
                emit info(0,"Need to Create htdocs dir in patch");
            }
        }else{
            //!!!ui->textEdit->insertPlainText("Valid");
            emit info(0,"Valid");
        }
        //!!!ui->textEdit->insertPlainText("\n");
        emit info(0,"\n");

        //!!!ui->textEdit->insertPlainText("IP:\n");
        emit info(0,"IP:\n");
        QList<QHostAddress> addr = QNetworkInterface::allAddresses();
        for(int i=0;i<addr.size();i++){
            //!!!ui->textcEdit->insertPlainText(" |- ");
            //!!!ui->textEdit->insertPlainText(addr.at(i).toString());
            //!!!ui->textEdit->insertPlainText("\n");
            emit info(0," |- ");
            emit info(0,addr.at(i).toString());
            emit info(0,"\n");
        }

        server->setMaxPendingConnections(9999);
        connect(server, &QTcpServer::newConnection, this, &com_to_web::incommingConnection);
    }else {
        //!!!ui->textEdit->insertPlainText("Socket not Start :(\n");
        emit info(0,"Socket not Start :(\n");
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::onNewWebs_connect(){
    qDebug() << "WBS new";
    QWebSocket *pSocket = webs_server->nextPendingConnection();
     disconnect(pSocket,nullptr,nullptr,nullptr);
    GR_http_client *abv=new GR_http_client();
    connect(abv,&GR_http_client::dataComplete, this,&com_to_web::client_requestComplete);
    abv->init(pSocket);
    GR_logger::log(abv,"CtW Client connected;");
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::incommingConnection(){ // обработчик подключений
    qDebug() << "HTTP new";
    QTcpSocket *socket = server->nextPendingConnection();//QTcpSocket
    disconnect(socket,nullptr,nullptr,nullptr);

    GR_http_client *abv=new GR_http_client();
    //connect(abv,&GR_http_client::requestComplete, this,&com_to_web::client_requestComplete);
      connect(abv,&GR_http_client::dataComplete, this,&com_to_web::client_requestComplete);
    abv->init(socket);
    //socket->peerAddress();
    //QString a=QString(socket->peerName());

    GR_logger::log(abv,"CtW Client connected;");
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::client_requestComplete(GR_http_client *http_client){
    qDebug() << "REQ done";
    QStringList list_param=http_client->get_list_param();
    //////////////////////////       ///////
    for(int i=0;i<sub_requests.size();i++){
        int a=http_client->is_rsw(sub_requests[i].str);
        int b=http_client->is_rsw(sub_requests[i].str);
        if( (sub_requests[i].type==0 && http_client->is_rsw(sub_requests[i].str)>0 ) ||
            (sub_requests[i].type==1 && http_client->is_rsw(sub_requests[i].str)==2)   ){
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
                    case HeaderType::CSSHeader:
                        http_client->send_css_header();
                        break;
                    case HeaderType::JSHeader:
                        http_client->send_js_header();
                        break;
                    case HeaderType::JSONHeader:
                        http_client->send_json_header();
                        break;
                    default:
                        break;
                }

                sub_requests[i].cb(http_client);
                if(sub_requests[i].single_shot){
                    http_client->socket->close();
                }
        }
    }
    //////////////////////////       ///////
    if(http_client->is_rsw("/dev")>0){
        http_client->send_data_header();
        dev_manager.add_client(http_client);
        GR_logger::log(this,"CtW Dev");
    //////////////////////////////  ////////
    }else if(http_client->is_rsw("/sys/tcp/")>0){
        http_client->send_data_header();
        new gr_tcp_client(http_client);
        GR_logger::log(this,"CtW Tcp");
    //////////////////////////////  ////////
    }else if(http_client->is_rsw("/sys/udp/")>0){
        http_client->send_data_header();
        new gr_udp_client(http_client);
        //http_client->close();
        GR_logger::log(this,"CtW UDP");
    ////////////////////////////////        ///////
    }else if(http_client->is_rsw("/sys/tree")>0){
        QDir dir;
        http_client->send_html_header();
        if(QSysInfo::productType()=="android"){
            get_tree_file(android_htdocs_patch+"/htdocs/","",http_client,android_htdocs_patch);
        }else{
            get_tree_file(dir.currentPath()+"/htdocs/","",http_client,dir.currentPath());
        }
        GR_logger::log(this,"CtW Htdocs Tree");
        http_client->socket->close();
    ////////////////////////////////     ////////
    }else if(http_client->is_rsw("/sys/log")>0){
        http_client->send_html_header();
        if(http_client->is_rsw("/sys/log/c")>0){
            GR_logger::clear();
        }else{
            GR_logger::send_log_to_socket_json(http_client);
        }
        GR_logger::log(this,"CtW GET Log");
        http_client->socket->close();
    }else if(http_client->is_rsw("/sys/settings")>0){   //    /sys/settings/(r),w/(j),l,p,/
        http_client->send_html_header();

        if(http_client->is_rsw("/sys/settings/c")>0){
            settings.clear_settings();
            http_client->socket->write("Ok clear;");
        }else if(http_client->is_rsw("/sys/settings/w/j")>0){
            conf_var.clear();
            conf_var.operator=(settings.create_arr_from_json(http_client->indata));
            settings.save_settings(&conf_var);
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
        http_client->socket->close();
        //////////////////////////////  ////////
    }else if(http_client->is_rsw("/sys/gen/")>0){
        http_client->send_data_header();
        new data_generator(http_client);
        GR_logger::log(this,"CtW GEN");
    }else if(http_client->is_rsw("/db/w")>0){
        http_client->send_html_header();
        htdocs_db_write_do(http_client);
        GR_logger::log(this,"CtW DB Write");
        http_client->socket->close();
    ////////
    }else if(http_client->is_rsw("/favicon.ico")==2){
        http_client->send_html_header();
        http_client->socket->write("Nice try to get favicon.ico :)))");
        GR_logger::log(this,"CtW TTG favicon.ico");
        http_client->socket->close();
    }else if(http_client->is_rsw("/")==2){
        http_client->send_html_header();
        http_client->socket->write("Main Page!");
        GR_logger::log(this,"CtW Main Page");
        http_client->socket->close();
    }else if(http_client->is_rsw("/htdocs")>0){
        //http_client->send_neutral_header();
        //http_client->send_html_header();
        /*if(http_client->hrp_headers[]){

        }else{
            http_client->send_neutral_header();
        }*/

        if(list_param[list_param.size()-1].endsWith("css")){
            http_client->send_css_header();
        }else if(list_param[list_param.size()-1].endsWith("js")){
            http_client->send_js_header();
        }else if(list_param[list_param.size()-1].endsWith("json")){
                http_client->send_json_header();
        }else{
            http_client->send_neutral_header();
        }
        htdocs_page_request_do(list_param,http_client);
        GR_logger::log(this,"CtW Page Send");
        http_client->socket->close();
        ////////////////////////////////     ////////
    }else{//тут проверять наличие файла в htdocs и редиректить
        http_client->send_html_header();
        http_client->socket->write("400 Bad Request!<br>\n");
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

        GR_logger::log(this,"CtW Error 400");
        http_client->socket->close();
    }

    //http_client->destroyed();
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
int com_to_web::reg_on(QString str,int type,bool single_shot,int send_header_type,void (*cb)(GR_http_client *http_client)){
    sub_request temp;
    temp.str=str;
    temp.type=type;
    temp.cb=cb;
    temp.single_shot=single_shot;
    temp.send_header_type=send_header_type;
    sub_requests<<temp;
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
