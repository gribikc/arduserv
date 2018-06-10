///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
void get_nrf24_config(){
  int i;
  for(i=0;i<30;i++){
    digitalWrite(nrf24l01_cs, LOW);
    Serial.print(i);
    Serial.print(": ");
    Serial.print(SPI.transfer(i));
    Serial.print("  ");
    Serial.print(SPI.transfer(0x00));
    Serial.print("  ");
    Serial.print(SPI.transfer(0x00));
    Serial.print("  ");
    Serial.print(SPI.transfer(0x00));
    Serial.print("  ");
    Serial.print(SPI.transfer(0x00));
    Serial.print("  ");
    Serial.print(SPI.transfer(0x00));
    Serial.print("  ");
    Serial.print(SPI.transfer(0x00));
    digitalWrite(nrf24l01_cs, HIGH);
    Serial.print("\n");
  }
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
int nrf24l01_init_tx(){
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x20);//CONFIG-0x00
  SPI.transfer(0x04);//4
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x21);//EN_AA-0x01
  SPI.transfer(0x00);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x24);//SETUP_RETR-0x04
  SPI.transfer(0x00);
  digitalWrite(nrf24l01_cs, HIGH);
  
  //digitalWrite(nrf24l01_cs, LOW);
  //SPI.transfer(0x25);//RF_CH-0x05*
  //SPI.transfer(0x3F);
  //digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x26);//RF_SETUP-0x04
  SPI.transfer(0x26);//28
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x20);//CONFIG-0x00
  SPI.transfer(0x0E);
  digitalWrite(nrf24l01_cs, HIGH);
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
int nrf24l01_init_rx(){
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x20);//CONFIG-0x00
  SPI.transfer(0x0F);//
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x21);//EN_AA-0x01
  SPI.transfer(0x00);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x22);//EN_RXADDR-0x02*
  SPI.transfer(0x3F);
  digitalWrite(nrf24l01_cs, HIGH);
  
  /*digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x25);//RF_CH-0x05*
  SPI.transfer(0x7D);
  digitalWrite(nrf24l01_cs, HIGH);*/
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x26);//RF_SETUP-0x06*
  SPI.transfer(0x26);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x31);//RX_PW_P0-0x11
  SPI.transfer(0x20);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x32);//RX_PW_P1-0x12
  SPI.transfer(0x20);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x33);//RX_PW_P2-0x13
  SPI.transfer(0x20);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x34);//RX_PW_P3-0x14
  SPI.transfer(0x20);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x35);//RX_PW_P4-0x15
  SPI.transfer(0x20);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x36);//RX_PW_P5-0x16
  SPI.transfer(0x20);
  digitalWrite(nrf24l01_cs, HIGH);
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
int nrf24l01_send_message(){
  nrf24l01_init_tx();  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0xA0);//0-spi fifo-addr
  
  SPI.transfer(0xAA);//1
  SPI.transfer(0xBB);//2
  SPI.transfer(0x01);//3
  SPI.transfer(0);//4
  SPI.transfer(0);//5
  SPI.transfer(0);//6
  SPI.transfer(0);//7
  SPI.transfer(0);//8
  SPI.transfer(0);//9
  SPI.transfer(0);//10
  SPI.transfer(0);//11
  SPI.transfer(0);//12
  SPI.transfer(0);//13
  SPI.transfer(0);//14
  SPI.transfer(0);//15
  SPI.transfer(0);//16
  SPI.transfer(0);//17
  SPI.transfer(0);//18
  SPI.transfer(0);//19
  SPI.transfer(0);//20
  SPI.transfer(0);//21
  SPI.transfer(0);//22
  SPI.transfer(0);//23
  SPI.transfer(0);//24
  SPI.transfer(0);//25
  SPI.transfer(0);//26
  SPI.transfer(0);//27
  SPI.transfer(0);//28
  SPI.transfer(0);//29
  SPI.transfer(0);//30
  SPI.transfer(0xCC);//31
  SPI.transfer(0xDD);//32
  digitalWrite(nrf24l01_cs, HIGH);  
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
