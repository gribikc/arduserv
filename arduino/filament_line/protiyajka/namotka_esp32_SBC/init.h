#include <esp_task_wdt.h>
#include <unordered_map>


void start_init(){
	//SYS
	
	//Serial
		Serial.begin(115200,SERIAL_8N1,RXD0,TXD0);
		Serial.println("Hello");
		#ifdef DEBUG_ON
			debug_stream=&Serial;//&Serial;//&tcp_ipClients[0]//
		#endif


  //EEPROM
    //EEPROM.begin(200);
    ////EEPROM.write(0,1);
    ////EEPROM.commit();
    //if(EEPROM.read(0)>0){
    //  EEPROM.get(1, eedat_upr);
    //  Serial.println("EEPROM read");
    //}else{
    //  Serial.println("EEPROM not valid!");
    //  EEPROM.put(1, eedat_upr);
    //  EEPROM.write(0, 1 );
    //  EEPROM.commit();
    //  Serial.println("EEPROM reset");
    //}
    
	//WiFi
		//WiFi.mode(WIFI_STA);//!!!???
    //WiFi.mode(WIFI_MODE_APSTA);
    //WiFi.mode(WIFI_AP_STA);

    Serial.print("MAC:");
    Serial.println(WiFi.macAddress());

    //WIFI SOFT AP
      //WiFi.softAP(eedat_upr.ap_name_host, eedat_upr.ap_key_host);//ap_name_host
      if (!WiFi.softAP(eedat_upr.ap_name_host, eedat_upr.ap_key_host)){
        Serial.print("AP create error!!!");
      }
      IPAddress IP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(IP);
      Serial.print("AP Host: ");
      Serial.println("TEST_AP");
      Serial.print("AP Key: ");
      Serial.println("12345670");

    //WIFI MDNS
      String hostname = "namotchik";
      WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
      WiFi.setHostname(hostname.c_str()); //define hostname
      MDNS.begin(hostname.c_str());
      Serial.print(hostname);
      Serial.println(".local");

    //WIFI HOST
		  //WiFi.disconnect();
		  WiFi.begin(WIFI_SSID, WIFI_KEY);

		//WEB
    	web_server.init();
      
      xTaskCreatePinnedToCore(
        [](void * pvParameters){
          for(;;){
            //esp_task_wdt_delete(0);
            tcp_ip.hasClient();//!!hz!!!//
            esp_task_wdt_deinit();
            web_server.do_web();
            wifi_do_all();////////////////!!!!!!!!!!
            esp_task_wdt_config_t a;
            a.timeout_ms=100;
            a.idle_core_mask=0;
            a.trigger_panic=1;
            esp_task_wdt_init(&a);//3,true);!!!!!!!!!!!!!!!
            vTaskDelay(10);
          } 
        }    ,  "WebServer"      ,  1024*8      ,  NULL    ,  2      ,  NULL     ,  0);

		//StepMotor//  float fs_=100000;//KHz
      timer = timerBegin(1000000);//0, 80, true);
      timerAttachInterrupt(timer, &onTimer);//, true);
      timerAlarm(timer, 1 * 10, true, 0);

//////////////////////////////////////////
//////////////////////////////////////////
  web_server.server->on("/move_lay", HTTP_POST, [web_server]() {//Иногда зависает и кудато улетает... такое ощущение что go_inc тупит...!!! !!! !!!
    std::unordered_map<std::string, std::string> arguments_map=std::move(web_server.get_map_param());
    if(arguments_map["type"]=="inc"){
      laying_mot.set_ob_sec(2);
      laying_mot.go_inc(atof(arguments_map["speed"].c_str())*1600);
    }else if(arguments_map["type"]=="goto"){
      laying_mot.set_ob_sec(2);
      laying_mot.go_to(atof(arguments_map["speed"].c_str())*1600);
    }else if(arguments_map["type"]=="odorst"){
      laying_mot.set_ob_sec(0.0);
      laying_mot.odometr_reset();
    }
    String str;
    str.clear();
    str+=String(laying_mot.get_odometr());

    web_server.server->send(200, "text/plan;", str);
  });

  web_server.server->on("/move_winder", HTTP_POST, [web_server]() {//тут сделать не только скорость но и расстояние в оборотах
    std::unordered_map<std::string, std::string> arguments_map=std::move(web_server.get_map_param());
    if(arguments_map["type"]=="set"){
      main_mot.set_ob_sec(atof(arguments_map["speed"].c_str()));
      if(eedat_upr.mode==1){
        laying_mot.set_ob_sec(main_mot.get_ob_sec()*eedat_upr.target_diametr);
      }
    }else if(arguments_map["type"]=="inc"){
      main_mot.inc_ob_sec(atof(arguments_map["speed"].c_str()));
      if(eedat_upr.mode==1){
        laying_mot.set_ob_sec(main_mot.get_ob_sec()*eedat_upr.target_diametr);
      }
    }else{
      //err
    }
    String str;
    str.clear();
    str+=String(laying_mot.get_odometr());

    web_server.server->send(200, "text/plan;", str);
  });
 ////////////////////////////////////////// 
 //////////////////////////////////////////
  web_server.server->on("/mode_start", HTTP_GET, [web_server]() {//!!! почемуто работает через гет /mode?type=set&mode=start
    std::unordered_map<std::string, std::string> arguments_map=std::move(web_server.get_map_param());
    //if(arguments_map["type"]=="set"){
    //  //main_mot.set_ob_sec(atof(arguments_map["speed"].c_str()));
    //  if(arguments_map["mode"]=="start"){
    //    main_mot.set_ob_sec(eedat_upr.speed_main);
    //    laying_mot.set_ob_sec(eedat_upr.speed_main*eedat_upr.target_diametr);
    //    laying_mot.go_inc(eedat_upr.spool_width*8*200);//targett_d
    //  }
    //}
    eedat_upr.mode=2;
    String str;
    str.clear();
    str+=String(laying_mot.get_odometr());

    web_server.server->send(200, "text/plan;", str);
  });
  
  web_server.server->on("/mode_auto", HTTP_GET, [web_server]() {
    String str;
    str+="OK.";
    //work_model.w_mode=1;
    web_server.server->send(200, "text/plan;", str);
  });

  web_server.server->on("/mode_stop", HTTP_GET, [web_server]() {
    String str;
    str+="OK.";
    //work_model.w_mode=0;
    web_server.server->send(200, "text/plan;", str);
  });
//////////////////////////////////////////
//////////////////////////////////////////

  //main_mot.set_ob_sec(eedat_upr.speed_main);
  //laying_mot.set_ob_sec(eedat_upr.speed_main*eedat_upr.target_diametr);
  //laying_mot.go_inc(eedat_upr.spool_width*8*200);//targett_d

//////////////////////////////////////////
  web_server.server->on("/eeprom_read", HTTP_GET, [web_server]() {
    String str;
    str.clear();

    str+="{\n";
      str+=" \"EEPROM_valid\":";        str+=String(EEPROM.read(0));            str+=",\n";EEPROM.commit();
      str+=" \"target_diametr\":";      str+=String(eedat_upr.target_diametr);  str+=",\n";
      str+=" \"ap_name_host\":\"";      str+=eedat_upr.ap_name_host;            str+="\",\n";
      str+=" \"ap_key_host\":\"";       str+=eedat_upr.ap_key_host;             str+="\",\n";
      str+=" \"ap_name_client\":\"";    str+=eedat_upr.ap_name_client;          str+="\",\n";
      str+=" \"ap_key_client\":\"";     str+=eedat_upr.ap_key_client;           str+="\",\n";
      str+=" \"local_name\":\"";        str+=eedat_upr.local_name;              str+="\",\n";
    str+="}\n";

    web_server.server->send(200, "text/plan;", str);
  });

  web_server.server->on("/eeprom_write", HTTP_POST, [web_server]() {
    std::unordered_map<std::string, std::string> arguments_map=std::move(web_server.get_map_param());

    /*Serial.print("Size:");
    Serial.println(arguments_map.size());
    for (auto& a : arguments_map){
      Serial.print(a.first.c_str());
      Serial.print(":");
      Serial.println(a.second.c_str());
    }*/
      
    eedat_upr.target_diametr      =atof(arguments_map["target_diametr"].c_str());
      
    eedat_upr.ap_name_host        =arguments_map["ap_name_host"].c_str();
    eedat_upr.ap_key_host         =arguments_map["ap_key_host"].c_str();
    eedat_upr.ap_name_client      =arguments_map["ap_name_client"].c_str();
    eedat_upr.ap_key_client       =arguments_map["ap_key_client"].c_str();
    eedat_upr.local_name          =arguments_map["local_name"].c_str();


    EEPROM.write(0,1);
    EEPROM.put(1, eedat_upr);
    EEPROM.commit();
   
    String str="OK";
    web_server.server->send(200, "text/plan;", str);
  });
  
  web_server.server->on("/eeprom_reset", HTTP_GET, [web_server]() {
    String str;
    str.clear();
    EEPROM.write(0,0);
    EEPROM.commit();
    str="Reset EEPROM OK!";
    web_server.server->send(200, "text/plan;", str);
  });

  web_server.server->on("/get_cur_settings", HTTP_GET, [web_server]() {
    String str;
      str.clear();

      str+="{\n";
        str+=" \"Mot_speed\":";         str+=String(0/*sm_prot.get_ob_sec(),6*/);      str+=",\n";  
        str+=" \"iad\":";               str+=String(0/*iad.get_interval(),0*/);        str+=",\n";
        str+=" \"diametr\":";           str+=String(0/*eedat_upr.target_diametr,6*/);  str+=",\n";
        str+=" \"pid_kp\":";             str+=String(0/*eedat_upr.k_p,6*/);            str+=",\n";
        str+=" \"pid_kd\":";             str+=String(0/*eedat_upr.k_d,6*/);            str+="\n";
      str+="}\n";

      web_server.server->send(200, "text/plan;", str);
  });
}
