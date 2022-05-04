
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>

#include "def.h"
#include "GR_digital_micrometer.h"
#include "GR_data_collector.h"
#include "wifi_key.h"
#include "web_server_gr.h"
#include "var.h"
#include "wifi_gr.h"
#include "init.h"


GR_data_collector<float> collect_izm;

void setup(){ 
  start_init();
//
  web_server.server->on("/status", HTTP_GET, [web_server]() {
		String str;
    str.clear();
    std::vector<float> &data=collect_izm.get();
    str+="[";
    bool st=1;
    for(auto &d:data){
      if(!st)str+=", ";st=0;
      str+=String(d,4);
    }
    str+="]";
    //str=String(izm.get_izm(),4);
		web_server.server->send(200, "text/plan;", str);
	});
    		

}

void loop(){ 
  if(izm.doit()){
    //Serial.print("from loop:");
    //obrv(izm.get_izm());
    collect_izm.add(izm.get_izm());
  }
  web_server.do_web();
  wifi_do_all();
} 


