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
		WiFi.disconnect();
		WiFi.begin(WIFI_SSID, WIFI_KEY);
	  	//delay(500);

	//Code

		//tcp_ip.begin();
		//izm.set_obr(obrv);
  		attachInterrupt(PIN_clk0,izm_irq,RISING);

		//WEB
    	web_server.init();

		//StepMotor
		timer = timerBegin(0, 80, true);
		timerAttachInterrupt(timer, &onTimer, true);
		timerAlarmWrite(timer, 10, true);//1 000 000 ~ 1c
		timerAlarmEnable(timer);

	//
	web_server.server->on("/status", HTTP_GET, [web_server]() {
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
		//str=String(izm.get_izm(),4);
		web_server.server->send(200, "text/plan;", str);
	});

	web_server.server->on("/status1", HTTP_GET, [web_server]() {
		String str;
		str.clear();
		std::vector<float> &data=collect_time_mes.get();
		str+="[\n";
		bool st=1;
		for(auto &d:data){
			if(!st)str+=", ";st=0;
			str+=String(d,4);
		}
		str+="\n]";
		//str=String(izm.get_izm(),4);
		web_server.server->send(200, "text/plan;", str);
	});

	web_server.server->on("/status2", HTTP_GET, [web_server]() {
		String str;
		str.clear();

		str+="[";
		str+=String(izm.lost_cnt);
		str+="]";
		web_server.server->send(200, "text/plan;", str);
	});

	web_server.server->on("/motgo", HTTP_GET, [web_server]() {
		String str;
		sm_prot.move();
		str+="OK.";
		web_server.server->send(200, "text/plan;", str);
	});

	web_server.server->on("/motset", HTTP_POST, [web_server]() {
		String str;
		sm_prot.move();
		str+="OK.";
		for (uint8_t i = 0; i < web_server.server->args(); i++) {
  			if(web_server.server->argName(i) == "speed"){
				float speed=atof(web_server.server->arg(i).c_str());
				sm_prot.set_f(speed);
			}
  		}
		web_server.server->send(200, "text/plan;", str);
	});
}
