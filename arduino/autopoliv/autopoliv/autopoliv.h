
//RELE////////////////////////////////////////////////////////////////////////////////
  void rele_swith(int num,bool state){
    digitalWrite(num, state);
  }


//GPS////////////////////////////////////////////////////////////////////////////////
  void sendUBX(uint8_t *MSG, uint8_t len) {// Send a byte array of UBX protocol to the GPS
    for(int i=0; i<len; i++) {
      Serial1.write(MSG[i]);
    }
  }

  void sendUBX_OFF(){
      uint8_t GPSoff[] = {0xB5, 0x62, 0x02, 0x41, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x4D, 0x3B};
      sendUBX(GPSoff, sizeof(GPSoff)/sizeof(uint8_t));
      Serial.println("OFF");  
  }

  void sendUBX_ON(){
        uint8_t GPSon[] = {0xB5, 0x62, 0x02, 0x41, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x4C, 0x37};
        sendUBX(GPSon, sizeof(GPSon)/sizeof(uint8_t));
        Serial.println("ON");
  }

//HZCHZ////////////////////////////////////////////////////////////////////////////////
  void light_sleep(){
      Serial.println("sleep");
      WiFi.disconnect();
      WiFi.mode(WIFI_OFF);
      esp_sleep_enable_timer_wakeup(10000000);
      esp_light_sleep_start();
  }