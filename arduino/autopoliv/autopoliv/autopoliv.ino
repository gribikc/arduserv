#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include "EEPROM.h"

#include <esp_pm.h>
#include <esp_wifi.h>
#include <esp_wifi_types.h>


#include "ESP32Time.h"
ESP32Time rtc(3600*3);  // offset in seconds GMT+1

#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;//portMUX_INITIALIZER_UN

#include "wifi_key.h"
#include "def.h"
#include "uart_gr.h"

#include "var.h"

#include "gps_function.h"

#include "bt_gr.h"
#include "web_server_gr.h"
#include "wifi_gr.h"

Web_server_gr web_server;
#include "autopoliv.h"

#include "init.h"

void IRAM_ATTR onTimer() {
	static char state=0;

	portENTER_CRITICAL_ISR(&timerMux);
	//interruptCounter++;
	portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  start_init();

  pinMode(PIN_RELE, OUTPUT);
  digitalWrite(PIN_RELE, LOW);
  


  EEPROM.begin(100);
  struct a{
    unsigned char mode=0;//[7]-on/off;[6:0]-day of week;
    unsigned char time_h=0;
    unsigned char time_m=0;
    unsigned char duration=0;
  };
  std::vector<a> a(5);
  EEPROM.put(1, a);
  EEPROM.commit();



}

void loop() {
	//WEB
		web_server.do_web();

	//WIRELESS MAINTENANCE
		wifi_do_all();	//maintenance
		bt_do_all();	//maintenance

	//Serial
		/*while(Serial1.available()){
			Serial.write(Serial1.read());
		}
		while(Serial.available()){
			Serial1.write(Serial.read());
		}*/
		collect_stream_data(&gnss_stream_buf);
	
	//GPS
  	if(gnss_cordinate.gpgga_valid==1 && gnss_cordinate.gpvtg_valid==1 && gnss_cordinate.gprmc_valid==1){
  		gnss_cordinate.gpgga_valid=0;
  		gnss_cordinate.gpvtg_valid=0;
      gnss_cordinate.gprmc_valid=0;
  		gnss_cordinate_valid=gnss_cordinate;
  
  		#ifdef DEBUG_ON
  			//debug_stream->println("GNSS: FIX.");
  		#endif
  		//usb_stream_buf.uart->write(uart_send_byte,96);

      //rtc.setTime(30, 24, 15, 17, 1, 2021);  // 17th Jan 2021 15:24:30
      rtc.setTime(gnss_cordinate_valid.Time_s, gnss_cordinate_valid.Time_m, gnss_cordinate_valid.Time_h, gnss_cordinate_valid.day, gnss_cordinate_valid.month, gnss_cordinate_valid.year+2000);
  	}

  //TEST
  static int timeinfo = rtc.getTimeStruct().tm_sec;
  if(timeinfo!=rtc.getTimeStruct().tm_sec){
    timeinfo = rtc.getTimeStruct().tm_sec;
    //Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));
    Serial.print(rtc.getDayofWeek());
    Serial.print("-");
    Serial.print(rtc.getHour(true));
    Serial.print(":");
    Serial.print(rtc.getMinute());
    Serial.print(":");
    Serial.print(rtc.getSecond());
    Serial.println();
  }
}
