#define nrf24l01_ce 49
#define nrf24l01_cs 48

#include <SPI.h>

#include "nrf24l01.h"
#include "var.h"
#include "gribikc_serial.h"
#include "init.h"

//#include "esp8266.h"
//gribikc_esp8266 esp8266;


gribikc_serial usb_serial;



void setup() {
  start_init();

 
  Serial.println("Start...");
  get_nrf24_config();
  nrf24l01_init_tx();
  get_nrf24_config();
  Serial.println("NRF...done");
}

void loop() {
  //uart_redirect_s3_s();
  //uart_redirect_s_to_s3();
  //esp8266.parser_at();
  //esp8266.write_data(0,3,esp8266.rx_buf);//(char id,byte len,char *arr)

  //get_nrf24_config();
  //delay(1500);
  if(Serial.available()){
    usb_serial.nmea_parser(Serial.read());
  }
  
}
