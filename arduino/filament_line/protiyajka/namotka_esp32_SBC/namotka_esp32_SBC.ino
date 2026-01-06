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

#include "WindingMachine.h"

#include "Button.h"
Button myButton(MOff);

WindingMachine windingmachine(main_mot,laying_mot);

void setup(){ 
  start_init();

  main_mot.set_ob_sec(0.0);
  laying_mot.set_ob_sec(0.0);

  //Парковка
    //Lay_Park();//!!!Убрать нахуй!!! сделать в лупе режим!!!
    //delay(3000);

  //onTimer_fo
  timerAttachInterrupt(timer, &onTimer_fo);//, true);
  Serial.println("Setup:Инициализация завершина!");
  sys_info.write("Setup:Инициализация завершина!");
}

void loop(){
  if(onTimer_flg){
    onTimer_flg=false;
    laying_mot.doit();
    main_mot.doit();

    windingmachine.doit();

    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    uint8_t event = myButton.doWork();
    
    switch(event) {
      case 1:
        Serial.println("Loop:Кнопка нажата");
        //windingmachine.play_pause();
        break;
      case 2:
        Serial.println("Loop:Кнопка отпущена");
        if(myButton.get_pre_event()==3 || myButton.get_pre_event()==4){
          Serial.println("Loop:.play_pause");
          windingmachine.play_pause();
        }else if(myButton.get_pre_event()==1){
          Serial.println("Loop:.pause");
          windingmachine.pause();
        }else if(myButton.get_pre_event()==5){
          Serial.println("Loop:.begin");
          windingmachine.begin();
        }

        break;
      case 3:
        Serial.println("Loop:Удержание 500 мс");
        break;
      case 4:
        Serial.println("Loop:Удержание 1 сек");
        break;
      case 5:
        Serial.println("Loop:Удержание 5 сек");
        break;
    }







  }



  
  

  //loop_timer.doit();//измеряем загрузку
} 
