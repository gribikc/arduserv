#define dtd_bmp 0
#define dtd_tst 1
#define dtd_count 2//к-во процессов нужно для массива

#define SD_cs 10
#define RXLED 17 // The RX LED has a defined Arduino pin
#define TXLED 30 // The TX LED has a defined Arduino pin



#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

#include "gr_serial.h"
#include "gr_ard_lib.h"

  //#define data_file "data_log_bmp180.log"
  
  Stream* user_stream=&Serial;
  Stream* dev_stream=&Serial;

  gr_serial uart_data;

  Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

  long unsigned int loop_cnt=0;
//////////////////
/////////////////
////////////////
  void setup() {
    delay(3000);
    pinMode(RXLED, OUTPUT); // Set RX LED as an output
    pinMode(TXLED, OUTPUT); // Set TX LED as an output
    //Serial
      Serial.begin (115200);//USB
      Serial1.begin(115200);//free
      
      user_stream->print("xdstartjson:{\n");
      user_stream->print("    \"type\":\"log\",\n");
      user_stream->print("    \"message\":\"Setup Start\"\n");
      user_stream->print("}:xdstopjson");
    //SPI
      pinMode(SD_cs, OUTPUT);
      digitalWrite(SD_cs, HIGH);
      SPI.begin();
      SPI.setClockDivider(SPI_CLOCK_DIV128);
      SPI.setBitOrder(MSBFIRST);
      SPI.transfer(0);
    //SD
      SD.begin(SD_cs);
    //BMP180
      bmp.begin();
  
      user_stream->print("xdstartjson:{\n");
      user_stream->print("    \"type\":\"log\",\n");
      user_stream->print("    \"message\":\"Loop Start\"\n");
      user_stream->print("}:xdstopjson");
      check_time(0,0);
  }
//////////////////
/////////////////
////////////////
  /*int check_time(unsigned int id,unsigned long m_sec){
    static unsigned long mils[]={};
    unsigned long cur_mils=micros();
    unsigned long delta=cur_mils-mils[id];
    if(delta>m_sec){
      mils[id]=cur_mils-(delta-m_sec);
      return 1;
    }
    return 0;
  }*/
//////////////////
/////////////////
////////////////
  void loop() {
    if(check_time(0,1000000)){
      bmp180_write_and_send();
      send_state();
    }
    //bmp180_write_and_send();
    //send_state();
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
    //delay(10000);
  }
////////////////////////
///////////////////////
//////////////////////
  void bmp180_write_and_send(){
    //1013.25hPa~760mmHg~1atm~101.325kPa
    static long unsigned int count=0;
    static signed char cnt=0;
    float temperature;

    sensors_event_t event;
    bmp.getEvent(&event);
    if (event.pressure){
      bmp.getTemperature(&temperature);
      
      user_stream->print("xdstartjson:{\n");                                          //dataFile.print("data:");
      user_stream->print("    \"type\":\"bmp_cur\",\n");                              //dataFile.print("type:bmp180,");
      user_stream->print("    \"count\":");                                           //dataFile.print("cnt:");
      user_stream->print(count);                                                      //dataFile.print(count);
      user_stream->print(",\n");                                                      //dataFile.print(",");
      user_stream->print("    \"cnt\":");                                           //dataFile.print("cnt:");
      user_stream->print(cnt);                                                      //dataFile.print(count);
      user_stream->print(",\n");                                                      //dataFile.print(",");
      user_stream->print("    \"Pressure\":");                                        //dataFile.print("hpa:");
      user_stream->print(event.pressure);                                             //dataFile.print(event.pressure);
      user_stream->print(",\n");                                                      //dataFile.print(",");
      user_stream->print("    \"Temperature\":");                                     //dataFile.print("celsius:");
      user_stream->print(temperature);                                                //dataFile.print(temperature);
      user_stream->print("\n");                                                       //dataFile.print("\n");
      user_stream->print("}:xdstopjson");                                             //dataFile.print("\n");

      if(cnt>=59){
        cnt=-1;
        File dataFile = SD.open("bmp180.log", FILE_WRITE);
        if (!dataFile) {
          user_stream->print("xdstartjson:{\n");
          user_stream->print("    \"type\":\"error\",\n");
          user_stream->print("    \"message\":\"File Error\"\n");
          user_stream->print("}:xdstopjson");
        }else{
          dataFile.print("type:bmp180,");
          dataFile.print("count:");
          dataFile.print(count);
          dataFile.print(",");
          dataFile.print("hpa:");
          dataFile.print(event.pressure);
          dataFile.print(",");
          dataFile.print("celsius:");
          dataFile.print(temperature);
          dataFile.print("\n");
          count++;
        }
        dataFile.flush();
        dataFile.close();
      }
    }else{
      user_stream->print("xdstartjson:{\n");
      user_stream->print("    \"type\":\"error\",\n");
      user_stream->print("    \"message\":\"Sensor Error\"\n");
      user_stream->print("}:xdstopjson");
    }
    cnt++;
  }
////////////////////////
///////////////////////
//////////////////////
  void invert_gpo(int gpo){
    //Serial.println(digitalRead(gpo));
    if(digitalRead(gpo)){
      digitalWrite(gpo,HIGH);
    }else{
      digitalWrite(gpo,LOW);
    }
  }
////////////////////////
///////////////////////
//////////////////////
  void send_state(){
    File dataFile = SD.open("bmp180.log");
    if (!dataFile) {
      user_stream->print("xdstartjson:{\n");
      user_stream->print("    \"type\":\"error\",\n");
      user_stream->print("    \"message\":\"File Error\"\n");
      user_stream->print("}:xdstopjson");
    }
  
    user_stream->print("xdstartjson:{\n");
    user_stream->print("    \"type\":\"status\",\n");
    user_stream->print("    \"file_size\":");
    user_stream->print(dataFile.size());
    user_stream->print("\n");
    user_stream->print("}:xdstopjson");
    
    dataFile.close();
  }
////////////////////////
///////////////////////
//////////////////////
