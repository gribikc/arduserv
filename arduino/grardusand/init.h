void start_init(){
  //var
    long_timer_cnt=0;
  //SPI init
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    SPI.setBitOrder(MSBFIRST);
  //Initialize serial communication
    Serial.begin (115200);//USB   //
    Serial1.begin(115200);//GPS   //
    Serial2.begin(115200);//BT   // AT+BAUD=115200,N
    Serial3.begin(9600);//RS232 //74880
  //NRF24L01
    pinMode(nrf24l01_ce, OUTPUT);//RF-CE
    pinMode(nrf24l01_cs, OUTPUT);//RF-CS
    digitalWrite(nrf24l01_ce, HIGH);//
    digitalWrite(nrf24l01_cs, HIGH);//

    pinMode(SD_cs, OUTPUT);//SD_cs
    digitalWrite(SD_cs, HIGH);//
  //
    SPI.transfer(0); //�� �����
  //
    delay(3000);

    if(!SD.exists("bmp180.log")){
      File myFile;
      myFile=SD.open("bmp180.log", FILE_WRITE);
      myFile.close();
    }
    user_stream->println("Init...done.");
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
  void init_BME280(){
      if(bme.begin()){
        user_stream->println("BMP_init...DONE");
        bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                        Adafruit_BME280::SAMPLING_X16,  // temperature
                        Adafruit_BME280::SAMPLING_X16, // pressure
                        Adafruit_BME280::SAMPLING_X16,  // humidity
                        Adafruit_BME280::FILTER_X16,
                        Adafruit_BME280::STANDBY_MS_0_5 );
      }else{
        user_stream->println("BMP_init...FALSE");  
      }  
  }
  ///
  void BME280_send_nmea() {
    user_stream->print("$BME280,thpa,");
      user_stream->print(bme.readTemperature());
    user_stream->print(",");
      user_stream->print(bme.readHumidity());
    user_stream->print(",");
      user_stream->print(bme.readPressure() / 100.0F);//1013.25hPa~760mmHg~1atm~101.325kPa
    user_stream->print(",");
      user_stream->print(bme.readAltitude(1013.25));//1013.25hPa~760mmHg~1atm~101.325kPa
    user_stream->print(",0*00");
    user_stream->println();
  }
  ///
  void BME280_send_json() {
    user_stream->print("xdstartjson:{\n");
    user_stream->print("    \"type\":\"bmp_cur\",\n");
    user_stream->print(" \"Temperature\":");
      user_stream->print(bme.readTemperature());
    user_stream->print(",\n \"Humidity\":");
      user_stream->print(bme.readHumidity());
    user_stream->print(",\n \"Pressure\":");
      user_stream->print(bme.readPressure() / 100.0F);//1013.25hPa~760mmHg~1atm~101.325kPa
    user_stream->print(",\n \"Altitude\":");
      user_stream->print(bme.readAltitude(1013.25));//1013.25hPa~760mmHg~1atm~101.325kPa
    user_stream->print("\n}:xdstopjson\n");
  }
  void BME280_save_to_file() {
    unsigned long count=0;
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
      dataFile.print(",hpa:");
      dataFile.print(bme.readPressure());
      dataFile.print(",");
      dataFile.print("celsius:");
      dataFile.print(bme.readTemperature());
      dataFile.print(",");
      dataFile.print("humidity:");
      dataFile.print(bme.readHumidity());
      dataFile.print("\n");
      count++;
    }
    dataFile.flush();
    dataFile.close();
  }
/////////////////////
/////////////////////
/////////////////////
