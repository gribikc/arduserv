void start_init(){
	//SYS
	
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

}
