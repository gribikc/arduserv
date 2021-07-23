#include "com_to_web.h"
//#include "file_system.h"
//#include "ui_com_to_web.h"


QList<QString> GR_logger::m_messages = {};
QList<GR_logger::data_log> GR_logger::log_info = {};

com_to_web::com_to_web(QWidget *parent) :
    QObject(parent)//,
    //ui(new Ui::com_to_web)
{

}

com_to_web::~com_to_web()
{
    this->deleteLater();
    qDebug() << "CTW off";
    //!!!delete ui;
}

void com_to_web::init(){
    //!!!ui->setupUi(this);

    //!!!ui->textEdit->insertPlainText("Start...\n");
    emit info(0,"Start...\n");

    gr_web_server=new GR_web_server();
    QObject::connect(gr_web_server,&GR_web_server::info,this,[&](int type,QString str){emit info(type,str);});
    gr_web_server->init();

    registaration_sys();
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//void com_to_web::client_requestComplete(GR_http_client *http_client){
//    qDebug() << "REQ done";
//    QStringList list_param=http_client->get_list_param();
//    //////////////////////////       ///////
//    //////////////////////////       ///////
//    if(http_client->is_rsw("/dev")>0){
//        http_client->send_data_header();
//        dev_manager.add_client(http_client);
//        GR_logger::log(this,"CtW Dev");
//    //////////////////////////////  ////////
//    }else if(http_client->is_rsw("/sys/tcp/")>0){
//        http_client->send_data_header();
//        new gr_tcp_client(http_client);
//        GR_logger::log(this,"CtW Tcp");
//    //////////////////////////////  ////////
//    }else if(http_client->is_rsw("/sys/udp/")>0){
//        http_client->send_data_header();
//        new gr_udp_client(http_client);
//        //http_client->close();
//        GR_logger::log(this,"CtW UDP");
//    ////////////////////////////////        ///////
//    }else if(http_client->is_rsw("/sys/tree")>0){
//        QDir dir;
//        http_client->send_html_header();
//        if(QSysInfo::productType()=="android"){
//            get_tree_file(android_htdocs_patch+"/htdocs/","",http_client,android_htdocs_patch);
//        }else{
//            get_tree_file(dir.currentPath()+"/htdocs/","",http_client,dir.currentPath());
//        }
//        GR_logger::log(this,"CtW Htdocs Tree");
//        http_client->socket->close();
//    ////////////////////////////////     ////////
//    }else if(http_client->is_rsw("/sys/log")>0){
//        http_client->send_html_header();
//        if(http_client->is_rsw("/sys/log/c")>0){
//            GR_logger::clear();
//        }else{
//            GR_logger::send_log_to_socket_json(http_client);
//        }
//        GR_logger::log(this,"CtW GET Log");
//        http_client->socket->close();
//    }else if(http_client->is_rsw("/sys/settings")>0){   //    /sys/settings/(r),w/(j),l,p,/
//        http_client->send_html_header();
//
//        if(http_client->is_rsw("/sys/settings/c")>0){
//            settings.clear_settings("GR_web_server");
//            http_client->socket->write("Ok clear;");
//        }else if(http_client->is_rsw("/sys/settings/w/j")>0){
//            conf_var.clear();
//            conf_var.operator=(settings.create_arr_from_json(http_client->indata));
//            settings.save_settings("GR_web_server",&conf_var);
//        }else if(http_client->is_rsw("/sys/settings/edit.html")==2){
//            //Q_INIT_RESOURCE(resources);
//            QFile file(":/settings_editor.html");
//            file.open(QIODevice::ReadOnly);
//            http_client->socket->write(file.readAll());
//            file.close();
//        }else{
//            http_client->socket->write(settings.create_json_from_arr(conf_var).toLocal8Bit());
//        }
//
//        GR_logger::log(this,"CtW GET Log");
//        http_client->socket->close();
//        //////////////////////////////  ////////
//    }else if(http_client->is_rsw("/sys/gen/")>0){
//        //http_client->send_data_header();
//        http_client->send_neutral_header();
//        new data_generator(http_client);
//        GR_logger::log(this,"CtW GEN");
//    }else if(http_client->is_rsw("/db/w")>0){
//        http_client->send_html_header();
//        htdocs_db_write_do(http_client);
//        GR_logger::log(this,"CtW DB Write");
//        http_client->socket->close();
//    ////////
//    }else if(http_client->is_rsw("/favicon.ico")==2){
//        http_client->send_html_header();
//        http_client->socket->write("Nice try to get favicon.ico :)))");
//        GR_logger::log(this,"CtW TTG favicon.ico");
//        http_client->socket->close();
//    }else if(http_client->is_rsw("/")==2){
//        http_client->send_html_header();
//        http_client->socket->write("Main Page!");
//        GR_logger::log(this,"CtW Main Page");
//        http_client->socket->close();
//    }else if(http_client->is_rsw("/htdocs")>0){
//        //http_client->send_neutral_header();
//        //http_client->send_html_header();
//        /*if(http_client->hrp_headers[]){
//
//        }else{
//            http_client->send_neutral_header();
//        }*/
//
//        /*if(list_param[list_param.size()-1].endsWith("css")){
//            http_client->send_css_header();
//        }else if(list_param[list_param.size()-1].endsWith("js")){
//            http_client->send_js_header();
//        }else if(list_param[list_param.size()-1].endsWith("json")){
//                http_client->send_json_header();
//        }else{
//            http_client->send_neutral_header();
//        }*/
//        http_client->send_file_header(list_param[list_param.size()-1]);
//        htdocs_page_request_do(list_param,http_client);
//        GR_logger::log(this,"CtW Page Send");
//        http_client->socket->close();
//        ////////////////////////////////     ////////
//    }else{//тут проверять наличие файла в htdocs и редиректить
//        http_client->send_html_header();
//        http_client->socket->write("400 Bad Request!<br>\n");
//        http_client->socket->write("Try:<br>\n");
//        http_client->socket->write("/                                   <br>\n");
//        http_client->socket->write("/htdocs/(d/i/r/fi.le)               <br>\n");
//        http_client->socket->write("/db/(r,w,s)/(name)                  <br>\n");
//        http_client->socket->write("<a href=\"/sys/tree\">/sys/tree/(h,j,r,...)</a> -Дерево HtDocs               <br>\n");
//        http_client->socket->write("<a href=\"/sys/settings/edit.html\">/sys/settings</a>                       <br>\n");
//        http_client->socket->write("<a href=\"/dev/com/l\">/dev/com/(w,r,s,l)/(num)/(speed)/</a>   <br>\n");
//        http_client->socket->write("/dev/sens/(w,r,s)/(type)/           <br>\n");
//        http_client->socket->write("<a href=\"/dev/bt/l\">/dev/bt/(w,r,s,l)/(name)</a>            <br>\n");
//        http_client->socket->write("<a href=\"/dev/gps/r\">/dev/gps/(w,r,s)/</a>                   <br>\n");
//
//        GR_logger::log(this,"CtW Error 400");
//        http_client->socket->close();
//    }
//
//    //http_client->destroyed();
//}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::registaration_sys(){
    /*reg_on("/reg_on",StartsWith,SingleShot,HTMLHeader,[](GR_http_client *http_client){
        http_client->socket->write("reg_on");
        qDebug() << "reg_on";
    });*/

    gr_web_server->reg_on("/dev",GR_web_server::StartsWith,GR_web_server::Continuous,GR_web_server::DataHeader,[&](GR_http_client *http_client){
        dev_manager.add_client(http_client);
        GR_logger::log(this,"CtW Dev");
    });

    gr_web_server->reg_on("/sys/tcp",GR_web_server::StartsWith,GR_web_server::Continuous,GR_web_server::DataHeader,[&](GR_http_client *http_client){
        new gr_tcp_client(http_client);
        GR_logger::log(this,"CtW Tcp");
    });

    gr_web_server->reg_on("/sys/udp",GR_web_server::StartsWith,GR_web_server::Continuous,GR_web_server::DataHeader,[&](GR_http_client *http_client){
        new gr_udp_client(http_client);
        GR_logger::log(this,"CtW Tcp");
    });

    gr_web_server->reg_on("/sys/gen/",GR_web_server::StartsWith,GR_web_server::Continuous,GR_web_server::NeutralHeader,[&](GR_http_client *http_client){
        new data_generator(http_client);
        GR_logger::log(this,"CtW GEN");
    });

}
