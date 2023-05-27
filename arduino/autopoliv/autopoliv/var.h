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

//BT	
	BluetoothSerial SerialBT;
	struct{
		bool status=0;
	}bt_state_tg;
	
//GNSS
    stream_buf gnss_stream_buf;




  struct task_for_shelder{
    unsigned char mode=0;//[7]-on/off;[6:0]-day of week;
    unsigned char time_h=0;
    unsigned char time_m=0;
    unsigned char duration=0;
  };
  std::vector<a> a(5);

  EEPROM.begin(100);
  EEPROM.put(1, a);
  EEPROM.commit();