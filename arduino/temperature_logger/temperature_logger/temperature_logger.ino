#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

  #define SD_cs 10
  File dataFile;
  
  Stream* user_stream=&Serial;
  Stream* dev_stream=&Serial;

  Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
//////////////////
/////////////////
////////////////
  void setup() {
    delay(3000);
    //Serial
      Serial.begin (115200);//USB
      Serial1.begin(115200);//free
      Serial.println("START SETUP:");
      Serial1.println("START SETUP:");
    //SPI
      pinMode(SD_cs, OUTPUT);
      digitalWrite(SD_cs, HIGH);
      SPI.begin();
      SPI.setClockDivider(SPI_CLOCK_DIV128);
      SPI.setBitOrder(MSBFIRST);
      SPI.transfer(0);
    //SD
      SD.begin(SD_cs);
      dataFile = SD.open("datalog.dat", FILE_WRITE);
    //BMP180
      bmp.begin();
  
    Serial.println("LOOP START:");
    Serial1.println("LOOP START:");
  }
//////////////////
/////////////////
////////////////
  void loop() {
    bmp180_read();
    delay(1000);
  }
////////////////////////
///////////////////////
//////////////////////
  void bmp180_read(){
    if (!dataFile) {
      user_stream->print("ERROR!!!");
    }
    /* Get a new sensor event */ 
    sensors_event_t event;
    bmp.getEvent(&event);
   
    /* Display the results (barometric pressure is measure in hPa) */
    if (event.pressure){
      float temperature;
      float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
      
      user_stream->println("xdstartjson:{");                                        dataFile.print("xdstartjson:{");
      
      user_stream->print("    \"Pressure\":\"");                                    dataFile.print("    \"Pressure\":\"");
      user_stream->print(event.pressure);                                           dataFile.print(event.pressure);
      user_stream->print("\",\n");                                                  dataFile.print("\",\n");
      bmp.getTemperature(&temperature);                                             //dataFile.print(&temperature);
      user_stream->print("    \"Temperature\":\"");                                 dataFile.print("    \"Temperature\":\"");
      user_stream->print(temperature);                                              dataFile.print(temperature);
      user_stream->print("\",\n");                                                  dataFile.print("\",\n");
      user_stream->print("    \"Altitude\":\"");                                    dataFile.print("    \"Altitude\":\"");
      user_stream->print(bmp.pressureToAltitude(seaLevelPressure,event.pressure));  dataFile.print(bmp.pressureToAltitude(seaLevelPressure,event.pressure));
      user_stream->print("\"\n");                                                   dataFile.print("\"\n");
      
      user_stream->print("}:xdstopjson");                                           dataFile.print("}:xdstopjson");
    }else{
      user_stream->println("xdstartjson:{");
      user_stream->println("    \"Sensor error\":\"1\"");
      user_stream->print("}:xdstopjson");
    }
  }
////////////////////////
///////////////////////
//////////////////////
