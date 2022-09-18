#include <esp_task_wdt.h>
#include <unordered_map>

void start_init(){
	//SYS
	
	//Serial
		Serial.begin(115200,SERIAL_8N1,RXD0,TXD0);
		Serial.print("TEST");
		Serial1.begin(9600,SERIAL_8N1,RXD1,TXD1);
		Serial1.print("TEST");
		#ifdef DEBUG_ON
			debug_stream=&Serial;//&Serial;//&tcp_ipClients[0]//
		#endif

	//WiFi
		WiFi.mode(WIFI_STA);

    String hostname = WIFI_DNAME;
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(hostname.c_str()); //define hostname
    MDNS.begin(hostname.c_str());
    
		//WiFi.disconnect();
		WiFi.begin(WIFI_SSID, WIFI_KEY);
	  	//delay(500);

	//Code

		//tcp_ip.begin();
		//izm.set_obr(obrv);
  		attachInterrupt(PIN_clk0,izm_irq,RISING);

		//WEB
    	web_server.init();
      
      xTaskCreatePinnedToCore(
        [](void * pvParameters){
          for(;;){
            //esp_task_wdt_delete(0);
            tcp_ip.hasClient();//!!hz!!!//
            esp_task_wdt_deinit();
            web_server.do_web();
            esp_task_wdt_init(3,true);
            vTaskDelay(10);
          } 
        }    ,  "WebServer"      ,  1024*8      ,  NULL    ,  2      ,  NULL     ,  0);

		//StepMotor
		timer = timerBegin(0, 80, true);
		timerAttachInterrupt(timer, &onTimer, true);
		timerAlarmWrite(timer, 10, true);//1 000 000 ~ 1c
		timerAlarmEnable(timer);

	//
	web_server.server->on("/get_izm_data", HTTP_GET, [web_server]() {
		String str;
		str.clear();
		std::vector<float> &data=collect_izm.get();
		str+="[\n";
		bool st=1;
		for(auto &d:data){
			if(!st)str+=", ";st=0;
			str+=String(d,4);
		}
		str+="\n]";
		web_server.server->send(200, "text/plan;", str);
	});
 
  web_server.server->on("/get_izm_data2", HTTP_GET, [web_server]() {
   String str;
    str.clear();
    str+="[\n";
    bool st=1;
    while(collect_izm_circle.is_readable()){
      if(!st)str+=", ";st=0;
      str+=String(collect_izm_circle.read().first,4);
    }
    str+="\n]";
    web_server.server->send(200, "text/plan;", str);
  });
  
  web_server.server->on("/get_pid_data", HTTP_GET, [web_server]() {
   String str;
    str.clear();
    str+="[\n";
    bool st=1;
    while(collect_pid_circle.is_readable()){
      if(!st)str+=", ";st=0;
      str+=String(collect_pid_circle.read().first,4);
    }
    str+="\n]";
    web_server.server->send(200, "text/plan;", str);
  });

	web_server.server->on("/error", HTTP_GET, [web_server]() {
		String str;
		str.clear();

		str+="{\n";
			str+=" lost_cnt:";
			str+=String(izm.lost_cnt);
			str+=",\n";
			str+=" izm_timer:{\n";
					str+="   cur:";
					str+=String(mes_int_izm.get_cur());
					str+=",\n";
					str+="   min:";
					str+=String(mes_int_izm.get_min());
					str+=",\n";
					str+="   avg:";
					str+=String(mes_int_izm.get_avr());
					str+=",\n";
					str+="   max:";
					str+=String(mes_int_izm.get_max());
					str+="\n";
			str+=" }";
			str+=",\n";
			str+=" motor:{\n";
					str+="   inc:";
					str+=String(sm_prot.get_inc());
					str+=",\n";
					str+="   ob_sec:";
					str+=String(sm_prot.get_ob_sec());
					str+=",\n";
					str+="   freq:";
					str+=String(sm_prot.get_freq());
					str+="\n";
			str+=" }";
			str+=",\n";
			str+=" main_timer:{\n";
					str+="   cur:";
					str+=String(loop_timer.get_cur());
					str+=",\n";
					str+="   min:";
					str+=String(loop_timer.get_min());
					str+=",\n";
					str+="   avg:";
					str+=String(loop_timer.get_avr());
					str+=",\n";
					str+="   max:";
					str+=String(loop_timer.get_max());
					str+="\n";
			str+=" }\n";
		str+="}\n";
		mes_int_izm.reset();
		loop_timer.reset();
		web_server.server->send(200, "text/plan;", str);
	});

	web_server.server->on("/motset", HTTP_POST, [web_server]() {
    std::unordered_map<std::string, std::string> arguments_map=std::move(web_server.get_map_param());

    if(arguments_map["type"]=="set"){
      sm_prot.set_ob_sec(atof(arguments_map["speed"].c_str()));
    }else if(arguments_map["type"]=="inc"){
      sm_prot.inc_ob_sec(atof(arguments_map["speed"].c_str()));
    }else{
      //err
    }
   
    String str="OK.cur_speed:";
		str+=sm_prot.get_ob_sec();

    /*web_server.server->sendHeader(F("Access-Control-Allow-Origin"), F("*"));
    web_server.server->sendHeader(F("Access-Control-Max-Age"), F("600"));
    web_server.server->sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
    web_server.server->sendHeader(F("Access-Control-Allow-Headers"), F("*"));*/

		web_server.server->send(200, "text/plan;", str);
	});

  web_server.server->on("/iadset", HTTP_POST, [web_server]() {
    String str;
    str+="OK.";
    int interval;
    String type;
    for (uint8_t i = 0; i < web_server.server->args(); i++) {
        if(web_server.server->argName(i) == "interval"){
        interval=atoi(web_server.server->arg(i).c_str());
      }
      if(web_server.server->argName(i) == "type"){
        type=web_server.server->arg(i);
      }
      }
    Serial.print("Type:");
    Serial.print(type);
    Serial.print(":NUM:");
    Serial.println(interval);
    if(type=="set"){
      iad.set_interval(interval);
    }
    str+="cur_speed:";
    str+=iad.get_interval();
    web_server.server->send(200, "text/plan;", str);
  });

  web_server.server->on("/mode_auto", HTTP_GET, [web_server]() {
    String str;
    str+="OK.";
    work_model.w_mode=1;
    web_server.server->send(200, "text/plan;", str);
  });
  web_server.server->on("/mode_stop", HTTP_GET, [web_server]() {
    String str;
    str+="OK.";
    work_model.w_mode=0;
    web_server.server->send(200, "text/plan;", str);
  });
  web_server.server->on("/set_diametr", HTTP_POST, [web_server]() {
    String str;
    str+="OK.";
    float diametr;
    for (uint8_t i = 0; i < web_server.server->args(); i++) {
      if(web_server.server->argName(i) == "diametr"){
        diametr=atof(web_server.server->arg(i).c_str());
      }
    }

    work_model.target_diametr=diametr;
    
    str+="diametr:";
    str+=diametr;
    web_server.server->send(200, "text/plan;", str);
  });
  web_server.server->on("/set_pid", HTTP_POST, [web_server]() {
    String str;
    str+="OK.";
    float kp;
    float kd;
    for (uint8_t i = 0; i < web_server.server->args(); i++) {
      if(web_server.server->argName(i) == "kp"){
        kp=atof(web_server.server->arg(i).c_str());
      }
      if(web_server.server->argName(i) == "kd"){
        kd=atof(web_server.server->arg(i).c_str());
      }
    }

    work_model.k_p=kp;
    work_model.k_d=kd;
    
    str+="kp:";
    str+=kp;
    str+=";kd:";
    str+=kd;
    web_server.server->send(200, "text/plan;", str);
  });
}
