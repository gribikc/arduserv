#include "com_to_web.h"
#include "ui_com_to_web.h"


com_to_web::com_to_web(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::com_to_web)
{
    ui->setupUi(this);

    ui->textEdit->insertPlainText("Start...");
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
    ui->textEdit->insertPlainText("Client connected;\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void com_to_web::stateChanged(){ // обработчик статуса, нужен для контроля за "вещающим"
    QObject * object = QObject::sender();
    if (!object){
        ui->textEdit->insertPlainText("Socket error...");
        return;
    }
    QTcpSocket * socket = static_cast<QTcpSocket *>(object);
    //printf(state);
    if (socket->state() == QAbstractSocket::UnconnectedState){
       ui->textEdit->insertPlainText("Disconnected;\n");
       for(int i=0;i<httprqs_parser.size();i++){
           if(httprqs_parser[i].socket==socket){
               //httprqs_parser[i].com_port->serial->close();

               httprqs_parser[i].gr_bt->bt_Socket->close();

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
        ui->textEdit->insertPlainText("Socket error...");
        return;
    }

    QTcpSocket *socket = static_cast<QTcpSocket *>(object);
    QByteArray arr;// =  socket->readAll();

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

    parser_data->com_parser_valid=0;

    if(parser_data->InData[data_size-1]==(char)0x0A && parser_data->InData[data_size-2]==(char)0x0D &&
       parser_data->InData[data_size-3]==(char)0x0A && parser_data->InData[data_size-4]==(char)0x0D     ){
        ui->textEdit->insertPlainText("Request complite:\n");
        QString data=parser_data->InData;
        QString temp;
        QStringList list_line = data.split("\r\n");
        QStringList list_in_line;

        for(int i=0;i<list_line.size();i++){
            temp=list_line[i];
            if(temp.contains("GET /R/COM/")){
                list_in_line=temp.split("/");

                temp=list_in_line[3];
                parser_data->com_num=temp.toInt();
                temp=list_in_line[4];
                parser_data->com_speed=temp.toInt();

                parser_data->com_parser_valid=1;//!!!



                //printf("GET /COM/;\n");
                //printf("READ COM%d,%d\n",parser_data->com_num,parser_data->com_speed);
            }
        }


        parser_data->socket->write("HTTP/1.1 200 OK\n");
        parser_data->socket->write("Content-type: text/plan\n");
        parser_data->socket->write("Connection: keep-alive\n");
        parser_data->socket->write("Access-Control-Allow-Origin: *\n");
        parser_data->socket->write("\n");

        // !!!parser_data->com_port=new gr_serial;
        // !!!parser_data->com_port->serial_open(parser_data->com_num,parser_data->com_speed,parser_data->socket);
        parser_data->gr_bt=new gr_bluetooth;
        parser_data->gr_bt->bt_open(parser_data->com_num,parser_data->com_speed,parser_data->socket);

        ui->textEdit->insertPlainText("open");



        /*printf("Data In:\n");
        for(int j=0;j<data_size;j++){
            a=parser_data->InData[j];
            //printf("%X",a);//DADA
            printf("%c",a);
        }
        printf("\n");*/
    }
}
