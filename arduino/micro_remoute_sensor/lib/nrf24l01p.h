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
  #define ARC15				0x0F
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
/* STATUS register */
  #define RX_DR		0x40		  
/* Instruction Mnemonics */
  #define R_REGISTER    0x00 /* last 4 bits will indicate reg. address */
  #define W_REGISTER    0x20 /* last 4 bits will indicate reg. address */
  #define W_TX_PAYLOAD	0xA0
  #define R_RX_PAYLOAD	0x61
  #define FLUSH_TX		0xE1
  #define FLUSH_RX		0xE2
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
class gribikc_nrf24l01p{
    public:
      bool write_reg(char addr,char data);
	  bool write_reg_fifo(char addr,char *data,int len);
      int read_reg(char addr);
      bool message_available();
	  bool message_sent();
      char print_message();
	  bool read_message(char *buf,int len);
      void read_to_s();
      
      void get_config();
	  void init();
      void init_rx();
      void init_tx();
	  void init_rx_shbu();
	  void send_receipt();
      void send_message();
	  void send_message_long();
	  void scan_PDCD();
	  
	int i;
	byte tuner_mode=0;//0-IDLE;1-RX;2-TX;
};

///////////////////////////////////////////////////////////////////////////////////////////
bool gribikc_nrf24l01p::message_available(){//+
	//digitalWrite(nrf24l01_cs, LOW);
		/*if((SPI.transfer(FIFO_STATUS)&0x0E)!=0x0E){
			if((SPI.transfer(0x00)&0x03)==2){
			  digitalWrite(nrf24l01_cs, HIGH); 
			  return 1;      
			}
		}*/
		/*SPI.transfer(FIFO_STATUS);
		if((SPI.transfer(0x00)&0x01)==0){
		  digitalWrite(nrf24l01_cs, HIGH); 
		  return 1;      
		}*/
	digitalWrite(nrf24l01_cs, LOW);
		if((SPI.transfer(W_REGISTER|STATUS)&MASK_RX_DR)==MASK_RX_DR){
			SPI.transfer(MASK_RX_DR);
			digitalWrite(nrf24l01_cs, HIGH); 
			return 1;      
		}
	digitalWrite(nrf24l01_cs, HIGH);
		
	digitalWrite(nrf24l01_cs, LOW);
		SPI.transfer(FIFO_STATUS);
		if((SPI.transfer(0x00)&0x01)==0){
		  digitalWrite(nrf24l01_cs, HIGH); 
		  return 1;      
		}
	digitalWrite(nrf24l01_cs, HIGH);
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
bool gribikc_nrf24l01p::message_sent(){//+
	digitalWrite(nrf24l01_cs, LOW);
		if((SPI.transfer(W_REGISTER|STATUS)&MASK_TX_DS)==MASK_TX_DS){
			SPI.transfer(MASK_TX_DS);
			digitalWrite(nrf24l01_cs, HIGH); 
			return 1;      
		}
	digitalWrite(nrf24l01_cs, HIGH);
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
bool gribikc_nrf24l01p::write_reg(char addr,char data){//+
	digitalWrite(nrf24l01_cs, LOW);
		SPI.transfer((W_REGISTER|addr));
		SPI.transfer(data);//4
	digitalWrite(nrf24l01_cs, HIGH);
	return 1;
}
bool gribikc_nrf24l01p::write_reg_fifo(char addr,char *data,int len){//
	int i;
	digitalWrite(nrf24l01_cs, LOW);
		SPI.transfer((W_REGISTER|addr));
		for(i=0;i<len;i++){
			SPI.transfer(data[i]);//4
		}
	digitalWrite(nrf24l01_cs, HIGH);
	return 1;
}
///////////////////////////////////////////////////////////////////////////////////////////
int gribikc_nrf24l01p::read_reg(char addr){//+
	int i=0;
	digitalWrite(nrf24l01_cs, LOW);
		SPI.transfer((0x00|addr));
		i=SPI.transfer(0x00);//4
	digitalWrite(nrf24l01_cs, HIGH);
	return i;
}
///////////////////////////////////////////////////////////////////////////////////////////
char gribikc_nrf24l01p::print_message(){//+
	int i;
	digitalWrite(nrf24l01_cs, LOW);
	SPI.transfer(R_RX_PAYLOAD);
	Serial.print("DATA0:");
	for(i=0;i<=31;i++){
	  Serial.print(":");
	  Serial.print(SPI.transfer(0x00));
	}
	Serial.print(";\n");
	digitalWrite(nrf24l01_cs, HIGH);
}
///////////////////////////////////////////////////////////////////////////////////////////
bool gribikc_nrf24l01p::read_message(char *buf,int len){//+
	//message_available();
	int i;
	digitalWrite(nrf24l01_cs, LOW);
		SPI.transfer(R_RX_PAYLOAD);
		for(i=0;i<len;i++){
		  buf[i]=SPI.transfer(0x00);
		}
	digitalWrite(nrf24l01_cs, HIGH);
	return 1;
}
///////////////////////////////////////////////////////////////////////////////////////////
void gribikc_nrf24l01p::read_to_s(){//+
	int i;
	if(tuner_mode==1){//0-IDLE;1-RX;2-TX;)
		if(message_available()){  
			digitalWrite(nrf24l01_cs, LOW);
				SPI.transfer(R_RX_PAYLOAD);
				for(i=0;i<32;i++){//32
					//Serial.print(char(i));//SPI.transfer(0x00)
					Serial.write(SPI.transfer(0x00));
				}
			digitalWrite(nrf24l01_cs, HIGH);
			if(!message_available()){
				init_tx();
				send_receipt();
			}
		}
	}else{
		if(message_sent()){
			init_rx();
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void gribikc_nrf24l01p::get_config(){//+
	int i;
	for(i=0;i<30;i++){
		Serial.print(i);
		Serial.print(":");
		Serial.print(read_reg(i));
		Serial.print("\n");
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void gribikc_nrf24l01p::init_rx_shbu(){
	digitalWrite(nrf24l01_ce, LOW);
		write_reg(CONFIG,EN_CRC|PWR_UP|PRIM_RX);
		//write_reg(EN_AA,0x00);
		write_reg(EN_RXADDR,ERX_P0);//ERX_P0|ERX_P1|ERX_P2
		//write_reg(SETUP_AW,AW5);//!!!???
		//write_reg(SETUP_RETR,ARC15);
		//write_reg(RF_CH,0x64);
		//write_reg(RF_SETUP,s250Kbps|m0dBm);
		//write_reg(DYNPD,0x00);		
		write_reg(RX_PW_P0,0x20);
		//write_reg(RX_PW_P1,0x00);
		//write_reg(RX_PW_P2,0x00);
		//write_reg(RX_PW_P3,0x00);
		//write_reg(RX_PW_P4,0x00);
		//write_reg(RX_PW_P5,0x00);
		
		//write_reg(DYNPD,0x00);
		//write_reg(FEATURE,0x00);
	digitalWrite(nrf24l01_ce, HIGH);
}///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void gribikc_nrf24l01p::init(){//+
	digitalWrite(nrf24l01_ce, LOW);
		write_reg(CONFIG,EN_CRC|CRCO);
		write_reg(EN_AA,0x00);
		write_reg(EN_RXADDR,ERX_P0|ERX_P1|ERX_P2);//ERX_P0|ERX_P1|ERX_P2
		write_reg(SETUP_AW,AW5);
		write_reg(SETUP_RETR,0x00);
		write_reg(RF_CH,0x64);
		write_reg(RF_SETUP,s250Kbps|m0dBm);		
		write_reg(RX_PW_P0,0x20);
		write_reg(RX_PW_P1,0x20);
		write_reg(RX_PW_P2,0x20);
		write_reg(RX_PW_P3,0x00);
		write_reg(RX_PW_P4,0x00);
		write_reg(RX_PW_P5,0x00);
		write_reg(DYNPD,0x00);
		write_reg(FEATURE,0x00);
	digitalWrite(nrf24l01_ce, HIGH);
	tuner_mode=0;//0-IDLE;1-RX;2-TX;
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void gribikc_nrf24l01p::init_rx(){//+
	digitalWrite(nrf24l01_ce, LOW);
		write_reg(CONFIG,EN_CRC|CRCO|PWR_UP|PRIM_RX);
	digitalWrite(nrf24l01_ce, HIGH);
	tuner_mode=1;//0-IDLE;1-RX;2-TX;
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void gribikc_nrf24l01p::init_tx(){//+
	digitalWrite(nrf24l01_ce, LOW);
		write_reg(CONFIG,EN_CRC|CRCO|PWR_UP);
	digitalWrite(nrf24l01_ce, HIGH);
	tuner_mode=2;//0-IDLE;1-RX;2-TX;
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void gribikc_nrf24l01p::send_receipt(){
	init_tx();
	digitalWrite(nrf24l01_ce, LOW);
		digitalWrite(nrf24l01_cs, LOW);
			SPI.transfer(W_TX_PAYLOAD);//0-spi fifo-addr
			for(int i=0;i<32;i++){	
				SPI.transfer(0xAA);//0
			}
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
	static char cnt=0;
	cnt++;
	init_tx();
	digitalWrite(nrf24l01_ce, LOW);
		digitalWrite(nrf24l01_cs, LOW);
			SPI.transfer(W_TX_PAYLOAD);//0-spi fifo-addr
				SPI.transfer(0xAA);//0
				SPI.transfer(0xBB);//1
				SPI.transfer(0x01);//2
				SPI.transfer(cnt);//3
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
				SPI.transfer(0xCC);//30
				SPI.transfer(0xDD);//31
		digitalWrite(nrf24l01_cs, HIGH);
	digitalWrite(nrf24l01_ce, HIGH);
}
void gribikc_nrf24l01p::send_message_long(){
	static char cnt=0;
	static char hr=0;
	static char mn=0;
	static char sc=0;
	cnt++;
	if(sc<59){
		sc++;
	}else{
		sc=0;
		if(mn<59){
			mn++;
		}else{
			mn=0;
			if(hr<23){
				hr++;
			}else{
				hr=0;
			}
		}
	}
	
	init_tx();
	//digitalWrite(nrf24l01_ce, LOW);
	digitalWrite(nrf24l01_ce, HIGH);
		digitalWrite(nrf24l01_cs, LOW);
			SPI.transfer(W_TX_PAYLOAD);//0-spi fifo-addr
				SPI.transfer(0xAA);//0
				SPI.transfer(0xBB);//1
				SPI.transfer(0x03);//2
				SPI.transfer(cnt);//3
				SPI.transfer(0);//4
				SPI.transfer(0);//5
				SPI.transfer(hr);//6
				SPI.transfer(mn);//7
				SPI.transfer(sc);//8
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
				SPI.transfer(0);//31
		digitalWrite(nrf24l01_cs, HIGH);
	//digitalWrite(nrf24l01_ce, HIGH);
		//while(read_reg(FIFO_STATUS)&16!=16){}
		delay(20);//???
	//digitalWrite(nrf24l01_ce, LOW);
		digitalWrite(nrf24l01_cs, LOW);
			SPI.transfer(W_TX_PAYLOAD);//0-spi fifo-addr
				SPI.transfer(0);//0
				SPI.transfer(0);//1
				SPI.transfer(0);//2
				SPI.transfer(0);//3
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
				SPI.transfer(0xCC);//30
				SPI.transfer(0xDD);//31
		digitalWrite(nrf24l01_cs, HIGH);
	//digitalWrite(nrf24l01_ce, HIGH);
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
/*void gribikc_nrf24l01p::scan_PDCD(){
	int cnt=0;
	int cnt_i=0;
	int cnt_pdcd=0;
	init_rx();
	delay(100);
	digitalWrite(nrf24l01_ce, HIGH);
	for(cnt=0;cnt<=125;cnt++){
		digitalWrite(nrf24l01_ce, LOW);
			write_reg(CONFIG,EN_CRC|CRCO|PRIM_RX);
			write_reg(RF_CH,cnt);
			write_reg(CONFIG,EN_CRC|CRCO|PWR_UP|PRIM_RX);
		digitalWrite(nrf24l01_ce, LOW);
		digitalWrite(nrf24l01_ce, HIGH);
		delay(100);
		digitalWrite(nrf24l01_ce, LOW);

		
		cnt_pdcd=0;
		for(cnt_i=0;cnt_i<=100;cnt_i++){
			cnt_pdcd+=read_reg(RPD);
		}
		Serial.print(cnt_pdcd,DEC);
		Serial.print(".");
	}
	Serial.println();
}*/
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void gribikc_nrf24l01p::scan_PDCD(){
	int cnt=0;
	int cnt_i=0;
	int cnt_pdcd=0;
	
	digitalWrite(nrf24l01_ce, LOW);
	delay(100);
	init_rx();
	delay(100);
	digitalWrite(nrf24l01_ce, LOW);
	write_reg(CONFIG,PRIM_RX);
	write_reg(RF_SETUP,s1Mbps);
	delay(100);
	

	for(cnt=0;cnt<=125;cnt++){
		cnt_pdcd=0;
		for(cnt_i=0;cnt_i<10;cnt_i++){
			cnt_pdcd+=read_reg(RPD)&0x01;
			write_reg(RF_CH,cnt);
			cnt_pdcd+=read_reg(RPD)&0x01;
			delay(1);
			cnt_pdcd+=read_reg(RPD)&0x01;
			digitalWrite(nrf24l01_ce, HIGH);
			cnt_pdcd+=read_reg(RPD)&0x01;
			delay(1);
			cnt_pdcd+=read_reg(RPD)&0x01;
			digitalWrite(nrf24l01_ce, LOW);
			cnt_pdcd+=read_reg(RPD)&0x01;
			delay(1);	
			cnt_pdcd+=read_reg(RPD)&0x01;
		}
		Serial.print(cnt_pdcd,DEC);//,DEC
		Serial.print(".");
	}

	Serial.println();
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
