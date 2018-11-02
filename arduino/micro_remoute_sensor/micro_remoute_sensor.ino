#define nrf24l01_ce 9
#define nrf24l01_cs 10

#include <SPI.h>

#include "var.h"
#include "lib/nrf24l01p.h"
#include "lib/gribikc_serial.h"
#include "init.h"


gribikc_serial usb_serial;
gribikc_nrf24l01p nrf24l01p;



void setup() {
  start_init();

 
  Serial.println("Start...");
    //nrf24l01p.get_config();
    //nrf24l01p.init_tx();
    //nrf24l01p.get_config();
  Serial.println("NRF...done");
}

void loop() {
  //uart_redirect_s3_s();
  //uart_redirect_s_to_s3();

  //get_nrf24_config();
  //delay(1500);
  /*if(Serial.available()){
    usb_serial.nmea_parser(Serial.read());
  }*/

  delay(1000);
  //nrf24l01p.send_message();
  nrf24l01p.send_message_long();
  //nrf24l01p.scan_PDCD();
  //Serial.println("Send...OK");

}
