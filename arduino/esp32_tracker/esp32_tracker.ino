#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>

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

void IRAM_ATTR onTimer() {
	static char state=0;

	portENTER_CRITICAL_ISR(&timerMux);
	//interruptCounter++;
	portEXIT_CRITICAL_ISR(&timerMux);
}

Web_server_gr web_server;

void setup() {
  start_init();
  
  //init_web_server_gr();
  //Web_server_gr web_server;
  web_server.init();
  web_server.server->on("/status", HTTP_GET, [web_server]() {
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
	//
	if(gnss_cordinate.gpgga_valid==1 && gnss_cordinate.gpvtg_valid==1){
		gnss_cordinate.gpgga_valid=0;
		gnss_cordinate.gpvtg_valid=0;
		gnss_cordinate_valid=gnss_cordinate;

		#ifdef DEBUG_ON
			debug_stream->println("GNSS: FIX.");
		#endif
		//usb_stream_buf.uart->write(uart_send_byte,96);
	}
}
