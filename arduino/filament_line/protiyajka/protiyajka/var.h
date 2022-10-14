int i,j,k;
/////
	hw_timer_t * timer = NULL;

//DeBUG&SYS
	#ifdef DEBUG_ON
		Stream* debug_stream;
	#endif
	
//WiFi
	//!!!Адовый костыль нее убирать отвалится веб сервер
	WiFiServer tcp_ip(TCP_PORT);
	WiFiClient tcp_ipClients[TCP_MAX_SRV_CLIENTS];
//Web
	Web_server_gr web_server;

//Global for Work
	GR_digital_micrometer izm(PIN_data0,PIN_clk0);
	
	GR_data_collector<float> collect_izm;
  GR_circle_buf<float> collect_izm_circle(100);
  GR_integrate_and_dump<float> iad;

  GR_circle_buf<float> collect_pid_circle(100);
  float out=0;
  float pre=0;

	GR_time_mesure mes_int_izm;
	GR_time_mesure loop_timer;
	
	GR_step_driver sm_prot(MOT_STEP,MOT_DIR,MOT_EN);
  ///Work Mode & EEPROM
  
    struct eedat_upr_def{
      float k_p=-0.05;
      float k_d=0.99;
      float target_diametr=1.75f;
      int iad=20;
      String ap_name_host="prot";
      String ap_key_host="12345678";
      String ap_name_client=WIFI_SSID;
      String ap_key_client=WIFI_KEY;
      String local_name="prot";
    }eedat_upr;

    struct work_model_def{
      float pre_error=0;
      int w_mode=0;//!!!=0//0-none;1-auto;2-uderjanie;
    }work_model;


  

//Func
	void obrv(float data){
		Serial.println(data,3);
	};

	void IRAM_ATTR izm_irq() {
		izm.get_bit();
	}

	void IRAM_ATTR onTimer() {
		sm_prot.doit();
		//portENTER_CRITICAL_ISR(&timerMux);
		////interruptCounter++;
		//portEXIT_CRITICAL_ISR(&timerMux);
	}
