#include "com_to_web.h"
#include "ui_com_to_web.h"


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
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::gr_sock_srv_start(){
    server = new QTcpServer();//this
    server->listen(QHostAddress::Any, 3128);
    if(server->isListening()){
        ui->textEdit->insertPlainText("Socket start localhost:3128\n");

        connect(server, &QTcpServer::newConnection, this, &com_to_web::incommingConnection);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::incommingConnection(){ // обработчик подключений
    QTcpSocket *socket = server->nextPendingConnection();//QTcpSocket

    connect(socket, &QTcpSocket::stateChanged, this, &com_to_web::stateChanged); // делаем обработчик изменения статуса сокета
    connect(socket, &QTcpSocket::readyRead, this, &com_to_web::readyRead);

    gr_httprqs_parser temp_gr_httprqs_parser;
    temp_gr_httprqs_parser.socket=socket;
    httprqs_parser << temp_gr_httprqs_parser;


    //socket->peerAddress();
    //QString a=QString(socket->peerName());
    ui->textEdit->insertPlainText("Client connected...\n");

    qDebug() << "Client connected;";

}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::stateChanged(){ // обработчик статуса, нужен для контроля за "вещающим"
    QObject * object = QObject::sender();
    if (!object){
        ui->textEdit->insertPlainText("    Socket error!\n");
        return;
    }
    QTcpSocket * socket = static_cast<QTcpSocket *>(object);
    //printf(state);
    if (socket->state() == QAbstractSocket::UnconnectedState){
       ui->textEdit->insertPlainText("Disconnected;\n");
       for(int i=0;i<httprqs_parser.size();i++){
           if(httprqs_parser[i].socket==socket){
                if(QSysInfo::productType()=="android"){
                    if(httprqs_parser[i].gr_bt!=nullptr){
                        httprqs_parser[i].gr_bt->bt_Socket->close();// disconnectFromService();//disconnected()

                        httprqs_parser[i].gr_bt->bt_discoveryAgent->destroyed();
                        httprqs_parser[i].gr_bt->bt_Socket->destroyed();
                        httprqs_parser[i].gr_bt->destroyed();
                    }
                }else if(QSysInfo::productType()=="windows" && httprqs_parser[i].data_wr==0){
                    if(httprqs_parser[i].com_port!=nullptr){
                        if(httprqs_parser[i].com_port->serial!=nullptr)
                            //httprqs_parser[i].com_port->serial->close();
                            delete(httprqs_parser[i].com_port->serial);
                            //httprqs_parser[i].com_port->serial->de
                        //delete(...)
                    }
                }
                httprqs_parser.removeAt(i);//!!!//!!!
                break;
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::readyRead(){ // обработчик входящих сообщений от "вещающего"
    QObject *object = QObject::sender(); // далее и ниже до цикла идет преобразования "отправителя сигнала" в сокет, дабы извлечь данные
    if (!object){
        ui->textEdit->insertPlainText("    Socket error!\n");
        return;
    }

    QTcpSocket *socket = static_cast<QTcpSocket *>(object);

    for(int i=0;i<httprqs_parser.size();i++){
        if(httprqs_parser[i].socket==socket){
            if(httprqs_parser[i].external_write_request==1){
                //socket->readBufferSize();
                httprqs_parser[i].hrp_del+=socket->readAll().size();//!!!
                httprqs_parser[httprqs_parser[i].is_dev_dublicate_id].com_port->serial->write(socket->readAll());
                if(httprqs_parser[i].hrp_headers["Content-Length"].toInt()==(httprqs_parser[i].InData.size()-httprqs_parser[i].hrp_del)){//!!!
                    httprqs_parser[httprqs_parser[i].is_dev_dublicate_id].external_write_request=0;
                    httprqs_parser[i].socket->write("DATA SENT SUCCESSFUL");
                    httprqs_parser[i].socket->close();
                }
            }else{
                httprqs_parser[i].InData.append(socket->readAll());
                parser_rqst(&httprqs_parser[i]);
            }
            break;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::parser_rqst(gr_httprqs_parser *parser_data){
    //int data_size=parser_data->InData.size();
    QString data=parser_data->InData;
    QString temp;
    QStringList list_line = data.split("\r\n");
    QStringList list_in_line;
    QByteArray qbt_temp;

    if(parser_data->hrp_headers_valid==0 &&  parser_data->hrp_del==0){//пока нечего не нашли
        //Ищем \r\n\r\n и заголовки(урл,контентлен), помечаем размер шапки
        http_request_parsing(parser_data);
    }

    if(parser_data->hrp_headers_valid==1 &&  parser_data->hrp_del!=0){
        //Разбираем урл получаем адрес устройства и прочие параметры
        postget_request_parsing(parser_data);
    }

    if(parser_data->hrp_headers_valid==2){
        //анализируем и делаем
        if(parser_data->com_parser_valid==1 || parser_data->bt_parser_valid==1){
            parser_data->socket->write("HTTP/1.1 200 OK\n");
            parser_data->socket->write("Content-type: text/plan\n");
            parser_data->socket->write("Connection: keep-alive\n");
            parser_data->socket->write("Access-Control-Allow-Origin: *\n");
            parser_data->socket->write("\n");

            find_device_and_do(parser_data);
        }else if(parser_data->main_page_parser_valid==1){
            parser_data->socket->write("HTTP/1.1 200 OK\n");
            parser_data->socket->write("Content-type: text/html\n");
            parser_data->socket->write("Connection: keep-alive\n");
            parser_data->socket->write("Access-Control-Allow-Origin: *\n");
            parser_data->socket->write("\n");

            main_page_request_do(parser_data);
        }else if(parser_data->htdocs_page_request_do==1){
            parser_data->socket->write("HTTP/1.1 200 OK\n");
            //parser_data->socket->write("Content-type: text/html\n");
            parser_data->socket->write("Connection: keep-alive\n");
            parser_data->socket->write("Access-Control-Allow-Origin: *\n");
            parser_data->socket->write("\n");

            htdocs_page_request_do(parser_data);
        }else{
            parser_data->socket->write("HTTP/1.1 200 OK\n");
            parser_data->socket->write("Content-type: text/plan\n");
            parser_data->socket->write("Connection: keep-alive\n");
            parser_data->socket->write("Access-Control-Allow-Origin: *\n");
            parser_data->socket->write("\n");

            ui->textEdit->insertPlainText("        No walid request\n");
            parser_data->socket->write("No walid request...\n");

            qbt_temp=QByteArray::number(httprqs_parser.size());
            parser_data->socket->write(qbt_temp);

            parser_data->socket->write("\r\n");
            parser_data->socket->write("\r\n");
            parser_data->socket->write("END.\r\n");

            parser_data->socket->close();
        }
    }


    /*if(parser_data->hrp_headers_valid==1){
        if(parser_data->hrp_headers["Content-Length"].isDetached()){
            int data_size_in_query=parser_data->hrp_headers["Content-Length"].toInt();
            if(data_size_in_query==(data_size-parser_data->hrp_del)){
                parser_data->socket->close();
            }
        }
    }*/
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::http_request_parsing(gr_httprqs_parser *parser_data){
    QList<QByteArray> header_line = parser_data->InData.split( 0x0D );
    QList<QByteArray> split_line;
    QString temp;

    int data_size=parser_data->InData.size();
    if(data_size>=3 && parser_data->hrp_del==0){//Ищем конец запроса
        for(int i=3;i<data_size;i++){
            if(parser_data->InData[i]==(char)0x0A && parser_data->InData[i-1]==(char)0x0D &&
               parser_data->InData[i-2]==(char)0x0A && parser_data->InData[i-3]==(char)0x0D){
                parser_data->hrp_del=i+1;
            }
        }
    }
    if(parser_data->hrp_del!=0 && parser_data->hrp_headers_valid==0){//Если есть признак завершонного заголовка и еще не обрабатывали
        //Request complite
        //parser_data->socket->write("HTTP/1.1 200 OK\n");
        //parser_data->socket->write("Content-type: text/plan\n");
        //parser_data->socket->write("Connection: keep-alive\n");
        //parser_data->socket->write("Access-Control-Allow-Origin: *\n");
        //parser_data->socket->write("\n");
        ui->textEdit->insertPlainText("        Request complite:\n");

        for(int i=0;i<header_line.size();i++){
            temp=header_line[i];
            if((temp.startsWith("GET ") || temp.startsWith("POST ")) && parser_data->hrp_headers_valid==0){//startsWith
                parser_data->hrp_headers.insertMulti("Query",header_line[i]);
                parser_data->hrp_headers_valid=1;//!!!
            }else if(temp.startsWith("\nContent-Length:")){
                split_line=header_line[i].split(':');
                if(split_line.size()==2){
                    parser_data->hrp_headers.insertMulti("Content-Length",split_line[1]);
                }
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::postget_request_parsing(gr_httprqs_parser *parser_data){
    QStringList list_in_line;
    QByteArray qbt_temp;
    QString temp=parser_data->hrp_headers["Query"];

    parser_data->hrp_headers_valid=2;

    parser_data->data_wr=temp.startsWith("GET /W/") ? 1 : 0;//contains
    parser_data->data_wr=temp.startsWith("POST /W/") ? 1 : 0;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////
        //COM
        if( (temp.startsWith("GET /R/COM/") || temp.startsWith("POST /R/COM/") || temp.startsWith("GET /W/COM/") || temp.startsWith("POST /W/COM/") ) && QSysInfo::productType()=="windows"){       //GET /R/COM/3/57600/
            list_in_line=temp.split("/");
            temp=list_in_line[3];
            parser_data->com_num=temp.toInt();
            temp=list_in_line[4];
            parser_data->com_speed=temp.toInt();

            parser_data->com_parser_valid=1;//!!!
            parser_data->bt_parser_valid=0;
            parser_data->main_page_parser_valid=0;
            parser_data->htdocs_page_request_do=0;
        }
        ///////////////////////////////////
        //BT
        if( (temp.startsWith("GET /R/BT/") || temp.startsWith("POST /W/BT/") || temp.startsWith("GET /R/BT/") || temp.startsWith("POST /W/BT/") ) && QSysInfo::productType()=="android"){        //GET /R/BT/HC-06/
            list_in_line=temp.split("/");
            temp=list_in_line[3];
            parser_data->bt_dev_name=temp;

            parser_data->com_parser_valid=0;
            parser_data->bt_parser_valid=1;
            parser_data->main_page_parser_valid=0;
            parser_data->htdocs_page_request_do=0;
        }
        ///////////////////////////////////
        //MAIN PAGE
        if( (temp.startsWith("GET / HTTP/") || temp.startsWith("POST / HTTP/") ) ){        //GET /R/BT/HC-06/
            parser_data->com_parser_valid=0;
            parser_data->bt_parser_valid=0;
            parser_data->main_page_parser_valid=1;
            parser_data->htdocs_page_request_do=0;
        }
        ///////////////////////////////////
        //PAGE
        if( (temp.startsWith("GET /htdocs") || temp.startsWith("POST /htdocs") ) ){        //GET /R/BT/HC-06/
            list_in_line=temp.split(" ");
            parser_data->htdocs_file_query=list_in_line[1];

            parser_data->com_parser_valid=0;
            parser_data->bt_parser_valid=0;
            parser_data->main_page_parser_valid=0;
            parser_data->htdocs_page_request_do=1;
        }
        ///////////////////////////////////
        //WRITE PAGE

        ///////////////////////////////////
        //GET SYS DATA

}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::find_device_and_do(gr_httprqs_parser *parser_data){
    QByteArray qbt_temp;
    ////////////////////////////////////////////////////////////////////////////////////////////
    for(int i=0;i<httprqs_parser.size();i++){//ищем открытый сокет с тем же именем
        if(QSysInfo::productType()=="windows"){
            if(httprqs_parser[i].socket!=parser_data->socket && httprqs_parser[i].com_num==parser_data->com_num && parser_data->com_parser_valid==1){
                parser_data->is_dev_dublicate_id=i;
                ui->textEdit->insertPlainText("        Dublicate COM find\n");
            }
        }else if(QSysInfo::productType()=="android"){
            if(httprqs_parser[i].socket!=parser_data->socket && httprqs_parser[i].bt_dev_name==parser_data->bt_dev_name && parser_data->bt_parser_valid==1){
                parser_data->is_dev_dublicate_id=i;
                ui->textEdit->insertPlainText("        Dublicate BT find\n");
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////
    if(parser_data->data_wr==0 && parser_data->is_dev_dublicate_id!=-1){//попытка открыть на чтение уже открытое устройство
        parser_data->socket->write("NOT OPEN PORT BUSY");
        parser_data->socket->close();
    }else if(parser_data->data_wr==1 && parser_data->is_dev_dublicate_id!=-1){//попытка записать в открытое устройство
        if(httprqs_parser[parser_data->is_dev_dublicate_id].external_write_request==0){//проверяем не зането ли устройство еще и на запись
            httprqs_parser[parser_data->is_dev_dublicate_id].external_write_request=1; //занимаем устройство

            //
            //QByteArray x("Pineapple");
            //QByteArray y = x.right(5);
            // y == "apple"

            QByteArray  data_to_send=parser_data->InData.right(parser_data->InData.size()-parser_data->hrp_del);//hrp_del

            if(QSysInfo::productType()=="windows"){
                httprqs_parser[parser_data->is_dev_dublicate_id].com_port->serial->write(data_to_send);// !!! //отправляем что есть
                ui->textEdit->insertPlainText("        Send data to serial\n");//LOG
            }else if(QSysInfo::productType()=="android"){
                httprqs_parser[parser_data->is_dev_dublicate_id].gr_bt->bt_Socket->write(data_to_send);// !!! //отправляем что есть
                ui->textEdit->insertPlainText("        Send data to BT\n");//LOG
            }

            if(parser_data->hrp_headers["Content-Length"].toInt()==(parser_data->InData.size()-parser_data->hrp_del) && parser_data->hrp_headers["Content-Length"].isDetached()){//проверям все ли данные отправлены
                httprqs_parser[parser_data->is_dev_dublicate_id].external_write_request=0;
                parser_data->socket->write("DATA SENT SUCCESSFUL");
                parser_data->socket->close();
            }else{
                parser_data->external_write_request=1;//не все данные пришли
            }
        }else{
            parser_data->socket->write("DATA NOT SENT PORT BUSY");
            parser_data->socket->close();
        }
    } else if(parser_data->bt_parser_valid==1 &&  parser_data->com_parser_valid==0 && QSysInfo::productType()=="android"){//BT walid request
        parser_data->gr_bt=new gr_bluetooth;
        parser_data->gr_bt->bt_open(parser_data->bt_dev_name,1,parser_data->socket);
        ui->textEdit->insertPlainText("        Open bt...\n");
    } else if(parser_data->bt_parser_valid==0 &&  parser_data->com_parser_valid==1 && QSysInfo::productType()=="windows"){//COM walid request
        parser_data->com_port=new gr_serial;
        parser_data->com_port->serial_open(parser_data->com_num,parser_data->com_speed,parser_data->socket);
        ui->textEdit->insertPlainText("        Open com...\n");
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::main_page_request_do(gr_httprqs_parser *parser_data){
    QByteArray qbt_temp;
    ui->textEdit->insertPlainText("        Main Page request\n");
    parser_data->socket->write("Main Page request...\n");

    qbt_temp=QByteArray::number(httprqs_parser.size());
    parser_data->socket->write(qbt_temp);

    parser_data->socket->write("\r\n");
    parser_data->socket->write("\r\n");
    parser_data->socket->write("END.\r\n");

    QDir dir;
    parser_data->socket->write("<br>");
    get_tree_file(dir.currentPath()+"/htdocs/","",parser_data,dir.currentPath());

    //parser_data->socket->close();//!!!
    //if(QSysInfo::productType()=="android"){
    //   parser_data->gr_bt=new gr_bluetooth;
    //   parser_data->gr_bt->bt_open("",0,parser_data->socket);
    //}else{
        parser_data->socket->close();
    //}

}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::htdocs_page_request_do(gr_httprqs_parser *parser_data){
    QByteArray qbt_temp;
    ui->textEdit->insertPlainText("        HtDocs Page request\n");

    QDir dir;
    //dir.currentPath()+"/htdocs/";
    QString file_str=dir.currentPath()+parser_data->htdocs_file_query.toLocal8Bit();
    QFile file_req(file_str);///dir.currentPath()+parser_data->htdocs_file_query.toLocal8Bit());
    file_req.open(QIODevice::ReadOnly);

    parser_data->socket->write(file_req.readAll());
    file_req.close();

    parser_data->socket->close();
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::get_tree_file(QString dir_patch, QString prefix_add, gr_httprqs_parser *parser_data,QString base_dir){
    QDir dir(dir_patch);
    //QDir::setCurrent(base_dir);
    dir.setFilter(QDir::AllDirs | QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();

    parser_data->socket->write("");
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        //parser_data->socket->write(fileInfo.size() );
        if( fileInfo.isDir() && fileInfo.fileName()!=".." && fileInfo.fileName()!="." ){
            parser_data->socket->write(prefix_add.toLocal8Bit());

                //parser_data->socket->write(fileInfo.absolutePath().toLocal8Bit());
                parser_data->socket->write(fileInfo.absolutePath().toLocal8Bit().replace(base_dir,""));
                parser_data->socket->write("/");
                    parser_data->socket->write(fileInfo.fileName().toLocal8Bit());
                parser_data->socket->write("/");

            parser_data->socket->write("\n<br>");
            get_tree_file( dir.absoluteFilePath( fileInfo.fileName()),(prefix_add+"&nbsp;&nbsp;&nbsp;&nbsp;"),parser_data,base_dir);
        }else if(fileInfo.isFile()){
            parser_data->socket->write(prefix_add.toLocal8Bit());

            parser_data->socket->write("<a href='");
            parser_data->socket->write(fileInfo.absolutePath().toLocal8Bit().replace(base_dir,""));
            parser_data->socket->write("/");
            parser_data->socket->write(fileInfo.fileName().toLocal8Bit());
            parser_data->socket->write("'>");
            parser_data->socket->write(fileInfo.fileName().toLocal8Bit());
            parser_data->socket->write("</a>");

                 parser_data->socket->write("(");
            parser_data->socket->write(QString::number(fileInfo.size()).toLocal8Bit());
                parser_data->socket->write(")");
            parser_data->socket->write("\n<br>");
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::on_pushButton_clicked(){
    ui->textEdit->clear();
}
