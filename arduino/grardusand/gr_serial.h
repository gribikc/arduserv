/////////////////////
#define RX_BUF_SIZE_OF 63
#define TX_BUF_SIZE_OF 31
#define MESSAGE_SIZE_OF 63
class gr_serial{
  public:
    unsigned char rx_buf[RX_BUF_SIZE_OF+1];
    unsigned char tx_buf[TX_BUF_SIZE_OF+1];
    int rx_buf_point=0;
    int tx_buf_point=0;

    //int nmea_parser(char in_byte);
    int do_rx(Stream* uart);
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


  int gr_serial::do_rx(Stream* uart){
    int temp_point=0;
    while(uart->available()){
      rx_buf_point=(rx_buf_point+1)&(RX_BUF_SIZE_OF);
      uart->readBytes(&rx_buf[rx_buf_point], 1);
      if(rx_buf[rx_buf_point]==0x2A){//try to find message
        if(rx_buf[((rx_buf_point-1)&(RX_BUF_SIZE_OF))]==0xEF){
          if(rx_buf[(rx_buf_point-MESSAGE_SIZE_OF+1)&(RX_BUF_SIZE_OF)]==0xCD){
            if(rx_buf[(rx_buf_point-MESSAGE_SIZE_OF)&(RX_BUF_SIZE_OF)]==0xAB){
              //Find_mesage_then_chec_crc
              //CRC
              //EMMIT
              return 1;
      } } } }//end try to find message
    }//whileend
    return 0;
  }
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
int gr_serial::get_id(){//uart_data.rx_buf[(uart_data.rx_buf_point-MESSAGE_SIZE_OF+2)&(RX_BUF_SIZE_OF)],HEX);
  return rx_buf[(rx_buf_point-MESSAGE_SIZE_OF+2)&(RX_BUF_SIZE_OF)];
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
//////////////////////////////
//////////////////////////////
