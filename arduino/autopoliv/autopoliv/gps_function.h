void nmea_parser(unsigned char in_byte);
float parse_float_from_sd(unsigned char *buf,int buf_counter);
int parse_int_from_sd(unsigned char *buf,int buf_counter);

struct  {
		int	Time_h;
		int	Time_m;
		int	Time_s;
    int year;
    int month;
    int day;
		float latitude_l;
		signed int latitude_h;
		float longitude_l;
		signed int longitude_h;

    int	gprmc_valid=0;
		
		double latitude;
		double longitude;
		
		int fix;
		int NOS;
		float HDOP;
		float Altitude;
		float Height;
		int gpgga_valid=0;

		float truetrack;
		float	magntrack;
		float ground_speed;
		int	gpvtg_valid=0;
		
		unsigned int sat_in_vie;
		unsigned int sat_snr;
		
		unsigned int gpgsv_siv;
		unsigned int	gpgsv_isnr;
		int gpgsv_valid=0;
		
		unsigned int glgsv_siv;
		unsigned int	glgsv_isnr;
		int glgsv_valid=0;
		
	} gnss_cordinate,gnss_cordinate_valid;
///////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////
void nmea_parser_converter(unsigned char* buf,unsigned char pointer){
	nmea_parser(buf[pointer]);
}
///////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////
void nmea_parser(unsigned char in_byte){
	static int	comma_counter;
	static unsigned	char	nmea_buf[32];
	static unsigned int	buf_counter;
	static int	GPVTG_flag,GPGGA_flag,GPGSV_flag,GLGSV_flag,GPRMC_flag;

	if(in_byte=='$' || buf_counter>=32){
		buf_counter=0;
		comma_counter=0;
		GPVTG_flag=0;
		GPGGA_flag=0;
		GPGSV_flag=0;
		GLGSV_flag=0;
    GPRMC_flag=0;
	}else{
		if(in_byte==','){
			if(comma_counter==0){
				if(	(nmea_buf[0]=='G' && nmea_buf[1]=='N' && nmea_buf[2]=='G' && nmea_buf[3]=='G' && nmea_buf[4]=='A') ||
					(nmea_buf[0]=='G' && nmea_buf[1]=='P' && nmea_buf[2]=='G' && nmea_buf[3]=='G' && nmea_buf[4]=='A')	){
					GPGGA_flag=1;
					GPVTG_flag=0;
					GPGSV_flag=0;
					GLGSV_flag=0;
          GPRMC_flag=0;
					gnss_cordinate.gpgga_valid=0;
					gnss_cordinate.fix=0;
					
					gnss_cordinate.sat_in_vie=gnss_cordinate.glgsv_siv+gnss_cordinate.gpgsv_siv;
					gnss_cordinate.sat_snr=(gnss_cordinate.gpgsv_isnr+gnss_cordinate.glgsv_isnr)/8;
					gnss_cordinate.glgsv_isnr=0;
					gnss_cordinate.gpgsv_isnr=0;
				}
				if(	(nmea_buf[0]=='G' && nmea_buf[1]=='N' && nmea_buf[2]=='V' && nmea_buf[3]=='T' && nmea_buf[4]=='G') ||
					(nmea_buf[0]=='G' && nmea_buf[1]=='P' && nmea_buf[2]=='V' && nmea_buf[3]=='T' && nmea_buf[4]=='G')	){
					GPVTG_flag=1;
					GPGGA_flag=0;
					GPGSV_flag=0;
					GLGSV_flag=0;
          GPRMC_flag=0;
					gnss_cordinate.gpvtg_valid=0;
					gnss_cordinate.truetrack=0.0f;
					gnss_cordinate.ground_speed=0.0f;
				}
				if(nmea_buf[0]=='G' && nmea_buf[1]=='P' && nmea_buf[2]=='G' && nmea_buf[3]=='S' && nmea_buf[4]=='V'){
					GPGSV_flag=1;
					GPVTG_flag=0;
					GPGGA_flag=0;
					GLGSV_flag=0;
          GPRMC_flag=0;
				}
				if(nmea_buf[0]=='G' && nmea_buf[1]=='L' && nmea_buf[2]=='G' && nmea_buf[3]=='S' && nmea_buf[4]=='V'){
					GLGSV_flag=1;
					GPVTG_flag=0;
					GPGGA_flag=0;
					GPGSV_flag=0;
          GPRMC_flag=0;
				}
        if(nmea_buf[0]=='G' && nmea_buf[1]=='P' && nmea_buf[2]=='R' && nmea_buf[3]=='M' && nmea_buf[4]=='C'){
          GPRMC_flag=1;
          GLGSV_flag=0;
					GPVTG_flag=0;
					GPGGA_flag=0;
					GPGSV_flag=0;
				}
			}else{
        //$GPRMC,161946.00,A,5620.52502,N,03030.98191,E,0.006,,270423,,,A*72
        if(GPRMC_flag==1){//
					switch(comma_counter){
						case 2://Message number
							if(buf_counter>0){
								if(nmea_buf[0]=='A'){
                  gnss_cordinate.gprmc_valid=1;
								}else{
                  gnss_cordinate.gprmc_valid=0;
                }
							}else{
								gnss_cordinate.gprmc_valid=0;
							}
						break;
            case 9://Message number
              gnss_cordinate.year= parse_int_from_sd(&nmea_buf[4],2);
              gnss_cordinate.month=parse_int_from_sd(&nmea_buf[2],2);
              gnss_cordinate.day=  parse_int_from_sd(nmea_buf,2);
              GPRMC_flag=0;
            break;
						default:
						break;
					}					
				}
        ///////////////////////////
        ///////////////////////////
				if(GLGSV_flag==1){//Sattelite GLO in view
					switch(comma_counter){
						case 2://Message number
							if(buf_counter>0){
								if(parse_int_from_sd(nmea_buf,buf_counter)==1){
									//gnss_cordinate.glgsv_siv=0;
									//gnss_cordinate.glgsv_isnr=0;
								}
							}else{
								//gnss_cordinate.glgsv_siv=0;
								//gnss_cordinate.glgsv_isnr=0;
							}
						break;
						case 3://
							if(buf_counter>0){
								gnss_cordinate.glgsv_siv=parse_int_from_sd(nmea_buf,buf_counter);
							}
						break;
						case 7:
						case 11:
						case 15:
						case 19:
							if(buf_counter>0){
								gnss_cordinate.glgsv_isnr=gnss_cordinate.glgsv_isnr+parse_int_from_sd(nmea_buf,buf_counter);
							}
						break;
						default:
						break;
					}					
				}
				///////////////
				///////////////
				if(GPGSV_flag==1){//Sattelite GPS in view
					switch(comma_counter){
						case 2://Message number
							if(buf_counter>0){
								if(parse_int_from_sd(nmea_buf,buf_counter)==1){
									//gnss_cordinate.gpgsv_siv=0;
									//gnss_cordinate.gpgsv_isnr=0;
								}
							}else{
								//gnss_cordinate.gpgsv_siv=0;
								//gnss_cordinate.gpgsv_isnr=0;
							}
						break;
						case 3://
							if(buf_counter>0){
								gnss_cordinate.gpgsv_siv=parse_int_from_sd(nmea_buf,buf_counter);
							}
						break;
						case 7:
						case 11:
						case 15:
						case 19:
							if(buf_counter>0){
								gnss_cordinate.gpgsv_isnr=gnss_cordinate.gpgsv_isnr+parse_int_from_sd(nmea_buf,buf_counter);
							}
						break;
						default:
						break;
					}					
				}
				///////////////
				///////////////
				if(GPVTG_flag==1){//Speed and Track
					switch(comma_counter){
						case 1://Track made good
							if(buf_counter>0){
								gnss_cordinate.truetrack=parse_float_from_sd(nmea_buf,buf_counter);
							}
						break;
						case 2://T
							if(nmea_buf[0]!='T'){
								//GPVTG_flag=0;
							}
						break;
						case 7://Speed
							if(buf_counter>0){
								gnss_cordinate.ground_speed=parse_float_from_sd(nmea_buf,buf_counter);
							}
						break;
						case 8://K
							//if(nmea_buf[0]=='K'){
								GPVTG_flag=0;
								gnss_cordinate.gpvtg_valid=1;
							//}
						break;
						default:
						break;
					}
				}
				///////////////
				///////////////
				if(GPGGA_flag==1){//Coordinate and state
					switch(comma_counter){
						case 1://Time
							if(buf_counter==9){
								gnss_cordinate.Time_h=(nmea_buf[0]-'0')*10+(nmea_buf[1]-'0');
								gnss_cordinate.Time_m=(nmea_buf[2]-'0')*10+(nmea_buf[3]-'0');
								gnss_cordinate.Time_s=(nmea_buf[4]-'0')*10+(nmea_buf[5]-'0');
							}else{
								GPGGA_flag=0;
							}
						break;						
						case 2://Latitude
							if(buf_counter==10 && nmea_buf[4]=='.'){
								gnss_cordinate.latitude=(double)(nmea_buf[5]-'0');
								gnss_cordinate.latitude=gnss_cordinate.latitude*10+(double)(nmea_buf[6]-'0');
								gnss_cordinate.latitude=gnss_cordinate.latitude*10+(double)(nmea_buf[7]-'0');
								gnss_cordinate.latitude=gnss_cordinate.latitude*10+(double)(nmea_buf[8]-'0');
								gnss_cordinate.latitude=gnss_cordinate.latitude*10+(double)(nmea_buf[9]-'0');//!!!

								gnss_cordinate.latitude=gnss_cordinate.latitude/100000;
								gnss_cordinate.latitude=gnss_cordinate.latitude+(double)(nmea_buf[2]-'0')*10+(double)(nmea_buf[3]-'0');
								gnss_cordinate.latitude=gnss_cordinate.latitude/60;
								gnss_cordinate.latitude+=(double)(nmea_buf[0]-'0')*10+(double)(nmea_buf[1]-'0');
							}else{
								//GPGGA_flag=0;
							}
						break;
						case 3://N/S						
							if(nmea_buf[0]!='N'){
								gnss_cordinate.latitude=gnss_cordinate.latitude*(-1);
							}
						break;
						case 4://Longitude
							if(buf_counter==11 && nmea_buf[5]=='.'){							
								gnss_cordinate.longitude=(double)(nmea_buf[6]-'0');
								gnss_cordinate.longitude=gnss_cordinate.longitude*10+(double)(nmea_buf[7]-'0');
								gnss_cordinate.longitude=gnss_cordinate.longitude*10+(double)(nmea_buf[8]-'0');
								gnss_cordinate.longitude=gnss_cordinate.longitude*10+(double)(nmea_buf[9]-'0');
								gnss_cordinate.longitude=gnss_cordinate.longitude*10+(double)(nmea_buf[10]-'0');//!!!
								
								gnss_cordinate.longitude=gnss_cordinate.longitude/100000;
								gnss_cordinate.longitude=gnss_cordinate.longitude+(double)(nmea_buf[3]-'0')*10+(double)(nmea_buf[4]-'0');
								gnss_cordinate.longitude=gnss_cordinate.longitude/60;
								gnss_cordinate.longitude+=(double)(nmea_buf[0]-'0')*100+(double)(nmea_buf[1]-'0')*10+(double)(nmea_buf[2]-'0');
							}else{
								//GPGGA_flag=0;
							}
						break;		
						case 5://W/E
							if(nmea_buf[0]!='E'){
								gnss_cordinate.longitude=gnss_cordinate.longitude*(-1);
							}
						break;
						case 6://Fix Quality
							if(nmea_buf[0]!='0' && buf_counter>0){
								gnss_cordinate.fix=1;
							}else{
								gnss_cordinate.fix=0;
							}
						break;
						case 7://NOS
							if(buf_counter>0){
								gnss_cordinate.NOS=parse_int_from_sd(nmea_buf,buf_counter);
							}else{
								gnss_cordinate.NOS=0;
							}
						break;
						case 8:
							if(buf_counter>0){
								gnss_cordinate.HDOP=parse_float_from_sd(nmea_buf,buf_counter);
							}else{
								gnss_cordinate.HDOP=99.9;
							}
						break;
						case 9:
							if(buf_counter>0){
								gnss_cordinate.Altitude=parse_float_from_sd(nmea_buf,buf_counter);
							}else{
								gnss_cordinate.Altitude=0;
							}
						break;
						case 11:
							if(buf_counter>0){
								gnss_cordinate.Height=parse_float_from_sd(nmea_buf,buf_counter);
							}else{
								gnss_cordinate.Height=0;
							}
						break;
						case 12:
								gnss_cordinate.gpgga_valid=1;
						break;							
						default:
						break;
					}
				}
			}
			buf_counter=0;
			comma_counter++;
		}else{
			nmea_buf[buf_counter]=in_byte;
			buf_counter++;
		}		
	}	
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
double parse_double_from_sd(unsigned char *buf,int buf_counter){//proverka na otricacelnoe
	double parsedata=0.0f;
	double temp=0.0f;
	int i=0;
	if(buf[0]=='-'){
		i++;
	}
	for(;i<buf_counter;i++){
		if(buf[i]=='.'){
			break;
		}
		parsedata=parsedata*10+(float)(buf[i]-'0');
	}
	for(buf_counter--;i<buf_counter;buf_counter--){
		temp+=(float)(buf[buf_counter]-'0');
		temp=(float)temp/10;
	}
	parsedata+=temp;
	if(buf[0]=='-'){
		parsedata=parsedata*(-1);
	}
	return parsedata;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
float parse_float_from_sd(unsigned char *buf,int buf_counter){//proverka na otricacelnoe
	float parsedata=0.0f;
	float temp=0.0f;
	int i=0;
	if(buf[0]=='-'){
		i++;
	}
	for(;i<buf_counter;i++){
		if(buf[i]=='.'){
			break;
		}
		parsedata=parsedata*10+(double)(buf[i]-'0');
	}
	for(buf_counter--;i<buf_counter;buf_counter--){
		temp+=(double)(buf[buf_counter]-'0');
		temp=(double)temp/10;
	}
	parsedata+=temp;
	if(buf[0]=='-'){
		parsedata=parsedata*(-1);
	}
	return parsedata;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int parse_int_from_sd(unsigned char *buf,int buf_counter){//proverka na otricacelnoe
	int parsedata=0;
	int i=0;
	if(buf[0]=='-'){
		i++;
	}else{
		if(buf[0]=='0'){
			buf[0]='0';
		}
	}
	for(;i<buf_counter;i++){
		parsedata=parsedata*10+(float)(buf[i]-'0');//!!!(int)
	}
	if(buf[0]=='-'){
		parsedata=parsedata*(-1);
	}
	return parsedata;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
