'use strict';
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*function float_from_byte_arr_gr(buf){
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
}*/
//////////////////
/*function byte_arr_from_float_gr(buf){
	var float32	= new Float32Array(1);
	float32[0] 	= buf;
	var float32_ba = new Uint8Array(float32.buffer);
	//console.log(float32_ba);
	return float32_ba;
}*/
//var float32 = new Float32Array([1.2]);
//float32
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//autoboat
	class autoboat_gr{
		//var
		//BBAA0100020000000000000000000000000000000000000000CCDD
		//var upr_cmd = new Array();
		//upr_cmd.push(nav_start : new Uint8Array([0xBB,0xAA,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]) );
		//var uint8 = new Uint8Array([0xBB,0xAA,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
		//Инициализация
		constructor(){
			this.upr_cmd = new Array();
				//												0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x10 0x11 0x12 0x13 0x14 0x15 0x16 0x17 0x18 0x19 0x20 0x21 0x22 0x23 0x24 0x25 0x26
				//                                               -26  -25  -24  -23  -22  -21  -20  -19  -18  -17  -16  -15  -14  -13  -12  -11  -10   -9   -8   -7   -6   -5   -4   -3   -2   -1    0
				//												 HEADER  ,0x01, ID , CMD,---------------------------------------------DATA----------------------------------------,CRCL,CRCH,  FOOTER
				this.upr_cmd['nav_ap_stop']=		new Uint8Array([0xBB,0xAA,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);//!!!
				this.upr_cmd['nav_ap_start']=		new Uint8Array([0xBB,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				//this.upr_cmd['nav_nnm']=			new Uint8Array([0xBB,0xAA,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				this.upr_cmd['nav_ap_reset']=		new Uint8Array([0xBB,0xAA,0x01,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				//this.upr_cmd['nav_nnm']=			new Uint8Array([0xBB,0xAA,0x01,0x00,0xXX,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				this.upr_cmd['nav_apt_kompass']=	new Uint8Array([0xBB,0xAA,0x01,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				this.upr_cmd['nav_apt_point']=		new Uint8Array([0xBB,0xAA,0x01,0x00,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				this.upr_cmd['nav_apt_line']=		new Uint8Array([0xBB,0xAA,0x01,0x00,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				this.upr_cmd['nav_apt_circle']=		new Uint8Array([0xBB,0xAA,0x01,0x00,0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);

				this.upr_cmd['nav_set_pidparam']=	new Uint8Array([0xBB,0xAA,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				this.upr_cmd['nav_set_rumpel']=		new Uint8Array([0xBB,0xAA,0x01,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				this.upr_cmd['nav_set_track']=		new Uint8Array([0xBB,0xAA,0x01,0x01,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);

				this.upr_cmd['nav_send_point']=		new Uint8Array([0xBB,0xAA,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);

			
			this.parser_data_array=new Array();
			this.start_point=0;
			this.end_point=0;

			this.MESSAGE_LEN=95;
			this.HEADER=[0xAA,0xBB];
			this.FOOTER=[0xCC,0xDD];
			
			this.telemetry_message={
				hour:["Час",0,6,0],									//-57                       ///////////hour:["Час",0,57,0],				//-57
				min:["Мин",0,7,0],									//-56                       ///////////min:["Мин",0,56,0],					//-56
				sec:["Сек",0,8,0],									//-55                       ///////////sec:["Сек",0,55,0],					//-55
				NOS:["NOS",0,9,0],									//к-во используемых спутников//-54                       ///////////NOS:["NOS",0,54,0],					//-54
				SIV:["SIV",0,10,0],									//к-во видимых спутников//-53                       ///////////SIV:["SIV",0,53,0],					//-53
				SSNR:["SSNR",0,11,0],								//сумма сигналов спутников//-52                       ///////////SSNR:["SSNR",0,52,0],				//-52
				HDOP:["HDOP",1,15,0],								//-51...-48(float)          ///////////HDOP:["HDOP",1,51,0],				//-51...-48(float)
				altitude:["Высота",1,19,0],							//-47...-44(float)          ///////////altitude:["Высота",1,47,0],			//-47...-44(float)
				height:["Высота",1,23,0],							//-43...-40(float)          ///////////height:["Высота",1,43,0],			//-43...-40(float)
				latitude:["Широта",2,29,0],							//-37(byte)-37...-34(float) ///////////latitude:["Широта",2,37,0],			//-37(byte)-37...-34(float)
				longitude:["Долгота",2,34,0],						//-33(byte)-32...-29(float) ///////////longitude:["Долгота",2,33,0],		//-33(byte)-32...-29(float)
				direction:["Направление",1,38,0],					//истенный курс//-28...-25(float)      ///////////direction:["Направление",1,28,0],		//-28...-25(float)
				compass:["Компас",1,42,0],							//компас//-24...-21(float)          ///////////compass:["Компас",1,24,0],			//-24...-21(float)
				speed:["Скорость",1,46,0],							//-20...-17(float)          ///////////speed:["Скорость",1,20,0],			//-20...-17(float)
				pilot_error:["ERR",1,50,0],							//ошибка навигации//-16...-13(float)              ///////////pilot_error:["ERR",1,16,0],		//-16...-13(float)
				pid:["PID",1,54,0],									//Выход регулятора
				tiller_position_cp:["Положение текущие",3,58,0],	//int//положение румпеля//-12...-9(float)       ///////////tiller_position:["Положение",1,12,0]	//-12...-9(float)
				tiller_position:["Положение требуемое",3,62,0],		//int//положение румпеля
				point_distance:["Расстояние до точки",1,66,0],
				current_point:["Текущая точка маршрута",1,70,0]
			}
		}
		//////////
		parser_data(stream){
			console.log(stream);
			document.getElementById("autobot_state").innerHTML="";
			for(var i in stream){
				document.getElementById("autobot_state").innerHTML+=stream[i][0]+": "+stream[i][3]+"<br>";
				if(i=='longitude' && stream['NOS'][3]>4){
					yandex_map_add_point_gr(stream['latitude'][3],stream['longitude'][3],10.3);
					//console.log(stream['longitude'][3]);
					if(auto_boat_config['auto_move_map_to_boat']){
						yandex_map_center_map_to(stream['latitude'][3],stream['longitude'][3],0);
					}
				}
			}
			/*this.end_point=stream.length;
			if(this.start_point>=this.end_point){
				this.start_point=0;
			}
			for(var i=this.start_point;i<this.end_point;i++){
				//console.log(stream.charCodeAt(i)&0xFF);
				if(this.start_point>=(this.MESSAGE_LEN+1)){
					if(	(stream.charCodeAt(i   )&0xFF)==this.FOOTER[1] && 
						(stream.charCodeAt(i-1 )&0xFF)==this.FOOTER[0] && 
						(stream.charCodeAt(i-this.MESSAGE_LEN+1)&0xFF)==this.HEADER[1] && 
						(stream.charCodeAt(i-this.MESSAGE_LEN)&0xFF)==this.HEADER[0] ){//-62//-63							//console.log(stream.charCodeAt(i-28)&0xFF);
						if((stream.charCodeAt(i-93)&0xFF)==0x03){//61
							this.telemetry_parser(stream,i);
						}
					}
				}
			}
			this.start_point=this.end_point;*/
		}
		error_event(message){
				console.log(message+'autoboat_gr');
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
				}else if(this.telemetry_message[i][1]==3){
					tmp_float_from_byte=stream.charCodeAt(end_byte+this.telemetry_message[i][2]-this.MESSAGE_LEN-0)&0xFF;
					tmp_float_from_byte=tmp_float_from_byte<<8;
					tmp_float_from_byte+=stream.charCodeAt(end_byte+this.telemetry_message[i][2]-this.MESSAGE_LEN-1)&0xFF;
					tmp_float_from_byte=tmp_float_from_byte<<8;
					tmp_float_from_byte+=stream.charCodeAt(end_byte+this.telemetry_message[i][2]-this.MESSAGE_LEN-2)&0xFF;
					tmp_float_from_byte=tmp_float_from_byte<<8;
					tmp_float_from_byte+=stream.charCodeAt(end_byte+this.telemetry_message[i][2]-this.MESSAGE_LEN-3)&0xFF;
					//tmp_float_from_byte=tmp_float_from_byte<<8;
					
					this.telemetry_message[i][3]=tmp_float_from_byte;
				}else{
					this.telemetry_message[i][3]="undf...";
				}
				document.getElementById("autobot_state").innerHTML+=this.telemetry_message[i][0]+": "+this.telemetry_message[i][3]+"<br>";
				
				//!!!yandex_map_add_point_gr(this.telemetry_message['longitude'][3],this.telemetry_message['latitude'][3],10.3);
				if(i=='longitude' && this.telemetry_message['NOS'][3]>4){
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
		send_cmd(name,url,mode){
			//console.log(name);
			//console.log(url);
			//console.log(this.upr_cmd[name]);//[name]
			var send_data=new Uint8Array();
			var float_byte_array;
			switch(name){
				/////////
				//////////////////////
				case 'nav_set_rumpel':
					send_data=this.upr_cmd[name];
					var incr=document.getElementById(name+"_value_gr").value;
					if(mode=='left'){
						incr=incr*(-1);
					}
					float_byte_array=byte_arr_from_float_gr(incr);
					send_data[5]=float_byte_array[0];
					send_data[6]=float_byte_array[1];
					send_data[7]=float_byte_array[2];
					send_data[8]=float_byte_array[3];
				break
				/////
				/////////////////////
				case 'nav_set_track':
					send_data=this.upr_cmd[name];
					var incr=document.getElementById(name+"_value_gr").value;
					if(mode=='left'){
						incr=incr*(-1);
					}
					float_byte_array=byte_arr_from_float_gr(incr);
					send_data[5]=float_byte_array[0];
					send_data[6]=float_byte_array[1];
					send_data[7]=float_byte_array[2];
					send_data[8]=float_byte_array[3];
				break
				/////
				////////////////////////
				case 'nav_set_pidparam':
					send_data=this.upr_cmd[name];
					var incr=document.getElementById(name+"_ke_value_gr").value;
					float_byte_array=byte_arr_from_float_gr(incr);
					send_data[5]=float_byte_array[0];
					send_data[6]=float_byte_array[1];
					send_data[7]=float_byte_array[2];
					send_data[8]=float_byte_array[3];
					
					var incr=document.getElementById(name+"_kp_value_gr").value;
					float_byte_array=byte_arr_from_float_gr(incr);
					send_data[9 ]=float_byte_array[0];
					send_data[10]=float_byte_array[1];
					send_data[11]=float_byte_array[2];
					send_data[12]=float_byte_array[3];
					
					var incr=document.getElementById(name+"_ki_value_gr").value;
					float_byte_array=byte_arr_from_float_gr(incr);
					send_data[13]=float_byte_array[0];
					send_data[14]=float_byte_array[1];
					send_data[15]=float_byte_array[2];
					send_data[16]=float_byte_array[3];
				break
				/////
				////////
				default:
					send_data[0]=0;
				break;
			}
			
			var xmlhttprq_test = new XMLHttpRequest();
			xmlhttprq_test.open('POST', url, true);//, true
			xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
			xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
			//var uint8 = new Uint8Array(2);
			//uint8[0] = 1;
			//uint8[1] = 2;
			xmlhttprq_test.send(send_data);//this.upr_cmd[name]
			//console.log(send_data);
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class json_config_read_gr{
		//Инициализация
			constructor() {}
		//Парсинг
			parser_data(type,arr){
				//console.log(arr);
				//if(Array.isArray(arr)){
					auto_boat_config=arr;
					//!!!update_config_data();
					create_table_from_array_gr(arr,'main_settings_edit');
				//}else{
				//	console.error("Настройки не получены");
				//	console.log(arr);
				//}
			}
	}

	function autoboat_save_settings_send_db(){
		var xmlhttprq_test = new XMLHttpRequest();
		xmlhttprq_test.open('POST', 'http://localhost:3128/w/db/autoboat/config.json', true);//, true
		xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
		xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		xmlhttprq_test.send(JSON.stringify(auto_boat_config));
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class json_routing_sets_read_gr{
		//Инициализация
			constructor() {}
		//Парсинг
			parser_data(type,arr){
				//console.log(arr);
				//if(Array.isArray(arr)){
					auto_boat_routing_sets=arr;
					create_table_from_array_gr(auto_boat_routing_sets,'routing_sets');
				//}
			}
	}
	
	function autoboat_save_routing_sets_send_db(){
		var xmlhttprq_test = new XMLHttpRequest();
		xmlhttprq_test.open('POST', 'http://localhost:3128/w/db/autoboat/routing_sets.json', true);//, true
		xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
		xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		xmlhttprq_test.send(JSON.stringify(auto_boat_routing_sets,null, '\t'));
		//console.log(auto_boat_routing_sets);
		//console.log(JSON.stringify(auto_boat_routing_sets,null, ' '));
	}

	function autoboat_routing_sets_test(){
		//console.log(trip_point_arr);
		var arr_push={};
		arr_push['name']="test name";
		arr_push['description']="test description";
		arr_push['start_point']=0;
		arr_push['loop_point']=3;
		arr_push['points']=new Array();
		
		var cord=new Float32Array(2);
		for(var i=0;i<trip_point_arr.length;i++){
			cord=trip_point_arr[i]['point'].geometry.getCoordinates();
			arr_push['points'].push(cord);
		}
		
		
		auto_boat_routing_sets.push(arr_push);
		//console.log(auto_boat_routing_sets);
		autoboat_save_routing_sets_send_db();
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
