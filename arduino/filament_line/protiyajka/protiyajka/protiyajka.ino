
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>

#include "def.h"
#include "GR_digital_micrometer.h"
#include "GR_data_collector.h"
#include "GR_time_mesure.h"
#include "GR_step_driver.h"
#include "GR_circle_buf.h"
#include "GR_integrate_and_dump.h"
#include "wifi_key.h"
#include "web_server_gr.h"
#include "var.h"
#include "wifi_gr.h"
#include "init.h"

void setup(){ 
  start_init();
  //
  izm.fake_mode_set(1);
}

void loop(){
  if(izm.doit()){//есть новое измерение
    mes_int_izm.doit();//мерим переод измерений, точнее входа в функцию

    float data=izm.get_izm();
    //collect_izm.add(data);//сохраняем в массив измерения
    collect_izm_circle.write(data);

    if(iad.put(data)){
      collect_izm.add(iad.get());

      float in=(iad.get()-1.75)*(-1);
      out+=in-0.99*pre;
      pre=in;
      collect_pid_circle.write(out);
    }

    //Serial.print("from loop:");
    //obrv(izm.get_izm());
  }


  //web_server.do_web();//отдаем пользователю данные
  wifi_do_all();//проверяем статус вайфая и новые соединения
  //Serial.println(izm.lost_cnt);
  loop_timer.doit();//измеряем загрузку
} 
