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

    /*
    //Синхронизация укладчика
      //Serial.print("Одометр:"); Serial.println(laying_mot.get_odometr());
      if(laying_mot.get_ob_sec()<=0.00001){
        if(laying_mot.get_odometr()==0){
          laying_mot.go_inc(eedat_upr.spool_width*8*200);
        }else{
          laying_mot.go_inc(-eedat_upr.spool_width*8*200);
        }
        laying_mot.set_ob_sec(eedat_upr.speed_main*eedat_upr.target_diametr);
        Serial.println("Програмный концевик(Мотор остановлен)");
        Serial.print("Одометр:"); Serial.println(laying_mot.get_odometr());
      }
      */
  }



  
  

  //loop_timer.doit();//измеряем загрузку
} 
