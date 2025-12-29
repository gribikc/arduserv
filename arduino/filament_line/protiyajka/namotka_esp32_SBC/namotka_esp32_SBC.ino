//////////////////////////////////
/*
катушка стандарт//4.75//4.5-4.6//////////66.5

*/
//////////////////////////////////


#include <WiFi.h>
#include <NetworkClient.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
//#include <EEPROM.h>
#include "EEPROM.h"
#include <rom/rtc.h>

#include "GR_circle_buf.h"
#include "Debounce.h"
#include "def.h"
#include "GR_time_mesure.h"
#include "GR_step_driver.h"
#include "wifi_key.h"
#include "web_server_gr.h"
#include "var.h"
#include "wifi_gr.h"
#include "init.h"


void setup(){ 
  start_init();

  main_mot.set_ob_sec(0.0);
  laying_mot.set_ob_sec(0.0);

  //Парковка
    Lay_Park();
    delay(3000);

  //Старт намотки
  //main_mot.set_ob_sec(eedat_upr.speed_main);
  //laying_mot.set_ob_sec(eedat_upr.speed_main*eedat_upr.target_diametr);
  //laying_mot.go_inc(eedat_upr.spool_width*8*200);//targett_d

  //onTimer_fo
  timerAttachInterrupt(timer, &onTimer_fo);//, true);
}

void loop(){
  if(onTimer_flg){
    onTimer_flg=false;
    laying_mot.doit();
    main_mot.doit();

   if(eedat_upr.mode==1){ 
    //Синхронизация укладчика
      //Serial.print("Одометр:"); Serial.println(laying_mot.get_odometr());
      if(laying_mot.get_ob_sec()==0.0f){//laying_mot.get_inc()==0//laying_mot.get_ob_sec()==0.0f
        if(laying_mot.get_odometr()==0){
          laying_mot.go_to((eedat_upr.spool_width-eedat_upr.target_diametr*1)*8*200);//go_to
        }else{
          laying_mot.go_to(0/*-eedat_upr.spool_width*8*200*/);//go_inc
        }
        laying_mot.set_ob_sec(main_mot.get_ob_sec()*eedat_upr.target_diametr);
        //Serial.println("Програмный концевик(Мотор остановлен)");
        //Serial.print("Скорость:"); Serial.println(laying_mot.get_ob_sec());
        Serial.print("Програмный концевик(Мотор остановлен) \n\r Одометр:"); Serial.println(laying_mot.get_odometr());
      }
   }
   
   
   if(eedat_upr.mode==2){
      eedat_upr.mode=1;
          //Старт намотки
        Serial.println("Старт намотки");
        main_mot.set_ob_sec(eedat_upr.speed_main);
        laying_mot.set_ob_sec(eedat_upr.speed_main*eedat_upr.target_diametr);
        laying_mot.go_to((eedat_upr.spool_width-eedat_upr.target_diametr*1)*8*200);//targett_d
        Serial.print("To:"); Serial.println((eedat_upr.spool_width-eedat_upr.target_diametr)*8*200);
   }

   if(eedat_upr.mode==3){
      eedat_upr.mode=0;
          //Старт намотки
        Serial.println("Стоп намотки");
        main_mot.set_ob_sec(0);
        laying_mot.set_ob_sec(2);
        laying_mot.go_to(0);//targett_d
        Serial.print("To:"); Serial.println((eedat_upr.spool_width-eedat_upr.target_diametr)*8*200);
   }
  }



  
  

  //loop_timer.doit();//измеряем загрузку
} 
