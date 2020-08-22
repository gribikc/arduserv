#include "gr_settings.h"

GR_settings::GR_settings(){
    QCoreApplication::setOrganizationName("Gribikc inc");
    QCoreApplication::setOrganizationDomain("www.ru");
    QCoreApplication::setApplicationName("COM TO WEB");
    settings=new QSettings();
    /*settings->beginGroup("main");
    QString margin = settings->value("htdocs_patch").toString();
    settings->setValue("htdocs_patch", "test");
    settings->endGroup();*/
}

const QVariant GR_settings::get_value(QString group_name,QString param_name){
    /*if(group_name==""){
        group_name="main";
    }*/
    //settings->beginGroup(group_name);
    QVariant val= settings->value(param_name);
    //settings->endGroup();
    return val;
}

void GR_settings::set_value(QString group_name,QString param_name,QVariant val){
    /*if(group_name==""){
        group_name="main";
    }*/
    //settings->beginGroup(group_name);
    settings->setValue(param_name, val);
    //settings->endGroup();
}

QStringList GR_settings::get_list(){
    return settings->allKeys();
}

void GR_settings::save_settings(QMap<QString, QVariant> *conf_var){
    QStringList settings_list=conf_var->keys();
    for(int i=0;i<settings_list.size();i++){
        settings->setValue(settings_list.at(i),conf_var->value(settings_list.at(i)));
    }
    settings->setValue("_valid_settings_is_",1);
}

int GR_settings::load_settings(QMap<QString, QVariant> *conf_var){
    if(settings->value("_valid_settings_is_").toInt()==1){
        conf_var->clear();
        QStringList settings_list=settings->allKeys();
        for(int i=0;i<settings_list.size();i++){
            if(settings_list.at(i)!="_valid_settings_is_"){
                conf_var->insert(settings_list.at(i),settings->value(settings_list.at(i)));
            }
        }
        return 1;
    }else {
        return 0;
    }
}

QString GR_settings::create_json_from_arr(QMap<QString, QVariant> conf_var){
    QJsonObject setting_to_json;
    setting_to_json=QJsonObject::fromVariantMap(conf_var);

    QJsonDocument doc(setting_to_json);
    QString str(doc.toJson(QJsonDocument::Compact));
    return str;
}

QMap<QString, QVariant> GR_settings::create_arr_from_json(QString in_data){
    QMap<QString, QVariant> conf;
    conf.clear();
    QJsonObject setting_to_json;
    QJsonDocument doc = QJsonDocument::fromJson(in_data.toLocal8Bit());// toUtf8());
    if(!doc.isNull()){
        if(doc.isObject()){
            setting_to_json = doc.object();
            return setting_to_json.toVariantMap();
        }
    }
    return conf;
}

void GR_settings::clear_settings(){
    settings->clear();
}
