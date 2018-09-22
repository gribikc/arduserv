void start_init(){
  //SPI init
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    SPI.setBitOrder(MSBFIRST);
  //Initialize serial communication
    Serial.begin(115200);
    //Serial1.begin(115200);
    //Serial2.begin(115200);
    //Serial3.begin(115200);//74880
  //NRF24L01
    pinMode(nrf24l01_ce, OUTPUT);//RF-CE
    pinMode(nrf24l01_cs, OUTPUT);//RF-CS
    digitalWrite(nrf24l01_ce, HIGH);//
    digitalWrite(nrf24l01_cs, HIGH);//
  //
    SPI.transfer(0); //�� �����
  //
    delay(5000);
    Serial.println("Init...done.");
}
