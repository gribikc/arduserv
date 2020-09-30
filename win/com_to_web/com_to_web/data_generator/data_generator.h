#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include <QObject>
#include <QtCore/QDebug>
#include <gr_http_client/gr_http_client.h>

class data_generator : public QObject
{
    Q_OBJECT
public:
    int cnt=0;
    explicit data_generator(GR_http_client *parent = nullptr);

    QTimer *timer;
    GR_http_client* partner;
    int timer_period;
    QString traffic_type;
    int traffic_size;
private slots:
    void timer_event();
protected:
     //void timer_event(QTimerEvent *);
     //void timer_event(QTimerEvent *e);
signals:

};

#endif // DATA_GENERATOR_H
