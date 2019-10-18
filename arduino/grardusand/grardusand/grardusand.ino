//#include <Adafruit_CircuitPlayground.h>
//#include <Adafruit_Circuit_Playground.h>


#define nrf24l01_ce 42
#define nrf24l01_cs 41
#define SD_cs 49

#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "lib/nrf24l01p.h"
#include "lib/gribikc_serial.h"
#include <Adafruit_BME280.h>
#include "var.h"

#include "init.h"

void setup() {
  start_init();
  
  //init_sd();
  
  /*user_stream->println("Start...");
    nrf24l01p.get_config();
    nrf24l01p.init();
    nrf24l01p.init_rx();
    nrf24l01p.get_config();
  user_stream->println("NRF...done");*/
  
  init_sd();

  init_BME280();
}

void loop() {
  long_timer_cnt++;
  
  // put your main code here, to run repeatedly:
    //nrf24l01p.read_to_s();
    //uart_both_redirect_s1_s();//GPS
    //uart_both_redirect_s2_s();//BT
    //uart_both_redirect_s3_s();//RS232
    
    //printValues();
    //BME280_send_data();
    //delay(1000);

    uart_both_redirect(&Serial,&Serial2);

    if((long_timer_cnt-bme280_tcnt)>300000){
      bme280_tcnt=long_timer_cnt;
      BME280_send_json();
      //BME280_send_nmea();
    }
}
