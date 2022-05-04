
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>

#include "def.h"
#include "GR_digital_micrometer.h"
#include "GR_data_collector.h"
#include "GR_time_mesure.h"
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
  if(izm.doit()){
    mes_int_izm.doit();
    collect_time_mes.add(mes_int_izm.get());
    collect_izm.add(izm.get_izm());
    //Serial.print("from loop:");
    //obrv(izm.get_izm());
  }
  //web_server.do_web();
  //wifi_do_all();
  //Serial.println(izm.lost_cnt);
} 


