#ifndef GR_SETTINGS_H
#define GR_SETTINGS_H
#include <QApplication>
#include <QSettings>
#include <QJsonObject>
#include <QJsonDocument>


class GR_settings
{
public:
    GR_settings();
    QSettings *settings;
    const QVariant get_value(QString group_name,QString param_name);
    void set_value(QString group_name, QString param_name, QVariant val);
    QStringList get_list(QString group_name);
    void save_settings(QString group_name,QMap<QString, QVariant> *conf_var);
    int load_settings(QString group_name,QMap<QString, QVariant> *conf_var);
    QString create_json_from_arr(QMap<QString, QVariant> conf_var);
    QMap<QString, QVariant> create_arr_from_json(QString in_data);
    void clear_settings(QString group_name);
};

#endif // GR_SETTINGS_H
