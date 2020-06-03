int i,j,k;
/////


//DeBUG&SYS
	#ifdef DEBUG_ON
		Stream* debug_stream;
	#endif
	
//WEB
	//stream_buf web_stream_buf;
	
//USB
	//stream_buf usb_stream_buf;
	
//WiFi
	WiFiServer tcp_ip(TCP_PORT);
	WiFiClient tcp_ipClients[TCP_MAX_SRV_CLIENTS];
	struct{
		int status=0;
	}wifi_state_tg;

	
//BT	
	BluetoothSerial SerialBT;
	struct{
		bool status=0;
	}bt_state_tg;
	
//GNSS
    stream_buf gnss_stream_buf;
