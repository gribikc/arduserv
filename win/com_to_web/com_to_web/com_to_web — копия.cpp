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
               //httprqs_parser[i].com_port->serial->close();
               //if(httprqs_parser[i].bt_parser_valid==1){
                    if(QSysInfo::productType()=="android"){
                        if(httprqs_parser[i].gr_bt->bt_Socket!=0){
                            httprqs_parser[i].gr_bt->bt_Socket->close();// disconnectFromService();//disconnected()
                        }
                        httprqs_parser[i].gr_bt->bt_discoveryAgent->destroyed();
                        httprqs_parser[i].gr_bt->bt_Socket->destroyed();
                        httprqs_parser[i].gr_bt->destroyed();
                    }else if(QSysInfo::productType()=="windows" && httprqs_parser[i].data_wr==0){
                        if(httprqs_parser[i].com_port!=nullptr){
                            if(httprqs_parser[i].com_port->serial!=nullptr)
                                //httprqs_parser[i].com_port->serial->close();
                                delete(httprqs_parser[i].com_port->serial);
                                //httprqs_parser[i].com_port->serial->de
                            //delete(...)
                        }
                    }
               //}

               httprqs_parser.removeAt(i);
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
            httprqs_parser[i].InData.append(socket->readAll());
            parser_rqst(&httprqs_parser[i]);
            break;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::parser_rqst(gr_httprqs_parser *parser_data){
    int data_size=parser_data->InData.size();
    QString data=parser_data->InData;
    QString temp;
    QStringList list_line = data.split("\r\n");
    QStringList list_in_line;
    int int_temp;
    QByteArray qbt_temp;


    parser_data->com_parser_valid=0;
    parser_data->bt_parser_valid=0;
    parser_data->data_wr=0;

    if(parser_data->InData[data_size-1]==(char)0x0A && parser_data->InData[data_size-2]==(char)0x0D &&
       parser_data->InData[data_size-3]==(char)0x0A && parser_data->InData[data_size-4]==(char)0x0D     ){
        //Request complite
            parser_data->socket->write("HTTP/1.1 200 OK\n");
            parser_data->socket->write("Content-type: text/plan\n");
            parser_data->socket->write("Connection: keep-alive\n");
            parser_data->socket->write("Access-Control-Allow-Origin: *\n");
            parser_data->socket->write("\n");
            ui->textEdit->insertPlainText("        Request complite:\n");
        //Parsing request
            for(int i=0;i<list_line.size();i++){
                temp=list_line[i];
                //data_wr

                //http://localhost:3128/R/COM/5/115200/
                if((temp.contains("GET /R/COM/") || temp.contains("POST /R/COM/") || temp.contains("GET /W/COM/") || temp.contains("POST /W/COM/")) && QSysInfo::productType()=="windows"){       //GET /R/COM/3/57600/
                    parser_data->data_wr=temp.contains("GET /W/COM/") ? 1 : 0;
                    list_in_line=temp.split("/");
                    temp=list_in_line[3];
                    parser_data->com_num=temp.toInt();
                    temp=list_in_line[4];
                    parser_data->com_speed=temp.toInt();
                    parser_data->com_parser_valid=1;//!!!
                    parser_data->bt_parser_valid=0;
                }
                if(temp.contains("GET /R/BT/") && QSysInfo::productType()=="android"){        //GET /R/BT/HC-06/
                    list_in_line=temp.split("/");
                    temp=list_in_line[3];
                    parser_data->bt_dev_name=temp;

                    parser_data->com_parser_valid=0;
                    parser_data->bt_parser_valid=1;
                }
            }
        //Open Socket
            if(parser_data->data_wr==1){
                for(int i=0;i<httprqs_parser.size();i++){
                    if(httprqs_parser[i].socket!=parser_data->socket){
                        if(httprqs_parser[i].com_num==parser_data->com_num && parser_data->com_parser_valid==1){
                            httprqs_parser[i].com_port->serial->write("123");
                            ui->textEdit->insertPlainText("        Send data to serial\n");
                            break;
                        }
                    }
                }
                parser_data->socket->close();
            }else if(parser_data->bt_parser_valid==0 &&  parser_data->com_parser_valid==0){//No walid request
                 ui->textEdit->insertPlainText("        No walid request\n");
                 parser_data->socket->write("No walid request...\n");

                 qbt_temp=QByteArray::number(httprqs_parser.size());
                 parser_data->socket->write(qbt_temp);

                 //qbt_temp="123";
                 //qbt_temp+=parser_data->bt_dev_name;
                 //parser_data->socket->write(qbt_temp);

                 parser_data->socket->write("\r\n");
                 parser_data->socket->write("\r\n");
                 parser_data->socket->write("END.\r\n");
                 //parser_data->socket->close();//!!!
                 if(QSysInfo::productType()=="android"){
                    parser_data->gr_bt=new gr_bluetooth;
                    parser_data->gr_bt->bt_open("",0,parser_data->socket);
                 }else{
                     parser_data->socket->close();
                 }
            } else if(parser_data->bt_parser_valid==1 &&  parser_data->com_parser_valid==0 && QSysInfo::productType()=="android"){//BT walid request
                parser_data->gr_bt=new gr_bluetooth;
                parser_data->gr_bt->bt_open(parser_data->bt_dev_name,1,parser_data->socket);
                ui->textEdit->insertPlainText("       Open bt...\n");
            } else if(parser_data->bt_parser_valid==0 &&  parser_data->com_parser_valid==1 && QSysInfo::productType()=="windows"){//COM walid request
                parser_data->com_port=new gr_serial;
                parser_data->com_port->serial_open(parser_data->com_num,parser_data->com_speed,parser_data->socket);
                ui->textEdit->insertPlainText("        Open com...\n");
            }
        //LOG




        // !!!parser_data->com_port=new gr_serial;
        // !!!parser_data->com_port->serial_open(parser_data->com_num,parser_data->com_speed,parser_data->socket);
        //printf("GET /COM/;\n");
        //printf("READ COM%d,%d\n",parser_data->com_num,parser_data->com_speed);
        //QString dev_name, int mode
        /*printf("Data In:\n");
        for(int j=0;j<data_size;j++){
            a=parser_data->InData[j];
            //printf("%X",a);//DADA
            printf("%c",a);
        }
        printf("\n");*/
    }
}
