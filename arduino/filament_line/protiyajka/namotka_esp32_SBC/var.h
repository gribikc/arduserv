/*
       _____________________
      |_____________________|
      |
      |
      |
      |
      |                                        ___
      |                                ___   _/
      |_____________________         _/     |_      0 по катушке
      |_____________________|       |_        \___  0 по упору
      |___________|  |__              \___
      |_________________|
      |
      |                                ____ 
      |                              _/
      |                             |_              0 по концевику
      |                               \____
*/




int i,j,k;

/////
	hw_timer_t * timer = NULL;

//DeBUG&SYS
	#ifdef DEBUG_ON
		Stream* debug_stream;
	#endif
    std::vector<String> collect_log(0);
    GR_circle_buf<String> sys_info(100);
	
//WiFi
	//!!!Адовый костыль нее убирать отвалится веб сервер
	WiFiServer tcp_ip(TCP_PORT);
	WiFiClient tcp_ipClients[TCP_MAX_SRV_CLIENTS];
//Web
	Web_server_gr web_server;

//Global for Work
	GR_time_mesure loop_timer;
	
  //GR_step_driver(       int step_pin,int dir_pin,int en_pin=0,int fb_pin=0,float degres=1.8f,float reduction=5.18f,bool dir=true):
	GR_step_driver laying_mot(MOT_STEP_P,MOT_DIR_P,MOT_EN_P,0,1.8f,1.0f,true);//true/false направление вращение двигателя
  GR_step_driver main_mot(MOT_STEP_S,MOT_DIR_S,MOT_EN_S,0,1.8f,12.0f,true);//true/false направление вращение двигателя//(MOT_STEP_S,MOT_DIR_S,MOT_EN_S,0,1.8f,5.18f,false)
  
  ///Work Mode & EEPROM
    struct eedat_upr_def{
      float speed_main=0.3f;//скорость намотки
      
      float lay_offset=7.0f;//3.90f;!!!///
      float target_diametr=2.0f;//1.85f;//Lay_Ki 0.5 на один оборот намотчика инкремент?!?!?!!! !!!

      float spool_thickness=5.0f;//4.75;
      float spool_width=64.5f;//64.5f;//-target_diametr;

      String ap_name_host="namotchik";
      String ap_key_host="12345670";
      String ap_name_client=WIFI_SSID;
      String ap_key_client=WIFI_KEY;
      String local_name="prot";
    }eedat_upr;

    struct work_model_def{
      float pre_error=0;
      int w_mode=0;//!!!=0//0-none;1-auto;2-uderjanie;
    }work_model;


Debounce lay_pos_button(LAY_S, 15);
volatile bool onTimer_flg=false;
//Func
	void IRAM_ATTR onTimer() {
    onTimer_flg=true;
		laying_mot.doit();
    main_mot.doit();
	}
  void IRAM_ATTR onTimer_fo() {
    onTimer_flg=true;
	}

  void Lay_Park(){//нужно 2 метода!!! один парковка по концевику. вторая установка в 0!!!
    //pinMode(LAY_S, INPUT);
    Serial.println("Парковка по концевику...");
    bool llps= lay_pos_button.update();
    llps= lay_pos_button.update();
    llps= lay_pos_button.update();
    llps= lay_pos_button.update();
    llps= lay_pos_button.update();
    llps= lay_pos_button.update();
    llps= lay_pos_button.update();
    llps= lay_pos_button.update();
    llps= lay_pos_button.update();
    llps= lay_pos_button.update();
    llps= lay_pos_button.update();
    laying_mot.dir(llps);//!!! //!
    laying_mot.set_ob_sec(2);///Lay_Ki);
    bool st_step=false;
    //0 нижний концевик
    //1 верхний концевик
    while(!st_step || llps){//!!!
      if(onTimer_flg){
        onTimer_flg=false;
        llps=lay_pos_button.update();
        st_step=(llps||st_step)?1:0;
        laying_mot.dir(llps);      
      }
    }

    //Отступ от 0 до края платформы
      laying_mot.odometr_reset();//вроде не надо
      laying_mot.go_inc( (eedat_upr.lay_offset+eedat_upr.spool_thickness+eedat_upr.target_diametr*0.0)*8*200 ) ;//разбить на 2 функциональных вызов
      //laying_mot.set_ob_sec(0);//!!!
      //laying_mot.go_inc(eedat_upr.spool_thickness*8*200);//разбить на 2 функциональных вызов
      //laying_mot.go_inc(eedat_upr.target_diametr*8*200);//разбить на 2 функциональных вызов
      Serial.println("Парковка по концевику...завершена");
      sys_info.write("Парковка по концевику...завершена");
      while(laying_mot.get_ob_sec()>0.00001){
        delay(50);
      }
      Serial.print("Скорость:");Serial.println(laying_mot.get_ob_sec());
      Serial.print("Одометр:"); Serial.println(laying_mot.get_odometr());
      laying_mot.odometr_reset();
      Serial.print("Одометр:"); Serial.println(laying_mot.get_odometr());
      Serial.println("Парковка по отступу...завершена");
      sys_info.write("Парковка по отступу...завершена");
  }
