#include "com_to_web.h"
#include <QApplication>

#include <QGuiApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    com_to_web w;
    w.show();


    return a.exec();
}

