#include "com_to_web.h"
#include "file_system.h"
#include "ui_com_to_web.h"

QList<QString> GR_logger::m_messages = {};
QList<GR_logger::data_log> GR_logger::log_info = {};

com_to_web::com_to_web(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::com_to_web)
{
    ui->setupUi(this);

    ui->textEdit->insertPlainText("Start...\n");
    gr_sock_srv_start();

}

com_to_web::~com_to_web()
{
    delete ui;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void com_to_web::gr_sock_srv_start(){
    server = new QTcpServer();//this
    server->listen(QHostAddress::Any, 3128);
    if(server->isListening()){
        ui->textEdit->insertPlainText("Socket start PORT:3128\n");

        ui->textEdit->insertPlainText("IP:\n");
        QList<QHostAddress> addr = QNetworkInterface::allAddresses();
        for(int i=0;i<addr.size();i++){
            ui->textEdit->insertPlainText(addr.at(i).toString());
            ui->textEdit->insertPlainText("\n");
        }
        server->setMaxPendingConnections(9999);
        connect(server, &QTcpServer::newConnection, this, &com_to_web::incommingConnection);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::incommingConnection(){ // обработчик подключений
    QTcpSocket *socket = server->nextPendingConnection();//QTcpSocket
    qintptr sdscrp=socket->socketDescriptor();

    GR_http_client *abv=new GR_http_client(sdscrp);
    //connect(abv,&GR_http_client::requestComplete, this,&com_to_web::client_requestComplete);
    connect(abv,&GR_http_client::dataComplete, this,&com_to_web::client_requestComplete);

    //socket->peerAddress();
    //QString a=QString(socket->peerName());
    ui->textEdit->insertPlainText("Client connected...\n");

    //qDebug() << "Client connected;";
    //GR_logger::log("Client connected");
    GR_logger::log(abv,"Client connected;");
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::client_requestComplete(GR_http_client *http_client){
    QStringList list_param=http_client->get_list_param();
    //////////////////////////       ///////
    if(http_client->is_rsw("/dev")>0){
        http_client->send_data_header();
        dev_manager.add_client(http_client);
    //////////////////////////////  ////////
    }else if(http_client->is_rsw("/sys/tcp/")>0){
        http_client->send_data_header();
        new gr_tcp_client(http_client);
        //http_client->close();
    }else if(http_client->is_rsw("/")==2){
        http_client->send_html_header();
        http_client->write("Main Page!");
        GR_logger::log(this,"CtW Main Page");
        http_client->close();
    ////////////////////////////////        ///////
    }else if(http_client->is_rsw("/sys/tree")>0){
        http_client->send_html_header();
        if(QSysInfo::productType()=="android"){
            get_tree_file(android_htdocs_patch+"/htdocs/","",http_client,android_htdocs_patch);
        }else{
            QDir dir;
            get_tree_file(dir.currentPath()+"/htdocs/","",http_client,dir.currentPath());
        }
        GR_logger::log(this,"CtW Htdocs Tree");
        http_client->close();
    ////////////////////////////////     ////////
    }else if(http_client->is_rsw("/htdocs")>0){
        http_client->send_neutral_header();
        htdocs_page_request_do(list_param,http_client);
        GR_logger::log(this,"CtW Page Send");
        http_client->close();
    ////////
    }else if(http_client->is_rsw("/favicon.ico")==2){
        http_client->send_html_header();
        http_client->write("Nice try to get favicon.ico :)))");
        GR_logger::log(this,"CtW TTG favicon.ico");
        http_client->close();
    }else if(http_client->is_rsw("/sys/log")>0){
        http_client->send_html_header();
        if(http_client->is_rsw("/sys/log/c")>0){
            GR_logger::clear();
        }else{
            GR_logger::send_log_to_socket_json(http_client);
        }
        GR_logger::log(this,"CtW GET Log");
        http_client->close();
    }else{
        http_client->send_html_header();
        http_client->write("400 Bad Request!<br>\n");
        http_client->write("Try:<br>\n");
        http_client->write("/                                   <br>\n");
        http_client->write("/htdocs/(d/i/r/fi.le)               <br>\n");
        http_client->write("/sys/tree/(h,j,r,...)               <br>\n");
        http_client->write("/db/(r,w,s)/(name)                  <br>\n");
        http_client->write("/dev/com/(w,r,s,l)/(num)/(speed)/   <br>\n");
        http_client->write("/dev/sens/(w,r,s)/(type)/           <br>\n");
        http_client->write("/dev/bt/(w,r,s,l)/(name)            <br>\n");
        http_client->write("/dev/gps/(w,r,s)/                   <br>\n");

        GR_logger::log(this,"CtW Error 400");
        http_client->close();
    }

    //http_client->destroyed();
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::on_pushButton_clicked(){
    ui->textEdit->clear();
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
