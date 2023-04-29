#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>

#include <esp_pm.h>
#include <esp_wifi.h>
#include <esp_wifi_types.h>


#include <ESP32Time.h>
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

#include "init.h"

#include "autopoliv.h"

void IRAM_ATTR onTimer() {
	static char state=0;

	portENTER_CRITICAL_ISR(&timerMux);
	//interruptCounter++;
	portEXIT_CRITICAL_ISR(&timerMux);
}

Web_server_gr web_server;

void setup() {
  start_init();

  pinMode(PIN_RELE, OUTPUT);
  digitalWrite(PIN_RELE, LOW);
  
  //init_web_server_gr();
  //Web_server_gr web_server;
  web_server.init();
  web_server.server->on("/status", HTTP_GET, [&web_server]() {
		String json = "{";
			json += "\"Time_h\":";		json += gnss_cordinate_valid.Time_h;				json += ",";
			json += "\"Time_m\":";		json += gnss_cordinate_valid.Time_m;				json += ",";
			json += "\"Time_s\":";		json += gnss_cordinate_valid.Time_s;				json += ",";
			json += "\"lat\":";			json += String(gnss_cordinate_valid.latitude,7);	json += ",";
			json += "\"lon\":";			json += String(gnss_cordinate_valid.longitude,7);	json += ",";
			json += "\"fix\":";			json += gnss_cordinate_valid.fix;					json += ",";
			json += "\"NOS\":";			json += gnss_cordinate_valid.NOS;					json += ",";
			json += "\"HDOP\":";		json += gnss_cordinate_valid.HDOP;					json += ",";
			json += "\"Altitude\":";	json += gnss_cordinate_valid.Altitude;				json += ",";
			json += "\"Height\":";		json += gnss_cordinate_valid.Height;				json += ",";
			json += "\"truetrack\":";	json += gnss_cordinate_valid.truetrack;				json += ",";
			json += "\"magntrack\":";	json += gnss_cordinate_valid.magntrack;				json += ",";
			json += "\"ground_speed\":";json += gnss_cordinate_valid.ground_speed;			json += ",";
			json += "\"sat_in_vie\":";	json += gnss_cordinate_valid.sat_in_vie;			json += ",";
			json += "\"sat_snr\":";		json += gnss_cordinate_valid.sat_snr;				json += ",";
			json += "\"gpgsv_siv\":";	json += gnss_cordinate_valid.gpgsv_siv;				json += ",";
			json += "\"gpgsv_isnr\":";	json += gnss_cordinate_valid.gpgsv_isnr;			json += ",";
			json += "\"glgsv_siv\":";	json += gnss_cordinate_valid.glgsv_siv;				json += ",";
			json += "\"glgsv_isnr\":";	json += gnss_cordinate_valid.glgsv_isnr;			json += "";
		json += "}";
		web_server.server->send(200, "text/plan", json);
		json = String();
	});

  web_server.server->on("/gps_off", HTTP_GET, [&web_server]() {
    String rspns = "off";
    sendUBX_OFF();
    web_server.server->send(200, "text/plan", rspns);
  });
  web_server.server->on("/gps_on", HTTP_GET, [&web_server]() {
    String rspns = "on";
    sendUBX_ON();
    web_server.server->send(200, "text/plan", rspns);
  });
  
  web_server.server->on("/min_power_save", HTTP_GET, [&web_server]() {
    String rspns = "min power save";
    Serial.println(rspns);
    esp_wifi_set_ps(WIFI_PS_MIN_MODEM);
    web_server.server->send(200, "text/plan", rspns);
  });
  web_server.server->on("/max_power_save", HTTP_GET, [&web_server]() {
    String rspns = "max power save";
    Serial.println(rspns);
    esp_wifi_set_ps(WIFI_PS_MAX_MODEM);
    web_server.server->send(200, "text/plan", rspns);
  });
  web_server.server->on("/no_power_save", HTTP_GET, [&web_server]() {
    String rspns = "no power save";
    Serial.println(rspns);
    esp_wifi_set_ps(WIFI_PS_NONE);
    web_server.server->send(200, "text/plan", rspns);
  });

  web_server.server->on("/mot_on", HTTP_GET, [&web_server]() {
    String rspns = "mot on";
    rele_swith(PIN_RELE, HIGH);
    web_server.server->send(200, "text/plan", rspns);
  });
  web_server.server->on("/mot_off", HTTP_GET, [&web_server]() {
    String rspns = "mot off";
    rele_swith(PIN_RELE, LOW);
    web_server.server->send(200, "text/plan", rspns);
  });
  
  web_server.server->on("/get_adc_akb", HTTP_GET, [&web_server]() {
    String rspns = "";
    double potValue;
    Serial.println("start adc");
    
    potValue=0;
    for(int i=0;i<100;i++)
      potValue += analogRead(PIN_SOLAR_VOLT);
    potValue/=100.0;
    rspns+=double(double(potValue)*20.8813/4095.0);
    
    rspns+="\r\n";

    potValue=0;
    for(int i=0;i<100;i++)  
      potValue += analogRead(PIN_BATT_VOLT);
    potValue/=100.0;
    rspns+=double(double(potValue)*9.4854/4095.0);
    
    Serial.println("stop adc");
    web_server.server->send(200, "text/plan", rspns);
  });

  web_server.server->on("/go_to_sleep", HTTP_GET, [&web_server]() {
    light_sleep();
  });

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
