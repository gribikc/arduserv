#include "main_windows/mainwindow.h"
#include "com_to_web.h"
#include "gr_ctw_thread/gr_ctw_thread.h"

#include <QApplication>

#include <QGuiApplication>
#include <QDebug>

//gr_ctw_thread *ctw;

int main(int argc, char *argv[])
{
    qDebug() << "Main start;";
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



    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    com_to_web ctw;

    //gr_ctw_thread *ctw;
    //gr_ctw_thread ctw;
    //ctw.start();
    //ctw=new gr_ctw_thread();
    //ctw->start();



    return a.exec();
}

