int i,j,k;
/////


//DeBUG&SYS
	#ifdef DEBUG_ON
		Stream* debug_stream;
	#endif
	
//WiFi
	WiFiServer tcp_ip(TCP_PORT);
	WiFiClient tcp_ipClients[TCP_MAX_SRV_CLIENTS];


//Web
	Web_server_gr web_server;

//Global
	GR_digital_micrometer izm(PIN_data0,PIN_clk0);
	GR_data_collector<float> collect_izm;

	GR_data_collector<float> collect_time_mes(100);
	GR_time_mesure mes_int_izm;
	
//Func
	void obrv(float data){
		Serial.println(data,3);
	};

	void IRAM_ATTR izm_irq() {
		izm.get_bit();
	}