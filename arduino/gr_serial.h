/////////////////////
class gribikc_serial{
  public:
    char rx_buf[32];
    char tx_buf[32];
    byte rx_buf_point=0;
    byte tx_buf_point=0;

    int nmea_parser(char in_byte);
    struct nmea_db {
      const char header[10];//STRIM,WRNRF
      const int len;
      const byte type[20];//0-byte;1-char;2-int32,3-int64,4-float,5-double,6-STRING,7-RAW
    };

    #define NMEADB_SIZE 2
    const nmea_db nmeadb[NMEADB_SIZE]= {   {  "TEST",3,{ 1,1,1 } },
                                           {  "ECHO",4,{ 1,1,1,1 } }  };  
};
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//коммент
int gribikc_serial::nmea_parser(char in_byte){
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
}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
void gribikc_check_serial(){
	//char i;
	//char sdacb[4];
	
	//sdacb[0]=Serial.available();
	//if(sdacb[0]>0){
		//for(i=0;i<sdacb[0];i++){
			/*if(Serial.peek()=='$'){
				Serial.println("Found:$");
				//Serial.read();
			}else{*/
				//if(while_counter-while_counter_log_delay>=30000){
				//	while_counter_log_delay=while_counter;

				//	Serial.print("Buf size:");
				//	Serial.println(sdacb[0],DEC);
				//}
			//}
		//}
	//}
}
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
	void uart_both_redirect_s1_s(){
	  char in_byte;
	  while(Serial1.available()){ 
		in_byte=Serial1.read(); 
		Serial.print(in_byte); 
	  }
	  while(Serial.available()){ 
		in_byte=Serial.read(); 
		Serial1.print(in_byte); 
	  }
	}
	void uart_redirect_s_to_s1(){
	  char in_byte;
	  while(Serial.available()){ 
		in_byte=Serial.read(); 
		Serial1.print(in_byte); 
	  }
	}
	//////////////////////////////
	//////////////////////////////
	void uart_both_redirect_s2_s(){
	  char in_byte;
	  while(Serial2.available()){ 
		in_byte=Serial2.read(); 
		Serial.print(in_byte); 
	  }
	  while(Serial.available()){ 
		in_byte=Serial.read(); 
		Serial2.print(in_byte); 
	  }
	}
	void uart_redirect_s_to_s2(){
	  char in_byte;
	  while(Serial.available()){ 
		in_byte=Serial.read(); 
		Serial2.print(in_byte); 
	  }
	}
	//////////////////////////////
	//////////////////////////////
	void uart_both_redirect_s3_s(){
	  char in_byte;
	  while(Serial3.available()){ 
		in_byte=Serial3.read(); 
		Serial.print(in_byte); 
	  }
	  while(Serial.available()){ 
		in_byte=Serial.read(); 
		Serial3.print(in_byte); 
	  }
	}
	void uart_redirect_s_to_s3(){
	  char in_byte;
	  while(Serial.available()){ 
		in_byte=Serial.read(); 
		Serial3.print(in_byte); 
	  }
}
//////////////////////////////
//////////////////////////////

