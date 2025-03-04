#include "main_windows/mainwindow.h"
#include "com_to_web.h"
#include "GR_web_server/gr_web_server.h"
#include "gr_ctw_thread/gr_ctw_thread.h"

#include <QApplication>

#include <QGuiApplication>
#include <QDebug>
#include <QObject>

//#include <QAndroidService>
//#include <QtAndroidExtras>
//#include <QAndroidJniObject>
//#include <QAndroidIntent>
//#include <QAndroidJniObject>
//#include <QAndroidJniEnvironment>
//#include <QtAndroid>

//gr_ctw_thread *ctw;


int main(int argc, char *argv[])
{
    qDebug() << "Main start;";
    QCoreApplication::setOrganizationName("Gribikc inc");
    QCoreApplication::setOrganizationDomain("www.ru");
    QCoreApplication::setApplicationName("COM TO WEB");

    //if (argc <= 1) {
    //    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();
    //    qDebug() << "Its main";
    //
    //    /*QAndroidIntent serviceIntent(QtAndroid::androidActivity().object(),
    //                                        "QtAndroidService");
    //    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
    //                "startService",
    //                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
    //                serviceIntent.handle().object());*/
    //
    //    /*QAndroidJniObject::callStaticMethod<void>(
    //        "QtAndroidService",
    //        "startQtAndroidService",
    //        "(Landroid/content/Context;)V",
    //        QtAndroid::androidActivity().object());*/
    //    /*QAndroidJniObject::callStaticMethod<void>(
    //        "QtAndroidService",
    //        "startQtAndroidService",
    //        "(Landroid/content/Context;)V",
    //        QtAndroid::androidActivity().object());
    //        //QtAndroid::androidContext().object());*/
    //
    //    return a.exec();
    //} else if (argc > 1 && strcmp(argv[1], "-service") == 0) {
    //    QAndroidService app(argc, argv);
    //    com_to_web ctw;
    //    qDebug() << "Service starting with from the same .so file";
    //    return app.exec();
    //    return 1;
    //} else {
    //    qDebug() << argc;
    //    qDebug() << argv;
    //    qWarning() << "Unrecognized command line argument";
    //    return -1;
    //}


    /*QProcess *process = new QProcess();
    QString program = "cmd.exe";
    QString folder = "C:\\";
    process->start(program, QStringList() << folder);*/

    //QtWebView::initialize();
    ////////////////////////////
    ////////////////////////////
    ////////////////////////////
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
    ////////////////////////////
    ////////////////////////////
    ////////////////////////////
        com_to_web ctw;
        QObject::connect(&ctw,&com_to_web::info,&w,&MainWindow::write_text);
        ctw.init();
    ////////////////////////////
    ////////////////////////////
    ////////////////////////////
        //GR_web_server gws;
        //QObject::connect(&gws,&GR_web_server::info,&w,&MainWindow::write_text);
        //gws.init();
    ////////////////////////////
    ////////////////////////////
    ////////////////////////////
        /*gr_ctw_thread ctw;
        ctw.start(QThread::HighestPriority);
        com_to_web *ctw_point=ctw.get_ctw_handler();
        QObject::disconnect(ctw_point,nullptr,nullptr,nullptr);
        QObject::connect(ctw_point,&com_to_web::info,nullptr,[] (int type,QString str)
        {
            qDebug()<<"AAA";
        }
        );*/
    ////////////////////////////
    ////////////////////////////
    ////////////////////////////
    return a.exec();
}

