//#define SEALEVELPRESSURE_HPA (1013.25)//1013.25

#define nrf24l01_ce 42
#define nrf24l01_cs 41
#define SD_cs 49

#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "var.h"
#include "lib/nrf24l01p.h"
#include "lib/gribikc_serial.h"
#include <Adafruit_BME280.h>


gribikc_serial usb_serial;
gribikc_nrf24l01p nrf24l01p;

Adafruit_BME280 bme;

#include "init.h"

void setup() {
  start_init();
 init_sd();
  Serial.println("Start...");
    nrf24l01p.get_config();
    nrf24l01p.init();
    nrf24l01p.init_rx();
    nrf24l01p.get_config();
  Serial.println("NRF...done");
    init_sd();

    init_BME280();

    
  
}

void loop() {
  // put your main code here, to run repeatedly:
    //nrf24l01p.read_to_s();
    //uart_both_redirect_s1_s();//GPS
    uart_both_redirect_s2_s();//BT
    //uart_both_redirect_s3_s();//RS232
    
    //printValues();
    //BME280_send_data();
    //delay(1000);
}
void BME280_send_data() {
    Serial.print("$BME280,thpa,");
    Serial.print(bme.readTemperature());
    Serial.print(",");
    Serial.print(bme.readHumidity());
    Serial.print(",");
    Serial.print(bme.readPressure() / 100.0F);//1013.25hPa~760mmHg~1atm~101.325kPa
    Serial.print(",");
    Serial.print(bme.readAltitude(1013.25));//1013.25hPa~760mmHg~1atm~101.325kPa
    Serial.print("*00");
    Serial.println();
}
