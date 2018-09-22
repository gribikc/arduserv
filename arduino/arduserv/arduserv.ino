#define nrf24l01_ce 49
#define nrf24l01_cs 48

#include <SPI.h>

#include "var.h"
#include "nrf24l01.h"
#include "gribikc_serial.h"
#include "init.h"


gribikc_serial usb_serial;
gribikc_nrf24l01p nrf24l01p;



void setup() {
  start_init();

 
  Serial.println("Start...");
  nrf24l01p.get_config();
  nrf24l01p.init_rx();
  nrf24l01p.get_config();
  Serial.println("NRF...done");
}

void loop() {
  //uart_redirect_s3_s();
  //uart_redirect_s_to_s3();

  /*if(Serial.available()){
    usb_serial.nmea_parser(Serial.read());
  }*/
 // Serial.print("Read_reg(0x11):"); 
  //Serial.println( nrf24l01p.read_reg(0x12));
  //nrf24l01p.read_to_s();
  /*i=nrf24l01p.read_reg(0x60);
  if(i!=32){
    Serial.println(i);
  }*/
  if(nrf24l01p.message_available()){
    nrf24l01p.take_message();
  }
  /*i=nrf24l01p.read_reg(0x60);
  if(i!=32){
    Serial.println(i);
  }*/
}
