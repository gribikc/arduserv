#ifndef GR_CTW_THREAD_H
#define GR_CTW_THREAD_H

#include <QThread>
#include "com_to_web.h"

class gr_ctw_thread : public QThread
{
    Q_OBJECT
    /*gr_ctw_thread(){
        qDebug() << "THRED1";
    }*/
    com_to_web *ctw;
protected:
    void run(){
        qDebug() << "THRED2";
        ctw=new com_to_web();
        QObject::disconnect(ctw,nullptr,nullptr,nullptr);
        /*QObject::connect(ctw,&com_to_web::info,this,[&] (int type,QString str)
            {
                qDebug()<<"AAA";
            });*/
        exec();
    }

public:
    //com_to_web *ctw;
    ~gr_ctw_thread(){
        terminate();
        ctw->deleteLater();
        deleteLater();
    }
    com_to_web * get_ctw_handler(){
        return ctw;
    }
signals:

public slots:
};


#endif // GR_CTW_THREAD_H
