#include "com_to_web.h"
#include <QApplication>

#include <QGuiApplication>
#include <QDebug>

//#include <QtAndroidExtras/QtAndroid>
//#include <QtAndroidExtras/QAndroidJniObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    com_to_web w;
    w.show();


    return a.exec();
}
/*int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    if (QCoreApplication::arguments().count() > 1){
        qDebug() << "I am the service";
    }
    else{
        qDebug() << "I am the application";
    }
    return app.exec();
}*/
