#include "main_windows/mainwindow.h"
#include "com_to_web.h"

#include <QApplication>

#include <QGuiApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    com_to_web ctw;
    //w.show();

    return a.exec();
}

