#include "main_windows/mainwindow.h"
#include "com_to_web.h"

#include <QApplication>

#include <QGuiApplication>
#include <QDebug>


int main(int argc, char *argv[])
{

    if (argc <= 1) {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        qDebug() << "Its main";
        return a.exec();
    } else if (argc > 1 && strcmp(argv[1], "-service") == 0) {
        QAndroidService app(argc, argv);
        com_to_web ctw;
        qDebug() << "Service starting with from the same .so file";
        return app.exec();
    } else {
        qDebug() << argc;
        qDebug() << argv;
        qWarning() << "Unrecognized command line argument";
        return -1;
    }



    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();

    com_to_web ctw;
    //w.show();

    return a.exec();*/
}

