#include <QtCore>
#include <QObject>
#include <QCoreApplication>
#include "gr_sock_srv/gr_sock_srv.h"

//gr_serial com_port;
//gr_sock_srv socks;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    printf("Programm start...\n");

    //gr_serial *com_port=new gr_serial();
    gr_sock_srv *socks=new  gr_sock_srv();

    //com_port->serial_open();
    socks->gr_sock_srv_start();


    return a.exec();
}
