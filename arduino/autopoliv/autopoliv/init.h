void start_init(){
	//SYS
    pinMode(PIN_RELE, OUTPUT);
    digitalWrite(PIN_RELE, LOW);
	
	//Serial
		Serial.begin(115200,SERIAL_8N1,RXD0,TXD0);
		Serial.print("TEST");
		Serial1.begin(115200,SERIAL_8N1,RXD1,TXD1);
		Serial1.print("TEST");
		#ifdef DEBUG_ON
			debug_stream=&Serial;//&tcp_ipClients[0]//
		#endif

	//WiFi
		WiFi.mode(WIFI_STA);
		WiFi.begin(WIFI_SSID, WIFI_KEY);
		//WebServer
		
	
	//BT
		//SerialBT.begin("BAP");
	
	//Other
	    gnss_stream_buf.uart=&Serial1;
        gnss_stream_buf.parser=nmea_parser_converter;


  //WEB INIT
    web_server.init();
    web_server.server->on("/status", HTTP_GET, [&web_server]() {
      String json = "{";
        json += "\"Time_h\":";		json += gnss_cordinate_valid.Time_h;				json += ",";
        json += "\"Time_m\":";		json += gnss_cordinate_valid.Time_m;				json += ",";
        json += "\"Time_s\":";		json += gnss_cordinate_valid.Time_s;				json += ",";
        json += "\"lat\":";			json += String(gnss_cordinate_valid.latitude,7);	json += ",";
        json += "\"lon\":";			json += String(gnss_cordinate_valid.longitude,7);	json += ",";
        json += "\"fix\":";			json += gnss_cordinate_valid.fix;					json += ",";
        json += "\"NOS\":";			json += gnss_cordinate_valid.NOS;					json += ",";
        json += "\"HDOP\":";		json += gnss_cordinate_valid.HDOP;					json += ",";
        json += "\"Altitude\":";	json += gnss_cordinate_valid.Altitude;				json += ",";
        json += "\"Height\":";		json += gnss_cordinate_valid.Height;				json += ",";
        json += "\"truetrack\":";	json += gnss_cordinate_valid.truetrack;				json += ",";
        json += "\"magntrack\":";	json += gnss_cordinate_valid.magntrack;				json += ",";
        json += "\"ground_speed\":";json += gnss_cordinate_valid.ground_speed;			json += ",";
        json += "\"sat_in_vie\":";	json += gnss_cordinate_valid.sat_in_vie;			json += ",";
        json += "\"sat_snr\":";		json += gnss_cordinate_valid.sat_snr;				json += ",";
        json += "\"gpgsv_siv\":";	json += gnss_cordinate_valid.gpgsv_siv;				json += ",";
        json += "\"gpgsv_isnr\":";	json += gnss_cordinate_valid.gpgsv_isnr;			json += ",";
        json += "\"glgsv_siv\":";	json += gnss_cordinate_valid.glgsv_siv;				json += ",";
        json += "\"glgsv_isnr\":";	json += gnss_cordinate_valid.glgsv_isnr;			json += "";
      json += "}";
      web_server.server->send(200, "text/plan", json);
      json = String();
    });

    web_server.server->on("/gps_off", HTTP_GET, [&web_server]() {
      String rspns = "off";
      sendUBX_OFF();
      web_server.server->send(200, "text/plan", rspns);
    });
    web_server.server->on("/gps_on", HTTP_GET, [&web_server]() {
      String rspns = "on";
      sendUBX_ON();
      web_server.server->send(200, "text/plan", rspns);
    });
    
    web_server.server->on("/min_power_save", HTTP_GET, [&web_server]() {
      String rspns = "min power save";
      Serial.println(rspns);
      esp_wifi_set_ps(WIFI_PS_MIN_MODEM);
      web_server.server->send(200, "text/plan", rspns);
    });
    web_server.server->on("/max_power_save", HTTP_GET, [&web_server]() {
      String rspns = "max power save";
      Serial.println(rspns);
      esp_wifi_set_ps(WIFI_PS_MAX_MODEM);
      web_server.server->send(200, "text/plan", rspns);
    });
    web_server.server->on("/no_power_save", HTTP_GET, [&web_server]() {
      String rspns = "no power save";
      Serial.println(rspns);
      esp_wifi_set_ps(WIFI_PS_NONE);
      web_server.server->send(200, "text/plan", rspns);
    });

    web_server.server->on("/mot_on", HTTP_GET, [&web_server]() {
      String rspns = "mot on";
      rele_swith(PIN_RELE, HIGH);
      web_server.server->send(200, "text/plan", rspns);
    });
    web_server.server->on("/mot_off", HTTP_GET, [&web_server]() {
      String rspns = "mot off";
      rele_swith(PIN_RELE, LOW);
      web_server.server->send(200, "text/plan", rspns);
    });
    
    web_server.server->on("/get_adc_akb", HTTP_GET, [&web_server]() {
      String rspns = "";
      double potValue;
      Serial.println("start adc");
      
      potValue=0;
      for(int i=0;i<100;i++)
        potValue += analogRead(PIN_SOLAR_VOLT);
      potValue/=100.0;
      rspns+=double(double(potValue)*20.8813/4095.0);
      
      rspns+="\r\n";

      potValue=0;
      for(int i=0;i<100;i++)  
        potValue += analogRead(PIN_BATT_VOLT);
      potValue/=100.0;
      rspns+=double(double(potValue)*9.4854/4095.0);
      
      Serial.println("stop adc");
      web_server.server->send(200, "text/plan", rspns);
    });

    web_server.server->on("/go_to_sleep", HTTP_GET, [&web_server]() {
      light_sleep();
    });
  ///////
}
