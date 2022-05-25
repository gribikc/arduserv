
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>

#include "def.h"
#include "GR_digital_micrometer.h"
#include "GR_data_collector.h"
#include "GR_time_mesure.h"
#include "GR_step_driver.h"
#include "wifi_key.h"
#include "web_server_gr.h"
#include "var.h"
#include "wifi_gr.h"
#include "init.h"

void setup(){ 
  start_init();
  //

}

void loop(){
  if(izm.doit()){//есть новое измерение
    mes_int_izm.doit();//мерим переод измерений, точнее входа в функцию
    collect_izm.add(izm.get_izm());//сохраняем в массив измерения

    //Serial.print("from loop:");
    //obrv(izm.get_izm());
  }


  //web_server.do_web();//отдаем пользователю данные
  wifi_do_all();//проверяем статус вайфая и новые соединения
  //Serial.println(izm.lost_cnt);
  loop_timer.doit();//измеряем загрузку
} 
