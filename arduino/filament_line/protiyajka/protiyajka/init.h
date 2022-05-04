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
		WiFi.begin(WIFI_SSID, WIFI_KEY);
	  	delay(500);

	//Code
		//izm.set_obr(obrv);
  		attachInterrupt(PIN_clk0,izm_irq,RISING);

	//WEB
    	web_server.init();

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
}
