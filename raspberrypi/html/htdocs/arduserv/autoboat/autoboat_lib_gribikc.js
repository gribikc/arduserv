'use strict';
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function float_from_byte_arr_gr(buf){
	var sig=0;
	var por=0;
	var man=0;
	
	if((buf&0x80000000)){//Знак
		var sig=-1;
	}else{
		var sig=1;
	}
	
	por=((buf>>23)&0xFF);//Порядок
	
	if(por!=0){//Мантисса
		man=((buf& 0x7FFFFF)|0x800000);
	}else{
		man=((buf&0x7FFFFF)<<1);
	}
	
	var res=sig*(man*Math.pow(2,(-23)))*(Math.pow(2,(por-127)));
	return res;
	
	//document.getElementById("debug").innerHTML+=sig+"<br>";
	//document.getElementById("debug").innerHTML+=por+"<br>";
	//document.getElementById("debug").innerHTML+=man+"<br>";
	//document.getElementById("debug").innerHTML+=res+"<br>";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//autoboat
	class autoboat_gr{
		//Инициализация
		constructor(){
			this.parser_data_array=new Array();
			this.start_point=0;
			this.end_point=0;

			this.MESSAGE_LEN=95;
			this.HEADER=[0xAA,0xBB];
			this.FOOTER=[0xCC,0xDD];
			
			this.telemetry_message={
				hour:["Час",0,6,0],						//-57                       ///////////hour:["Час",0,57,0],				//-57
				min:["Мин",0,7,0],						//-56                       ///////////min:["Мин",0,56,0],					//-56
				sec:["Сек",0,8,0],						//-55                       ///////////sec:["Сек",0,55,0],					//-55
				NOS:["NOS",0,9,0],						//к-во используемых спутников//-54                       ///////////NOS:["NOS",0,54,0],					//-54
				SIV:["SIV",0,10,0],						//к-во видимых спутников//-53                       ///////////SIV:["SIV",0,53,0],					//-53
				SSNR:["SSNR",0,11,0],					//сумма сигналов спутников//-52                       ///////////SSNR:["SSNR",0,52,0],				//-52
				HDOP:["HDOP",1,15,0],					//-51...-48(float)          ///////////HDOP:["HDOP",1,51,0],				//-51...-48(float)
				altitude:["Высота",1,19,0],				//-47...-44(float)          ///////////altitude:["Высота",1,47,0],			//-47...-44(float)
				height:["Высота",1,23,0],				//-43...-40(float)          ///////////height:["Высота",1,43,0],			//-43...-40(float)
				latitude:["Широта",2,29,0],				//-37(byte)-37...-34(float) ///////////latitude:["Широта",2,37,0],			//-37(byte)-37...-34(float)
				longitude:["Долгота",2,34,0],			//-33(byte)-32...-29(float) ///////////longitude:["Долгота",2,33,0],		//-33(byte)-32...-29(float)
				direction:["Направление",1,38,0],		//истенный курс//-28...-25(float)      ///////////direction:["Направление",1,28,0],		//-28...-25(float)
				compass:["Компас",1,42,0],				//компас//-24...-21(float)          ///////////compass:["Компас",1,24,0],			//-24...-21(float)
				speed:["Скорость",1,46,0],				//-20...-17(float)          ///////////speed:["Скорость",1,20,0],			//-20...-17(float)
				pilot_error:["ERR",1,50,0],				//ошибка навигации//-16...-13(float)              ///////////pilot_error:["ERR",1,16,0],		//-16...-13(float)
				pid:["PID",1,54,0],						//Выход регулятора
				tiller_position_cp:["Положение текущие",1,58,0],	//положение румпеля//-12...-9(float)       ///////////tiller_position:["Положение",1,12,0]	//-12...-9(float)
				tiller_position:["Положение требуемое",1,62,0],	//положение румпеля
				point_distance:["Расстояние до точки",1,66,0],
				current_point:["Текущая точка маршрута",1,70,0]
			}
		}
		parser_data(stream){
			this.end_point=stream.length;
			if(this.start_point>=this.end_point){
				this.start_point=0;
			}
			for(var i=this.start_point;i<this.end_point;i++){
				//console.log(stream.charCodeAt(i)&0xFF);
				if(this.start_point>=96){
					if(	(stream.charCodeAt(i   )&0xFF)==0xDD && (stream.charCodeAt(i-1 )&0xFF)==0xCC && 
						(stream.charCodeAt(i-this.MESSAGE_LEN+1)&0xFF)==0xBB && (stream.charCodeAt(i-this.MESSAGE_LEN)&0xFF)==0xAA ){//-62//-63							//console.log(stream.charCodeAt(i-28)&0xFF);
						if((stream.charCodeAt(i-93)&0xFF)==0x03){//61
							this.telemetry_parser(stream,i);
						}
					}
				}
			}
			this.start_point=this.end_point;
		}
		//////////
		telemetry_parser(stream,end_byte){
			//console.log(stream.charCodeAt(end_byte-60)&0xFF);
			//console.log(stream.charCodeAt(end_byte-55)&0xFF);
			var tmp_float_from_byte=0;
			document.getElementById("autobot_state").innerHTML="";
			for(var i in this.telemetry_message){
				this.telemetry_message[i][3]=0;
				if(this.telemetry_message[i][1]==0){//char
					this.telemetry_message[i][3]=stream.charCodeAt(end_byte+this.telemetry_message[i][2]-this.MESSAGE_LEN)&0xFF;
				}else if(this.telemetry_message[i][1]==1){//float
					//float_from_byte_arr_gr(buf)
					tmp_float_from_byte=stream.charCodeAt(end_byte+this.telemetry_message[i][2]-this.MESSAGE_LEN-0)&0xFF;
					tmp_float_from_byte=tmp_float_from_byte<<8;
					tmp_float_from_byte+=stream.charCodeAt(end_byte+this.telemetry_message[i][2]-this.MESSAGE_LEN-1)&0xFF;
					tmp_float_from_byte=tmp_float_from_byte<<8;
					tmp_float_from_byte+=stream.charCodeAt(end_byte+this.telemetry_message[i][2]-this.MESSAGE_LEN-2)&0xFF;
					tmp_float_from_byte=tmp_float_from_byte<<8;
					tmp_float_from_byte+=stream.charCodeAt(end_byte+this.telemetry_message[i][2]-this.MESSAGE_LEN-3)&0xFF;
					//tmp_float_from_byte=tmp_float_from_byte<<8;
					
					this.telemetry_message[i][3]=float_from_byte_arr_gr(tmp_float_from_byte);//tmp_float_from_byte;
				}else if(this.telemetry_message[i][1]==2){
					//float_from_byte_arr_gr(buf)
					tmp_float_from_byte=stream.charCodeAt(end_byte+this.telemetry_message[i][2]-this.MESSAGE_LEN-0)&0xFF;
					tmp_float_from_byte=tmp_float_from_byte<<8;
					tmp_float_from_byte+=stream.charCodeAt(end_byte+this.telemetry_message[i][2]-this.MESSAGE_LEN-1)&0xFF;
					tmp_float_from_byte=tmp_float_from_byte<<8;
					tmp_float_from_byte+=stream.charCodeAt(end_byte+this.telemetry_message[i][2]-this.MESSAGE_LEN-2)&0xFF;
					tmp_float_from_byte=tmp_float_from_byte<<8;
					tmp_float_from_byte+=stream.charCodeAt(end_byte+this.telemetry_message[i][2]-this.MESSAGE_LEN-3)&0xFF;
					//tmp_float_from_byte=tmp_float_from_byte<<8;
					
					this.telemetry_message[i][3]=float_from_byte_arr_gr(tmp_float_from_byte);//+stream.charCodeAt(end_byte+this.telemetry_message[i][2]-this.MESSAGE_LEN-4)&0xFF
				}else{
					this.telemetry_message[i][3]="undf...";
				}
				document.getElementById("autobot_state").innerHTML+=this.telemetry_message[i][0]+": "+this.telemetry_message[i][3]+"<br>";
				
				//!!!yandex_map_add_point_gr(this.telemetry_message['longitude'][3],this.telemetry_message['latitude'][3],10.3);
				if(i=='longitude'){
					yandex_map_add_point_gr(this.telemetry_message['latitude'][3],this.telemetry_message['longitude'][3],10.3);
					//console.log(this.telemetry_message['longitude'][3]);
					if(auto_boat_config['auto_move_map_to_boat']){
						yandex_map_center_map_to(this.telemetry_message['latitude'][3],this.telemetry_message['longitude'][3],0);
					}
				}
			}
			//console.log(this.telemetry_message);
			var k=3.1234567890123456789;
			//console.log(readBytes(k,1));
		}		
		//////////		
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
