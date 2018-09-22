/* Memory Map */
  #define CONFIG      0x00
  #define EN_AA       0x01
  #define EN_RXADDR   0x02
  #define SETUP_AW    0x03
  #define SETUP_RETR  0x04
  #define RF_CH       0x05
  #define RF_SETUP    0x06
  #define STATUS      0x07
  #define OBSERVE_TX  0x08
  #define RPD         0x09
  #define RX_ADDR_P0  0x0A
  #define RX_ADDR_P1  0x0B
  #define RX_ADDR_P2  0x0C
  #define RX_ADDR_P3  0x0D
  #define RX_ADDR_P4  0x0E
  #define RX_ADDR_P5  0x0F
  #define TX_ADDR     0x10
  #define RX_PW_P0    0x11
  #define RX_PW_P1    0x12
  #define RX_PW_P2    0x13
  #define RX_PW_P3    0x14
  #define RX_PW_P4    0x15
  #define RX_PW_P5    0x16
  #define FIFO_STATUS 0x17
  #define DYNPD       0x1C
  #define FEATURE     0x1D

/* configuratio nregister */
  #define MASK_RX_DR  64
  #define MASK_TX_DS  32
  #define MASK_MAX_RT 16
  #define EN_CRC      8
  #define CRCO        4
  #define PWR_UP      2
  #define PRIM_RX     1
/* enable auto acknowledgment */
  #define ENAA_P5     32
  #define ENAA_P4     16
  #define ENAA_P3     8
  #define ENAA_P2     4
  #define ENAA_P1     2
  #define ENAA_P0     1
/* enable rx addresses */
  #define ERX_P5      32
  #define ERX_P4      16
  #define ERX_P3      8
  #define ERX_P2      4
  #define ERX_P1      2
  #define ERX_P0      1
/* setup of address width */
  #define AW3          1 /* 2 bits */
  #define AW4          2 /* 2 bits */
  #define AW5          3 /* 2 bits */
/* setup of auto re-transmission */
  #define ARD         4 /* 4 bits */
  #define ARC         0 /* 4 bits */
/* RF setup register */
  #define CONT_WAVE   128
  #define PLL_LOCK    16
  #define s1Mbps       0
  #define s2Mbps       8
  #define s250Kbps     32
  #define m18dBm      0 /* 2 bits */  
  #define m12dBm      2 /* 2 bits */  
  #define m6dBm       4 /* 2 bits */  
  #define m0dBm       6 /* 2 bits */  
/* Instruction Mnemonics */
  #define R_REGISTER    0x00 /* last 4 bits will indicate reg. address */
  #define W_REGISTER    0x20 /* last 4 bits will indicate reg. address */
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
class gribikc_nrf24l01p{
    public:
      bool write_reg(char addr,char data);
      int read_reg(char addr);
      bool message_available();
      char take_message();
      void read_to_s();
      
      void get_config();
      void init_rx();
      void init_tx();
      void send_message();
};

///////////////////////////////////////////////////////////////////////////////////////////
bool gribikc_nrf24l01p::message_available(){
  digitalWrite(nrf24l01_cs, LOW);
  if((SPI.transfer(0x17)&0x0E)==0){
    if((SPI.transfer(0x00)&0x03)==2){
      digitalWrite(nrf24l01_cs, HIGH); 
      return 1;      
    }
  }
  digitalWrite(nrf24l01_cs, HIGH);
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
bool gribikc_nrf24l01p::write_reg(char addr,char data){
  char return_char;
  digitalWrite(nrf24l01_cs, LOW);
    return_char=SPI.transfer((0x20|addr));
    SPI.transfer(data);//4
  digitalWrite(nrf24l01_cs, HIGH);
  return return_char;
}
///////////////////////////////////////////////////////////////////////////////////////////
int gribikc_nrf24l01p::read_reg(char addr){
  digitalWrite(nrf24l01_cs, LOW);
    SPI.transfer((0x00|addr));
    i=SPI.transfer(0x00);//4
  digitalWrite(nrf24l01_cs, HIGH);
  return i;
}
///////////////////////////////////////////////////////////////////////////////////////////
char gribikc_nrf24l01p::take_message(){
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x61);
  //if((SPI.transfer(0x61)&14)!=14){
    Serial.print("DATA0:");
    for(i=0;i<=31;i++){
      Serial.print(":");
      Serial.print(SPI.transfer(0x00));
    }
    Serial.print(";\n");
  //}
  digitalWrite(nrf24l01_cs, HIGH);
}
///////////////////////////////////////////////////////////////////////////////////////////
void gribikc_nrf24l01p::read_to_s(){
  if((read_reg(0x17)&3)!=1){  
    digitalWrite(nrf24l01_cs, LOW);
    if((SPI.transfer(96)&14)!=14){
      Serial.print("DATA1:");
      for(i=0;i<=31;i++){
        Serial.print(":");
        Serial.print(SPI.transfer(0x00),DEC);
      }
      Serial.print(";\n");
    }
    digitalWrite(nrf24l01_cs, HIGH);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void gribikc_nrf24l01p::get_config(){
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
void gribikc_nrf24l01p::init_rx(){
  digitalWrite(nrf24l01_ce, LOW);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|CONFIG);//0x20//CONFIG-0x00
  SPI.transfer(EN_CRC|CRCO|PWR_UP|PRIM_RX);//0x0F
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|EN_AA);//0x21//EN_AA-0x01
  SPI.transfer(0x00);//0x00//~ENAA_P5|~ENAA_P4|~ENAA_P3|~ENAA_P2|~ENAA_P1|~ENAA_P0
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|EN_RXADDR);//0x22//EN_RXADDR-0x02*
  SPI.transfer(ERX_P0);//0x3F//ERX_P5|ERX_P4|ERX_P3|ERX_P2|ERX_P1|ERX_P0
  digitalWrite(nrf24l01_cs, HIGH);

  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|SETUP_AW);
  SPI.transfer(AW5);
  digitalWrite(nrf24l01_cs, HIGH);

  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|SETUP_RETR);
  SPI.transfer(0x00);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|RF_CH);//RF_CH-0x05*
  SPI.transfer(0x02);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|RF_SETUP);//0x26//RF_SETUP-0x06*
  SPI.transfer(s250Kbps|m0dBm);//0x26
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|RX_PW_P0);//RX_PW_P0-0x11
  SPI.transfer(0x20);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|RX_PW_P1);//RX_PW_P1-0x12
  SPI.transfer(0x20);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|RX_PW_P2);//RX_PW_P2-0x13
  SPI.transfer(0x20);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|RX_PW_P3);//RX_PW_P3-0x14
  SPI.transfer(0x20);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|RX_PW_P4);//RX_PW_P4-0x15
  SPI.transfer(0x20);
  digitalWrite(nrf24l01_cs, HIGH);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|RX_PW_P5);//RX_PW_P5-0x16
  SPI.transfer(0x20);
  digitalWrite(nrf24l01_cs, HIGH);

  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|DYNPD);//RX_PW_P5-0x16
  SPI.transfer(0x00);
  digitalWrite(nrf24l01_cs, HIGH);

  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(W_REGISTER|FEATURE);//RX_PW_P5-0x16
  SPI.transfer(0x00);
  digitalWrite(nrf24l01_cs, HIGH);

  digitalWrite(nrf24l01_ce, HIGH);
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void gribikc_nrf24l01p::init_tx(){
  digitalWrite(nrf24l01_ce, LOW);
  
  digitalWrite(nrf24l01_cs, LOW);
  SPI.transfer(0x20);//0x20//CONFIG-0x00//W_REGISTER|CONFIG
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

  digitalWrite(nrf24l01_ce, HIGH);
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void gribikc_nrf24l01p::send_message(){
  init_tx();  
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
  //nrf24l01_send_message();
  //Serial.println("Send...OK");
  //nrf24l01_init_rx();
      /*digitalWrite(nrf24l01_cs, LOW);
      Serial.print("Carrier Detect");
      Serial.print(": ");
      Serial.print(SPI.transfer(9));
      Serial.print(":");
      Serial.print(SPI.transfer(0x00));
      digitalWrite(nrf24l01_cs, HIGH);
      Serial.print(";\n");

      digitalWrite(nrf24l01_cs, LOW);
      Serial.print("Lost packets");
      Serial.print(": ");
      Serial.print(SPI.transfer(8));
      Serial.print(":");
      Serial.print((SPI.transfer(0x00)));
      digitalWrite(nrf24l01_cs, HIGH);
      Serial.print(";\n");*/
  ///
