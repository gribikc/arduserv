'use strict';
//PARSERing
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PARENT
class parser_parent_gr{
	constructor(hub,parameter) {
		this.buf="";
		this.parser_data_array=new Array();
		this.hub_handler=hub;
		this.parameter=parameter;
		if(parameter){	
			this.is_collected=('collected' in this.parameter) ? (this.parameter.collected ? 1:0) : 0;
		}else{
			this.is_collected=0;
		}
		this.buf_start_point=0;
		this.buf_end_point=0;
		this.parser_begin_point=0;
		this.parser_begin_point_valid=0;
		this.cut_point=0;
	}
	
	parser(){
		//переопределяется в наследнике
	}
	
	parser_data(stream){
		//!!!this.hub_handler.parser_data(this.parser_data_array);
		//
		
		this.buf+=stream;
		this.buf_end_point=this.buf.length;
		this.cut_point=0;
		if(this.buf_start_point>=this.buf_end_point){//!!!>=???//
			this.buf_start_point=0;
		}
		
		this.parser();//!!!for(var i=this.buf_start_point;i<this.buf_end_point;i++){
		
		if(this.is_collected){
			//COLLECT
			this.buf.substring(this.cut_point);
			this.buf_start_point=this.buf.length;
		}else{	
			//NO COLLECT
			this.buf_start_point=0;//this.buf.length;
			this.buf="";
		}
	}
	find(i=0){
		if(this.parser_data_array.length>0 || Object.keys(this.parser_data_array).length>0){
			this.hub_handler.parser_data(this.parser_data_array);					
			this.parser_data_array=new Array();
		}
		this.cut_point=i;
	}
	
	error_event(message){
		this.hub_handler.error_event(message);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//JSON
class nt_json_gr extends parser_parent_gr{
	parser(){
		//console.log(this.buf);
		try {
			this.parser_data_array=JSON.parse( this.buf );
		}catch (exception) {
			//console.log('ERROR: ' + exception);
		}
		/*if(this.parser_data_array.length>0 || Object.keys(this.parser_data_array).length>0){
			this.hub_handler.parser_data(this.parser_data_array);					
			this.parser_data_array=new Array();
		}*/
		find();
	}	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//JSON STREAM
class nt_json_stream_gr extends parser_parent_gr{
	parser(){
		for(var i=this.buf_start_point;i<this.buf_end_point;i++){
			if(this.buf_start_point>=31 || i>=31){
				if(	(this.buf.charAt(i-0)) 	==	"{" &&
					(this.buf.charAt(i-1)) 	==	":" &&
					(this.buf.charAt(i-2)) 	==	"n" &&
					(this.buf.charAt(i-3)) 	==	"o" &&
					(this.buf.charAt(i-4)) 	==	"s" &&
					(this.buf.charAt(i-5)) 	==	"j" &&
					(this.buf.charAt(i-6)) 	==	"t" &&
					(this.buf.charAt(i-7)) 	==	"r" &&
					(this.buf.charAt(i-8)) 	==	"a" &&
					(this.buf.charAt(i-9)) 	==	"t" &&
					(this.buf.charAt(i-10)) 	==	"s" &&
					(this.buf.charAt(i-11)) 	==	"d" &&
					(this.buf.charAt(i-12)) 	==	"x"){//xdstartjson:{
						this.parser_begin_point=i;
						this.parser_begin_point_valid=1;
				}
				if(	(this.buf.charAt(i-0)) 	==	"n" &&
					(this.buf.charAt(i-1)) 	==	"o" &&
					(this.buf.charAt(i-2)) 	==	"s" &&
					(this.buf.charAt(i-3)) 	==	"j" &&
					(this.buf.charAt(i-4)) 	==	"p" &&
					(this.buf.charAt(i-5)) 	==	"o" &&
					(this.buf.charAt(i-6)) 	==	"t" &&
					(this.buf.charAt(i-7)) 	==	"s" &&
					(this.buf.charAt(i-8)) 	==	"d" &&
					(this.buf.charAt(i-9)) 	==	"x" &&
					(this.buf.charAt(i-10)) 	==	":" &&
					(this.buf.charAt(i-11)) 	==	"}"){//}:xdstopjson
						if(this.parser_begin_point_valid==1){
							//this.cut_point=i;
							try {
								this.parser_data_array=JSON.parse( this.buf.slice(this.parser_begin_point, i-10) );
							}catch (exception) {
								//console.log('ERROR: ' + exception);
							}
							/*if(this.parser_data_array.length>0 || Object.keys(this.parser_data_array).length>0){
								this.hub_handler.parser_data(this.parser_data_array);					
								this.parser_data_array=new Array();
							}*/
							find(i);
							//console.log(this.parser_data_array);
						}
						this.parser_begin_point_valid=0;
				}
			}
		}
	}	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//RAW
class nt_raw_parser_gr extends parser_parent_gr{
	parser(){
		for(var i=this.buf_start_point;i<this.buf_end_point;i++){
			if(this.end_point>=(this.parameter.db_matrix[0]['message_len'])){	//if(this.start_point>=(this.db_matrix[0]['message_len']+1)){
				if(	(this.buf.charCodeAt(i   )&0xFF)==this.parameter.db_matrix[0]['footer'][1] && 
					(this.buf.charCodeAt(i-1 )&0xFF)==this.parameter.db_matrix[0]['footer'][0] && 
					(this.buf.charCodeAt(i-this.parameter.db_matrix[0]['message_len']+1)&0xFF)==this.parameter.db_matrix[0]['header'][1] && 
					(this.buf.charCodeAt(i-this.parameter.db_matrix[0]['message_len'])&0xFF)==this.parameter.db_matrix[0]['header'][0] ){	//-62//-63							//console.log(stream.charCodeAt(i-28)&0xFF);
					if((this.buf.charCodeAt(i-93)&0xFF)==0x03){	//61
						this.message_parser(this.buf,i,0);
					}
				}
			}
		}
	}
	message_parser(stream,end_byte,m_id){
		var tmp_float_from_byte=0;
		for(var i in this.parameter.db_matrix[m_id]['message']){
			this.parameter.db_matrix[m_id]['message'][i][3]=0;//обнуляем матрицу
			if(this.parameter.db_matrix[m_id]['message'][i][1]==0){//char
				this.parameter.db_matrix[m_id]['message'][i][3]=stream.charCodeAt(end_byte+this.parameter.db_matrix[m_id]['message'][i][2]-this.parameter.db_matrix[m_id]['message_len'])&0xFF;
			}else if(this.parameter.db_matrix[m_id]['message'][i][1]==1){//float
				//float_from_byte_arr_gr(buf)
				tmp_float_from_byte=stream.charCodeAt(end_byte+this.parameter.db_matrix[m_id]['message'][i][2]-this.parameter.db_matrix[m_id]['message_len']-0)&0xFF;
				tmp_float_from_byte=tmp_float_from_byte<<8;
				tmp_float_from_byte+=stream.charCodeAt(end_byte+this.parameter.db_matrix[m_id]['message'][i][2]-this.parameter.db_matrix[m_id]['message_len']-1)&0xFF;
				tmp_float_from_byte=tmp_float_from_byte<<8;
				tmp_float_from_byte+=stream.charCodeAt(end_byte+this.parameter.db_matrix[m_id]['message'][i][2]-this.parameter.db_matrix[m_id]['message_len']-2)&0xFF;
				tmp_float_from_byte=tmp_float_from_byte<<8;
				tmp_float_from_byte+=stream.charCodeAt(end_byte+this.parameter.db_matrix[m_id]['message'][i][2]-this.parameter.db_matrix[m_id]['message_len']-3)&0xFF;
				//tmp_float_from_byte=tmp_float_from_byte<<8;
				
				this.parameter.db_matrix[m_id]['message'][i][3]=float_from_byte_arr_gr(tmp_float_from_byte);//tmp_float_from_byte;
			}else if(this.parameter.db_matrix[m_id]['message'][i][1]==2){//byte.float
				//float_from_byte_arr_gr(buf)
				tmp_float_from_byte=stream.charCodeAt(end_byte+this.parameter.db_matrix[m_id]['message'][i][2]-this.parameter.db_matrix[m_id]['message_len']-0)&0xFF;
				tmp_float_from_byte=tmp_float_from_byte<<8;
				tmp_float_from_byte+=stream.charCodeAt(end_byte+this.parameter.db_matrix[m_id]['message'][i][2]-this.parameter.db_matrix[m_id]['message_len']-1)&0xFF;
				tmp_float_from_byte=tmp_float_from_byte<<8;
				tmp_float_from_byte+=stream.charCodeAt(end_byte+this.parameter.db_matrix[m_id]['message'][i][2]-this.parameter.db_matrix[m_id]['message_len']-2)&0xFF;
				tmp_float_from_byte=tmp_float_from_byte<<8;
				tmp_float_from_byte+=stream.charCodeAt(end_byte+this.parameter.db_matrix[m_id]['message'][i][2]-this.parameter.db_matrix[m_id]['message_len']-3)&0xFF;
				//tmp_float_from_byte=tmp_float_from_byte<<8;
				
				this.parameter.db_matrix[m_id]['message'][i][3]=float_from_byte_arr_gr(tmp_float_from_byte);//+stream.charCodeAt(end_byte+this.parameter.db_matrix[i][2]-this.MESSAGE_LEN-4)&0xFF
			}else if(this.parameter.db_matrix[m_id]['message'][i][1]==3){//int
				tmp_float_from_byte=stream.charCodeAt(end_byte+this.parameter.db_matrix[m_id]['message'][i][2]-this.parameter.db_matrix[m_id]['message_len']-0)&0xFF;
				tmp_float_from_byte=tmp_float_from_byte<<8;
				tmp_float_from_byte+=stream.charCodeAt(end_byte+this.parameter.db_matrix[m_id]['message'][i][2]-this.parameter.db_matrix[m_id]['message_len']-1)&0xFF;
				tmp_float_from_byte=tmp_float_from_byte<<8;
				tmp_float_from_byte+=stream.charCodeAt(end_byte+this.parameter.db_matrix[m_id]['message'][i][2]-this.parameter.db_matrix[m_id]['message_len']-2)&0xFF;
				tmp_float_from_byte=tmp_float_from_byte<<8;
				tmp_float_from_byte+=stream.charCodeAt(end_byte+this.parameter.db_matrix[m_id]['message'][i][2]-this.parameter.db_matrix[m_id]['message_len']-3)&0xFF;
				//tmp_float_from_byte=tmp_float_from_byte<<8;
				
				this.parameter.db_matrix[m_id]['message'][i][3]=tmp_float_from_byte;
			}else{
				this.parameter.db_matrix[m_id]['message'][i][3]="undf...";
			}

			this.hub_handler.parser_data(this.parameter.db_matrix[m_id]['message']);
		}				
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//BLANCK
	class array_data_to_log_gr extends parser_parent_gr{
		parser(){
			console.log(buf.toString());
		}

	}

	class array_data_to_to_to_gr extends parser_parent_gr{
		parser(){
			console.log(buf.toString());
		}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//SNMP!!!
	class snmp_parser_gr {//!!!CONTAINER!!!
		//Инициализация
			constructor(hub) {
				this.parser_data_array=new Array();
				this.hub_handler=hub;
			}
		//Парсинг
			parser_data(stream){
					//console.log(stream);
					/*var arr=new Uint8Array(stream.length);
					for(var i=0;i<stream.length;i++){
						arr[i]=stream.charCodeAt(i);
					}
					console.log(arr);
					document.getElementById('test_data_0').innerHTML=stream;*/
					
					var arr=this.snmp_tree(stream,0);
					if(arr.length>0 && arr[0][2][3][0][1]['data']!=undefined && arr[0][2][3][0][1]['data'].length>0){
						this.hub_handler.parser_data(arr[0][2][3][0][1]['data']);
					}else{	
						//console.log("SNMP REQUEST EMPTY OR NOT VALID");
						//console.log(stream);
						this.hub_handler.error_event("SNMP REQUEST EMPTY OR NOT VALID");
					}
			}
			///////////////////////////////////////////////////////////////
			//////////////////////////////////////////
			/////////////////////
			error_event(message){
				this.hub_handler.error_event(message);
			}
			///////////////////////////////////////////////////////////////
			//////////////////////////////////////////
			/////////////////////
				snmp_tree(arr,index){
					var k = {start: index,l_size:0};
					var array;
					var array_ret=[];
					for(var i=0;i<arr.length;i++){
						array=this.get_data(arr,k);//0//5
						if(array['type']>0x10){
							array=this.snmp_tree(array['data'],0);
						}
						array_ret.push(array);
						i=k.start;
					}
					return array_ret;
				}			
				/////////////////////
				get_data(arr,index){
					var k=index.start;
					var data=new Array();
					//Integer(0x02),String(0x04),Object ID(0x06),varBind(0x30),SNMP RESPONSE(0xA2)
						data['type']=arr.charCodeAt(k)&255;
						k++;
					//LENGTH
						data['len']=0;
						if((arr.charCodeAt(k)&255)>127){
							var l_of_len=arr.charCodeAt(k)&(127);
							var len=0;
							index.l_size=l_of_len+1;
							k++;
							for(var i=0;i<l_of_len;i++){
								len*=256;
								len+=arr.charCodeAt(k)&255;
								k++;
							}
							data['len']=len;
						}else{
							data['len']=arr.charCodeAt(k)&255;
							k++;
						}
					//DATA
						data['data']=new Array();;
						for(var i=0;i<data['len'];i++){
							if(data['type']==0x04){
								data['data']+=arr.charAt(k);
							}else{
								//data['data']+=arr[k];
								//data['data']+=arr.charCodeAt(k);
								//data['data'][i]=arr.charCodeAt(k)&255;
								data['data']+=arr.charAt(k);
							}
							k++;
						}
					/////
					index.start=k;
					return data;
				}
			/////////////////////
			//////////////////////////////////////////
			///////////////////////////////////////////////////////////////
	}
	
	function snmp_query(oid,type,send_string){//1-input(get);0-output(set)
		//Therefore, the first two numbers of an SNMP OID are encoded as 43 or 0x2B, because (40*1)+3 = 43.
		//
		//Integer 			0x02 Sequence 			0x30
		//Octet String 		0x04 GetRequest PDU 	0xA0
		//Null 				0x05 GetResponse PDU 	0xA2
		//Object Identifier 0x06 SetRequest PDU 	0xA3
		
		var arr=[];
		arr[0]=0x30;//ASN.1 header
			arr[1]=0x00;//!!!XX;//L
				arr[2]=0x02;//T
					arr[3]=0x01;//L
					arr[4]=0x01;//Version
				arr[5]=0x04;//T
					arr[6]=0x06;//L
					arr[8]=0x75;//u
					arr[9]=0x62;//b
					arr[7]=0x70;//P
					arr[10]=0x6C;//l
					arr[11]=0x69;//i
					arr[12]=0x63;//c
				arr[13]=(type)?0xA0:0xA3;//SNMP GET/SET request//0xA0-GET//0xA3-SET//
					arr[14]=0x00;//!!!00;L
						arr[15]=0x02;//SNMP request ID
							arr[16]=0x01;//L
							arr[17]=0x01;//Version
						arr[18]=0x02;//SNMP error status
							arr[19]=0x01;//L
							arr[20]=0x00;//Version
						arr[21]=0x02;//SNMP index:
							arr[22]=0x01;//L
							arr[23]=0x00;//Version
						arr[24]=0x30;//varBind list
							arr[25]=0x00;//!!!XX;//L
							arr[26]=0x30;//varBind
								arr[27]=0x00;//!!!XX;//L
									arr[28]=0x06;//Object ID
										arr[29]=0x00;//!!!XX;//L
										arr[30]=0x2b;//
											var oid_arr=oid.split(".");
											var size_of_oid=1;
											for(var i=2;i<oid_arr.length;i++){
												var oid_decode=oid_arr[i];
												for(var j=4;j>=0;j--){
													var a=(oid_decode>>(7*j));
													oid_decode=oid_decode-a*(128<<(j-1)*7);
													if(a>0 && j>0){
														a^=0x80;
													}
													if(a>0 || j==0){
														arr.push(a);
														size_of_oid++;
													}
												}
											}

									arr.push(((type)?0x05:0x04));//varBind//(type)?0x05:0x04
									arr.push(((type)?0x00:send_string.length));//L
										if(type==0){
											for(var i=0;i<send_string.length;i++){
												arr.push(send_string.charCodeAt(i));
											}
										}

									arr[29]=size_of_oid;
									arr[27]=arr[29]+4+((type)?0x00:send_string.length);
									arr[25]=arr[27]+2;
									arr[14]=arr[27]+13;
									arr[1] =arr[14]+13;
		return arr;
	}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//NMEA!!!
	/*
	Класс принимает бесконечный поток данных,
	определяет начало сообщения согласно протоколу.
	Подсчитывает контрольную сумму.
	Передает в виде массива структурированные сообщения хабу...
	*/
	class nmea_parser_gr {
		//Инициализация
			constructor(hub) {
				this.parser_start_valid=0;				//установка при обнаружении $, сброс про обнаружении конца строки
				this.nmea_data;							//буфер для выдергивания сообщений
				this.parser_nmea_array=new Array();
				
				this.start_point=0;
				this.end_point=0;
				
				this.hub_handler=hub;
			}
		//Парсинг
			parser_data(stream){
				//console.log(stream);
				this.end_point=stream.length;
				if(this.start_point>=this.end_point){
					this.start_point=0;
				}
				for(var i=this.start_point;i<this.end_point;i++){	//обходим все поступившие данные
					if(stream.charAt(i)=='$'){			//Обнаружели начало
						this.parser_start_valid=1;
						this.nmea_data="$";				//очищаем буфер
					}else{
						this.nmea_data+=stream.charAt(i);
						if(stream.charCodeAt(i)==10 && this.parser_start_valid==1){//Обнаружели конец////(xhr.responseText.charCodeAt(i-4)=="*" && xhr.responseText.charCodeAt(i-1)==13 || xhr.responseText.charCodeAt(i)==10 && nmea_start_point_valid==1
							this.parser_start_valid=0;

							var nmea_array=this.nmea_data.split(",");				//парсинг NMEA
							var temp=nmea_array[nmea_array.length-1].split("*");	//выделяем контрольную сумму
							nmea_array[nmea_array.length-1]=temp[0];
							nmea_array[nmea_array.length]=temp[1];
							this.parser_nmea_array.push(nmea_array);//!!!
							//console.log(nmea_array);
						}
					}
				}
				this.start_point=this.end_point;
				if(this.parser_nmea_array.length>0 && 1){
					this.hub_handler.parser_data(this.parser_nmea_array);
					this.parser_nmea_array=new Array();
				}
			}
			error_event(message){
				this.hub_handler.error_event(message);
			}
		//Сброс данных
			clear_nmea_array(){
				this.parser_nmea_array=new Array();
			}
		//чуть

		//чуть
		
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

