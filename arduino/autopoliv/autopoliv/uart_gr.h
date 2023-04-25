	#ifdef DEBUG_ON
		extern Stream* debug_stream;
	#endif
	
	/*#define CMT_BYTE 0
    #define CMT_FLOAT 1
    #define CMT_EXOT 2
    #define CMT_INT 3
    #define CMT_DOUBLE 4

    #define CMI_STD 0
    #define CMI_HEAD_S 4
    #define CMI_FOOT_S 4
    #define CMI_DATA_S 7
    #define CMI_MASK 31
    #define CMI_SIZE 4*/
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
	typedef struct  {
			unsigned char	rx_buf[32];
			unsigned char	rx_buf_in_point=0;
			unsigned char	rx_buf_us_point=0;
			unsigned char	rx_in=0;

			unsigned char 	tx_buf[128];
			unsigned char	tx_buf_in_point=0;
			unsigned char	tx_buf_us_point=0;
			unsigned char	tx_in=0;
			
			Stream* uart;
			void (*parser)(unsigned char* buf,unsigned char pointer);
	} stream_buf;
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
	void collect_stream_data(stream_buf* buf){
		while(buf->uart->available()){
			buf->rx_buf_in_point=(buf->rx_buf_in_point+1)&31;
			buf->rx_buf[buf->rx_buf_in_point]=buf->uart->read();
			buf->rx_in=1;
			buf->parser(buf->rx_buf,buf->rx_buf_in_point);
		}
	}
	void write_buf_data(stream_buf* buf,unsigned char data){
		//while(buf->uart->available()){
			buf->rx_buf_in_point=(buf->rx_buf_in_point+1)&31;
			buf->rx_buf[buf->rx_buf_in_point]=data;
			buf->rx_in=1;
			buf->parser(buf->rx_buf,buf->rx_buf_in_point);
		//}
	}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
    typedef struct{
		unsigned char type;
		unsigned char start;
    } code_message_structure_gr;

    typedef struct{
        union {
			bool v_bool;
			unsigned char v_char;
			unsigned char v_uchar[4];
			signed char v_schar[4];
			//byte v_byte[4];
			unsigned int v_uint;
			signed int v_sint;
			float v_float;
			double v_double;
        } val;
    } union_data_gr;

    typedef struct {
		unsigned char type;
		unsigned char message_len;
		unsigned char header_len;
		unsigned char footer_len;
		unsigned char data_len;
		unsigned char header[CMI_HEAD_S];
		unsigned char footer[CMI_FOOT_S];
		void (*do_func) (union_data_gr*);
        union_data_gr* data_pars;
		code_message_structure_gr data_struct[CMI_DATA_S];
    } code_message_info;
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
	void find_frame_data(unsigned char* buf,unsigned char pointer,code_message_info *message_info){
		unsigned char i,j,k,p;
		for(i=0;i<CMI_SIZE;i++){//sizeof(message_info)/sizeof(code_message_info)
			for(j=0;j<message_info[i].header_len;j++){//COR_HEAD
				if(buf[((pointer-(message_info[i].message_len-1-j))&CMI_MASK)]!=message_info[i].header[j]){
					break;
				}
			}
			for(k=0;k<message_info[i].footer_len;k++){//COR_FOOT
				if(buf[((pointer-(message_info[i].footer_len-1-k))&CMI_MASK)]!=message_info[i].footer[k]){
					break;
				}
			}
			if(j==message_info[i].header_len && k==message_info[i].footer_len){
				#ifdef DEBUG_ON
					debug_stream->println("UART_GR: message recived new cast.");
				#endif
				for(p=0;p<message_info[i].data_len;p++){
					switch(message_info[i].data_struct[p].type){
						case CMT_BYTE: 
                            //message_info[i].data_pars[p].val.v_char=3  ;  //->val.v_char=3;
                            //parser_data->va
                            //buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start))&CMI_MASK);
                            message_info[i].data_pars[p].val.v_char=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start))&CMI_MASK)];
						break;
						case CMT_FLOAT:
							message_info[i].data_pars[p].val.v_uchar[0]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start))&CMI_MASK)];
							message_info[i].data_pars[p].val.v_uchar[1]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start-1))&CMI_MASK)];
							message_info[i].data_pars[p].val.v_uchar[2]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start-2))&CMI_MASK)];
							message_info[i].data_pars[p].val.v_uchar[3]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start-3))&CMI_MASK)];
						break;
						case CMT_INT:
							message_info[i].data_pars[p].val.v_uchar[0]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start))&CMI_MASK)];
							message_info[i].data_pars[p].val.v_uchar[1]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start-1))&CMI_MASK)];
							message_info[i].data_pars[p].val.v_uchar[2]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start-2))&CMI_MASK)];
							message_info[i].data_pars[p].val.v_uchar[3]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start-3))&CMI_MASK)];
						break;
						case CMT_DOUBLE:
							message_info[i].data_pars[p].val.v_uchar[0]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start))&CMI_MASK)];
							message_info[i].data_pars[p].val.v_uchar[1]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start-1))&CMI_MASK)];
							message_info[i].data_pars[p].val.v_uchar[2]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start-2))&CMI_MASK)];
							message_info[i].data_pars[p].val.v_uchar[3]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start-3))&CMI_MASK)];
							message_info[i].data_pars[p].val.v_uchar[4]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start-4))&CMI_MASK)];
							message_info[i].data_pars[p].val.v_uchar[5]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start-5))&CMI_MASK)];
							message_info[i].data_pars[p].val.v_uchar[6]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start-6))&CMI_MASK)];
							message_info[i].data_pars[p].val.v_uchar[7]=buf[((pointer-(message_info[i].message_len-1-message_info[i].data_struct[p].start-7))&CMI_MASK)];
						break;
						
						default:
						break;
					}
				}
				message_info[i].do_func(message_info->data_pars);
			}
		}
	}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
