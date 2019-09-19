#ifndef GR_LOGGER_H
#define GR_LOGGER_H
#include <QObject>

#include <QtCore>
#include <QObject>
#include <QCoreApplication>

class GR_logger{
    public:
        static void log(QString text) {
            //m_messages.append(text);
             qDebug() << text;
        }//Logger::log("Андрюша-хрюшка");

        //static const QVector<QString>& get();
        //static void clear();
    private:
        static QList<QString> m_messages;
};


#endif // GR_LOGGER_H
