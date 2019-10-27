#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

  #define SD_cs 10
  #define RXLED 17 // The RX LED has a defined Arduino pin
  #define TXLED 30 // The TX LED has a defined Arduino pin
  
  Stream* user_stream=&Serial;
  Stream* dev_stream=&Serial;

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
  }
//////////////////
/////////////////
////////////////
  void loop() {
    bmp180_write_and_send();
    send_state();
    delay(1000);
  }
////////////////////////
///////////////////////
//////////////////////
  void bmp180_write_and_send(){
    File dataFile = SD.open("datalog.dat", FILE_WRITE);
    if (!dataFile) {
      user_stream->print("xdstartjson:{\n");
      user_stream->print("    \"type\":\"error\",\n");
      user_stream->print("    \"message\":\"File Error\"\n");
      user_stream->print("}:xdstopjson");
    }
    sensors_event_t event;
    bmp.getEvent(&event);
    if (event.pressure){
      float temperature;
      bmp.getTemperature(&temperature);
      
      user_stream->print("xdstartjson:{\n");                                          dataFile.print("xdstartjson:{\n");
      
      user_stream->print("    \"type\":\"bmp_cur\",\n");
      user_stream->print("    \"Pressure\":");                                        dataFile.print("    \"Pressure\":\"");
      user_stream->print(event.pressure);                                             dataFile.print(event.pressure);
      user_stream->print(",\n");                                                      dataFile.print(",\n");
      user_stream->print("    \"Temperature\":");                                     dataFile.print("    \"Temperature\":");
      user_stream->print(temperature);                                                dataFile.print(temperature);
      user_stream->print("\n");                                                       dataFile.print("\n");
      
      user_stream->print("}:xdstopjson");                                               dataFile.print("}:xdstopjson");
    }else{
      user_stream->print("xdstartjson:{\n");
      user_stream->print("    \"type\":\"error\",\n");
      user_stream->print("    \"message\":\"Sensor Error\"\n");
      user_stream->print("}:xdstopjson");
    }
    dataFile.flush();
    dataFile.close();
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
  File dataFile = SD.open("datalog.dat");

  user_stream->print("xdstartjson:{\n");
  user_stream->print("    \"type\":\"status\",\n");
  user_stream->print("    \"file_size\":");
  user_stream->print(dataFile.size());
  //user_stream->print(",\n");
  //user_stream->print("    \"available\":");
  //user_stream->print(dataFile.available());
  user_stream->print("\n");
  user_stream->print("}:xdstopjson");
  
  dataFile.close();
}
