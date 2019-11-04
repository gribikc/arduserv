//#include <Adafruit_CircuitPlayground.h>
//#include <Adafruit_Circuit_Playground.h>


#define dtd_count 5

#define nrf24l01_ce 42
#define nrf24l01_cs 41
#define SD_cs 49

#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "gr_serial.h"
#include "gr_ard_lib.h"
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
  //check_time(0,0);
}
void loop() {
  
  // put your main code here, to run repeatedly:
    //nrf24l01p.read_to_s();
    //uart_both_redirect_s1_s();//GPS
    //uart_both_redirect_s2_s();//BT
    //uart_both_redirect_s3_s();//RS232
    
    //printValues();
    //BME280_send_data();
    //delay(1000);

    //uart_both_redirect(&Serial,&Serial2);
    if(uart_data.do_rx(user_stream)){
      user_stream->print("xdstartjson:{\n");
      user_stream->print("    \"type\":\"info\",\n");
      user_stream->print("    \"byte\":\"");
      //user_stream->print(uart_data.rx_buf[(uart_data.rx_buf_point-MESSAGE_SIZE_OF+2)&(RX_BUF_SIZE_OF)],HEX);
      user_stream->print(uart_data.get_id(),HEX);
      user_stream->print("\",\n");
      user_stream->print("    \"message\":\"new message\"\n");
      user_stream->print("}:xdstopjson");
    }

    if(check_time(1,5000000)){//
      user_stream->print("xdstartjson:{\n");
      user_stream->print("    \"type\":\"info\",\n");
      user_stream->print("    \"byte\":\"");
      user_stream->print(micros());
      user_stream->print("\",\n");
      user_stream->print("    \"message\":\"Timer0(3)\"\n");
      user_stream->print("}:xdstopjson");
    }

    if(uart_data.do_rx(user_stream)){
      event_uart_rx_message();
    }

    if(check_time(2,1000000)){
      BME280_save_to_file();
    }
    if(check_time(0,1000000)){
      BME280_send_json();
      //BME280_send_nmea();
    }
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void event_uart_rx_message(){
      user_stream->print("xdstartjson:{\n");
      user_stream->print("    \"type\":\"info\",\n");
      user_stream->print("    \"byte\":\"");
      //user_stream->print(uart_data.rx_buf[(uart_data.rx_buf_point-MESSAGE_SIZE_OF+2)&(RX_BUF_SIZE_OF)],HEX);
      user_stream->print(uart_data.get_id(),HEX);
      user_stream->print("\",\n");
      user_stream->print("    \"message\":\"new message\"\n");
      user_stream->print("}:xdstopjson");
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////
