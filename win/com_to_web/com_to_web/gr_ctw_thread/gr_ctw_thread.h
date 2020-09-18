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
        exec();
    }

public:
    ~gr_ctw_thread(){
        deleteLater();
    }
signals:

public slots:
};


#endif // GR_CTW_THREAD_H
