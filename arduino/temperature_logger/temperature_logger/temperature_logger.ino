#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

  #define SD_cs 10
  
  Sd2Card card;
  SdVolume volume;
  SdFile root;
  
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
      init_sd();
    //BMP180
      if(!bmp.begin()) {/* Initialise the sensor */
        /* There was a problem detecting the BMP085 ... check your connections */
        Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
        while(1);
      }
      displaySensorDetails();/* Display some basic information on this sensor */
  
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
//////////////////
/////////////////
////////////////
  void init_sd(){
    if (!card.init(SPI_HALF_SPEED, SD_cs)) {
      user_stream->println("SD_init...Fail");
    } else {
      user_stream->println("SD_init...Done");
      if (volume.init(card)) {
        user_stream->println("SD_volume...Done");
      }else{
        user_stream->println("SD_volume...FALSE");  
      }
    }  
    uint32_t volumesize;
  
    volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
    volumesize *= volume.clusterCount();       // we'll have a lot of clusters
    volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
    volumesize /= 1024;
    user_stream->print("SD_size (Gb):  ");
    user_stream->println((float)volumesize / 1024.0);      
  }
////////////////////////
///////////////////////
//////////////////////
  void displaySensorDetails(void){
    sensor_t sensor;
    bmp.getSensor(&sensor);
    user_stream->println("------------------------------------");
    user_stream->print  ("Sensor:       "); user_stream->println(sensor.name);
    user_stream->print  ("Driver Ver:   "); user_stream->println(sensor.version);
    user_stream->print  ("Unique ID:    "); user_stream->println(sensor.sensor_id);
    user_stream->print  ("Max Value:    "); user_stream->print(sensor.max_value); Serial.println(" hPa");
    user_stream->print  ("Min Value:    "); user_stream->print(sensor.min_value); Serial.println(" hPa");
    user_stream->print  ("Resolution:   "); user_stream->print(sensor.resolution); Serial.println(" hPa");  
    user_stream->println("------------------------------------");
    user_stream->println("");
  }
  ///////////////////
  void bmp180_read(){
      /* Get a new sensor event */ 
    sensors_event_t event;
    bmp.getEvent(&event);
   
    /* Display the results (barometric pressure is measure in hPa) */
    if (event.pressure){
      /* Display atmospheric pressue in hPa */
      user_stream->print("Pressure:    ");
      user_stream->print(event.pressure);
      user_stream->println(" hPa");
      
      float temperature;
      bmp.getTemperature(&temperature);
      user_stream->print("Temperature: ");
      user_stream->print(temperature);
      user_stream->println(" C");
  
      float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
      user_stream->print("Altitude:    "); 
      user_stream->print(bmp.pressureToAltitude(seaLevelPressure,event.pressure)); 
      user_stream->println(" m");
      user_stream->println("");
    }else{
      user_stream->println("Sensor error");
    }
  }
////////////////////////
///////////////////////
//////////////////////
