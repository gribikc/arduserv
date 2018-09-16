#define nrf24l01_ce 9
#define nrf24l01_cs 10

#include <SPI.h>

#include "nrf24l01.h"
#include "var.h"
#include "gribikc_serial.h"
#include "init.h"


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

  //get_nrf24_config();
  //delay(1500);
  /*if(Serial.available()){
    usb_serial.nmea_parser(Serial.read());
  }*/

  delay(1000);
  nrf24l01_send_message();
  Serial.println("Send...OK");
  //nrf24l01_init_rx();
      digitalWrite(nrf24l01_cs, LOW);
      Serial.print("Carrier Detect");
      Serial.print(": ");
      Serial.print(SPI.transfer(9));
      Serial.print("  ");
      Serial.print(SPI.transfer(0x00));
      Serial.print("  ");
      Serial.print(SPI.transfer(0x00));
      digitalWrite(nrf24l01_cs, HIGH);
      Serial.print("\n");
  
}
