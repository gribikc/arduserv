
#include <WiFi.h>
#include <NetworkClient.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
//#include <EEPROM.h>
#include "EEPROM.h"

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

float ob_sec_incr=0.001;

void setup(){ 
  start_init();
  //
  izm.fake_mode_set(eedat_upr.musurer_fake_mode>0?true:false);
  izm.set_out_s(eedat_upr.musurer_sign>0?true:false);
  izm.set_precision(eedat_upr.musurer_precision);
  iad.set_interval(eedat_upr.iad);

  //EEPROM.writeByte(0, 0);

  pinMode (22, OUTPUT);
  pinMode (23, OUTPUT);

  main_mot_shnek.set_ob_sec(0.0);
}

void loop(){
  if(izm.doit()){//есть новое измерение c микрометра
    mes_int_izm.doit();//мерим переод измерений, точнее входа в функцию для отладки

    float data=izm.get_izm();//получаем измерение
    //Serial.print("IZM:");
    //erial.println(data);
    //collect_izm.add(data);//сохраняем в массив измерения
    collect_izm_circle.write(data);//сохраняем в массив измерения для передачи в web

    if(iad.put(data)){//загоняем измерение в усреднитель и проверяем можно ли брать измерение
      collect_izm.add(iad.get());//сохраняем в массив измерения для передачи в web

      float error=(iad.get()-eedat_upr.target_diametr)*(-1)*eedat_upr.k_p;//вычисление ошибки: измеренное значение диаметра минус заданное и умноженоое на коэффицент передачи ПИД
      
      float out=error-eedat_upr.k_d*work_model.pre_error;//Реализация ПИД
      out+=sm_prot.get_ob_sec();
      
      work_model.pre_error=error;//сохранение преведущий ошибки
      
      if(work_model.w_mode==1){
        sm_prot.set_ob_sec(out);
      }
      collect_pid_circle.write(sm_prot.get_ob_sec());


      //main_mot_shnek.set_ob_sec(ob_sec_incr);
      //ob_sec_incr+=0.1;
    }

    //Serial.print("from loop:");
    //obrv(izm.get_izm());
  }


  //web_server.do_web();//отдаем пользователю данные
  //!!!!!!!!!!!!!!!!!!!!!wifi_do_all();//проверяем статус вайфая и новые соединения
  //Serial.println(izm.lost_cnt);
  loop_timer.doit();//измеряем загрузку
} 
