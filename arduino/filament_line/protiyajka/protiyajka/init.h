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
}
