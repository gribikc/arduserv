#define nrf24l01_ce 49
#define nrf24l01_cs 48

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
    nrf24l01p.get_config();
    nrf24l01p.init();
    nrf24l01p.init_rx();
    nrf24l01p.get_config();
  Serial.println("NRF...done");
}

void loop() {
  //uart_redirect_s3_s();
  //uart_redirect_s_to_s3();

  if(nrf24l01p.message_available()){
    nrf24l01p.print_message();
  }
  /*if(nrf24l01p.message_available()){
    nrf24l01p.read_message(rx_buf,32);
    for(int i=0;i<32;i++){
      Serial.print(byte(rx_buf[i]),HEX);
      Serial.print(":");
    }
    Serial.println();
  }*/
  //nrf24l01p.scan_PDCD();
  //!!!nrf24l01p.read_to_s();
}
