/////////////////////
#define RX_BUF_SIZE_OF 63
#define TX_BUF_SIZE_OF 31
#define MESSAGE_SIZE_OF 63
class gr_serial{
  public:
    char rx_buf[RX_BUF_SIZE_OF+1];
    char tx_buf[TX_BUF_SIZE_OF+1];
    byte rx_buf_point=0;
    byte tx_buf_point=0;

    //int nmea_parser(char in_byte);
    int do(Stream* uart);
    int get_id();
    int get_int(int start_of);
    char get_char(int start_of);
    float get_float(int start_of);
    
    struct nmea_db {
      const char header[10];//STRIM,WRNRF
      const int len;
      const byte type[20];//0-byte;1-char;2-int32,3-int64,4-float,5-double,6-STRING,7-RAW
    };
};


int gr_serial::do(Stream* uart){
  while(uart.available()){
    rx_buf_point=(rx_buf_point+1)&(RX_BUF_SIZE_OF);
    uart.readBytes(rx_buf[rx_buf_point], 1);
    if(rx_buf[rx_buf_point]==0xAA){
    if(rx_buf[(rx_buf_point-1)&(RX_BUF_SIZE_OF)]==0xEF){
    if(rx_buf[(rx_buf_point-MESSAGE_SIZE_OF+1)&(RX_BUF_SIZE_OF)]==0xCD){
    if(rx_buf[(rx_buf_point-MESSAGE_SIZE_OF)&(RX_BUF_SIZE_OF)]==0xAB){
      //Find_mesage_then_chec_crc
      //CRC
      //EMMIT
      return 1;
    }}}}
  }
  return 0;
}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//коммент
//  #define NMEADB_SIZE 2
//  const nmea_db nmeadb[NMEADB_SIZE]= {   {  "TEST",3,{ 1,1,1 } },
//                                           {  "ECHO",4,{ 1,1,1,1 } }  };  
/*int gribikc_serial::nmea_parser(char in_byte){
  static bool found_start=0;
  static bool found_end=0;
  static byte point=0;
  static signed int message_id=-1;
  static int comma_counter=0;
  //коммент
  int i=0;
  int k=0;
  int j=0;
  //коммент
  if(in_byte=='$'){
    point=0;
    found_start=1;
    found_end=0;
    Serial.println("found:$");
    return 0;
  }
  //коммент
  if(in_byte==10 || in_byte==13){
    found_end=1;
    Serial.println("found:<cl>||<nr>");
  }
  ////коммент
  if(found_start==1 && found_end==1){//Найдено сообщение//Обработка
    message_id=-1;
    comma_counter=0;
    Serial.println("$DEBUG,1,Parsing,0");//$TEST,1,2,3,4
    for(i=0;i<point;i++){//обходим весь буфер
      for(j=0;j<NMEADB_SIZE;j++){//обход массива узнаваемых
        for(k=i;rx_buf[k]!=',';k++){//идем по массиву до следующей запятой
          if(comma_counter==0){//проверяем заголовок
            if(rx_buf[k]!=nmeadb[j].header[k]){
              break;
            }else if(rx_buf[k+1]==','){
              Serial.println("$DEBUG,1,SomeFind,0");
            }
          }
        }
      }
      comma_counter++;
      i=k;
    }
    comma_counter=0;
    point=0;
    found_start=0;
    found_end=0;
    return 0;
  }
  //коммент
  if(found_start==0 && found_end==1){//Был найден конец сообщения но небыло $
    point=0;
    found_start=0;
    found_end=0;
    return 0;
  }
  //Заполняем буфер после обнаружения $
  rx_buf[point]=in_byte;
  point++;
}*/
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

////////////////////////////////
////////////////////////////////
	char uart_both_redirect(Stream* a,Stream* b){
	  char in_byte;
	  while(a->available()){ 
		in_byte=a->read(); 
		b->print(in_byte); 
	  }
	  while(b->available()){ 
		in_byte=b->read(); 
		a->print(in_byte); 
	  }
	  return in_byte;
	}
//////////////////////////////
//////////////////////////////
