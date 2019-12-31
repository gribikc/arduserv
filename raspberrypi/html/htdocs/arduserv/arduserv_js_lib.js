'use strict';
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//messageDEEP_MYSQL_TO_MAP
	class json_deep_to_map_gr{
		//Инициализация
			constructor() {
				
			}
		//Парсинг
			parser_data(arr){
				
				document.getElementById("gr_db_log_txa").innerHTML="Size:";
				document.getElementById("gr_db_log_txa").innerHTML+=arr.length;
				document.getElementById("gr_db_log_txa").innerHTML+='\n';
				
				//console.log(arr);
				
				var x=0;
				var y=0;
				for(var j=1;j<arr.length;j++){//обход входного массива сообщений
					x=arr[j][0][2]/100;
					x=x.toFixed(0)*1+(x-x.toFixed(0))*1.666666666;
					if(arr[j][0][3]!="N"){
						x=x*(-1);
					}
					y=arr[j][0][4]/100;
					y=y.toFixed(0)*1+(y-y.toFixed(0))*1.666666666;
					if(arr[j][0][5]!="E"){
						y=y*(-1);
					}
					document.getElementById("gr_db_log_txa").innerHTML+="X:"+x;
					document.getElementById("gr_db_log_txa").innerHTML+=";Y:"+y;
					document.getElementById("gr_db_log_txa").innerHTML+=";D:"+arr[j][1][1]+'\n';
					yandex_map_add_deep_gr(x,y,arr[j][1][1]);
				}
			}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//messageDB_HUB
	class valid_db_gr{
		//Инициализация
			constructor(db) {
				this.db_array=db;
			}
		//Парсинг
			parser_data(arr){
				type=0;///!!!
				console.log("error");
				for(var j=0;j<arr.length;j++){//обход входного массива сообщений
					for(var i=0;i<this.db_array.length;i++){//обход базданного массива
						if(type==this.db_array[i].type && arr[j][0]==this.db_array[i].mark){//проверяем тип сообщения и индентификатор
							for(var k=0;k<arr[j].length;k++){//обход массива сообщения
								if(this.db_array[i].matrix[k][0]==1){
									document.getElementById(this.db_array[i].matrix[k][1]).innerHTML=this.db_array[i].matrix[k][2];
									document.getElementById(this.db_array[i].matrix[k][1]).innerHTML+=this.db_array[i].matrix[k][3](arr[j][k])
									document.getElementById(this.db_array[i].matrix[k][1]).innerHTML+=this.db_array[i].matrix[k][4];
								}
							}
						}
					}
				}
			}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PARSERing
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SNMP
	/*
	
	*/
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	class array_data_to_log_gr {
		//Инициализация
			constructor() {

			}
		//Парсинг
			parser_data(stream){
				console.log(stream);
			}
			error_event(message){
				this.hub_handler.error_event(message);
			}
	}
	class array_to_to_to_gr {
		//Инициализация
			constructor() {

			}
		//Парсинг
			parser_data(stream){
				
			}
			error_event(message){
				this.hub_handler.error_event(message);
			}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//JSON
	/*
	Принимает поток данных конечной длинны генерируемый сервером(php&mysql) заранее структурированный
	*/
	class json_parser_gr {
		//Инициализация
			constructor(hub) {
				this.parser_data_array=new Array();
				this.hub_handler=hub;
			}
		//Парсинг
			parser_data(stream){
				this.parser_data_array=JSON.parse(stream);
				
				if(this.parser_data_array.length>0 || Object.keys(this.parser_data_array).length>0){
					this.hub_handler.parser_data(this.parser_data_array);					
					this.parser_data_array=new Array();
				}
			}
			error_event(message){
				this.hub_handler.error_event(message);
			}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//JSON_STREAM
	class json_stream_parser_gr{
		//Инициализация
			constructor(hub){
				this.parser_data_array=new Array();
				this.hub_handler=hub;
				this.start_point=0;
				this.end_point=0;
				this.json_begin_point=0;
				this.json_begin_point_valid=0;
			}
		//Парсинг
			parser_data(stream){
				this.end_point=stream.length;
					if(this.start_point>=this.end_point){
						this.start_point=0;
					}
					for(var i=this.start_point;i<this.end_point;i++){
						if(this.start_point>=31){
							if(	(stream.charAt(i-0)) 	==	"{" &&
								(stream.charAt(i-1)) 	==	":" &&
								(stream.charAt(i-2)) 	==	"n" &&
								(stream.charAt(i-3)) 	==	"o" &&
								(stream.charAt(i-4)) 	==	"s" &&
								(stream.charAt(i-5)) 	==	"j" &&
								(stream.charAt(i-6)) 	==	"t" &&
								(stream.charAt(i-7)) 	==	"r" &&
								(stream.charAt(i-8)) 	==	"a" &&
								(stream.charAt(i-9)) 	==	"t" &&
								(stream.charAt(i-10)) 	==	"s" &&
								(stream.charAt(i-11)) 	==	"d" &&
								(stream.charAt(i-12)) 	==	"x"){//xdstartjson:{
									this.json_begin_point=i;
									this.json_begin_point_valid=1;
							}
							if(	(stream.charAt(i-0)) 	==	"n" &&
								(stream.charAt(i-1)) 	==	"o" &&
								(stream.charAt(i-2)) 	==	"s" &&
								(stream.charAt(i-3)) 	==	"j" &&
								(stream.charAt(i-4)) 	==	"p" &&
								(stream.charAt(i-5)) 	==	"o" &&
								(stream.charAt(i-6)) 	==	"t" &&
								(stream.charAt(i-7)) 	==	"s" &&
								(stream.charAt(i-8)) 	==	"d" &&
								(stream.charAt(i-9)) 	==	"x" &&
								(stream.charAt(i-10)) 	==	":" &&
								(stream.charAt(i-11)) 	==	"}"){//}:xdstopjson
									if(this.json_begin_point_valid==1){
										this.parser_data_array=JSON.parse( stream.slice(this.json_begin_point, i-10) );
				
										if(this.parser_data_array.length>0 || Object.keys(this.parser_data_array).length>0){
											this.hub_handler.parser_data(this.parser_data_array);					
											this.parser_data_array=new Array();
										}
										//console.log(this.parser_data_array);
									}
									this.json_begin_point_valid=0;
							}
						}
					}
				this.start_point=this.end_point;
			}
			error_event(message){
				this.hub_handler.error_event(message);
			}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//RAW
	/*
	Принимает бесконечный поток без начала и конца
	В класс нужно передать длинну сообщения,заголовок и конец чтобы получить массив нарезанных сообщений,но это не точно
	*/
	class raw_parser_gr {
		//Инициализация
			constructor(hub,db_matrix) {//hub
				this.parser_data_array=new Array();
				this.hub_handler=hub;
				this.start_point=0;
				this.end_point=0;
				this.db_matrix=db_matrix;
				
				this.MESSAGE_LEN=95;
				this.HEADER=[0xAA,0xBB];
				this.FOOTER=[0xCC,0xDD];
			}
		//Парсинг
			parser_data(stream){
				this.end_point=stream.length;
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
								this.message_parser(stream,i);
							}
						}
					}
				}
				this.start_point=this.end_point;
			}
			message_parser(stream,end_byte){
				var tmp_float_from_byte=0;
				for(var i in this.db_matrix){
					this.db_matrix[i][3]=0;//обнуляем матрицу
					if(this.db_matrix[i][1]==0){//char
						this.db_matrix[i][3]=stream.charCodeAt(end_byte+this.db_matrix[i][2]-this.MESSAGE_LEN)&0xFF;
					}else if(this.db_matrix[i][1]==1){//float
						//float_from_byte_arr_gr(buf)
						tmp_float_from_byte=stream.charCodeAt(end_byte+this.db_matrix[i][2]-this.MESSAGE_LEN-0)&0xFF;
						tmp_float_from_byte=tmp_float_from_byte<<8;
						tmp_float_from_byte+=stream.charCodeAt(end_byte+this.db_matrix[i][2]-this.MESSAGE_LEN-1)&0xFF;
						tmp_float_from_byte=tmp_float_from_byte<<8;
						tmp_float_from_byte+=stream.charCodeAt(end_byte+this.db_matrix[i][2]-this.MESSAGE_LEN-2)&0xFF;
						tmp_float_from_byte=tmp_float_from_byte<<8;
						tmp_float_from_byte+=stream.charCodeAt(end_byte+this.db_matrix[i][2]-this.MESSAGE_LEN-3)&0xFF;
						//tmp_float_from_byte=tmp_float_from_byte<<8;
						
						this.db_matrix[i][3]=float_from_byte_arr_gr(tmp_float_from_byte);//tmp_float_from_byte;
					}else if(this.db_matrix[i][1]==2){//byte.float
						//float_from_byte_arr_gr(buf)
						tmp_float_from_byte=stream.charCodeAt(end_byte+this.db_matrix[i][2]-this.MESSAGE_LEN-0)&0xFF;
						tmp_float_from_byte=tmp_float_from_byte<<8;
						tmp_float_from_byte+=stream.charCodeAt(end_byte+this.db_matrix[i][2]-this.MESSAGE_LEN-1)&0xFF;
						tmp_float_from_byte=tmp_float_from_byte<<8;
						tmp_float_from_byte+=stream.charCodeAt(end_byte+this.db_matrix[i][2]-this.MESSAGE_LEN-2)&0xFF;
						tmp_float_from_byte=tmp_float_from_byte<<8;
						tmp_float_from_byte+=stream.charCodeAt(end_byte+this.db_matrix[i][2]-this.MESSAGE_LEN-3)&0xFF;
						//tmp_float_from_byte=tmp_float_from_byte<<8;
						
						this.db_matrix[i][3]=float_from_byte_arr_gr(tmp_float_from_byte);//+stream.charCodeAt(end_byte+this.db_matrix[i][2]-this.MESSAGE_LEN-4)&0xFF
					}else if(this.db_matrix[i][1]==3){//int
						tmp_float_from_byte=stream.charCodeAt(end_byte+this.db_matrix[i][2]-this.MESSAGE_LEN-0)&0xFF;
						tmp_float_from_byte=tmp_float_from_byte<<8;
						tmp_float_from_byte+=stream.charCodeAt(end_byte+this.db_matrix[i][2]-this.MESSAGE_LEN-1)&0xFF;
						tmp_float_from_byte=tmp_float_from_byte<<8;
						tmp_float_from_byte+=stream.charCodeAt(end_byte+this.db_matrix[i][2]-this.MESSAGE_LEN-2)&0xFF;
						tmp_float_from_byte=tmp_float_from_byte<<8;
						tmp_float_from_byte+=stream.charCodeAt(end_byte+this.db_matrix[i][2]-this.MESSAGE_LEN-3)&0xFF;
						//tmp_float_from_byte=tmp_float_from_byte<<8;
						
						this.db_matrix[i][3]=tmp_float_from_byte;
					}else{
						this.db_matrix[i][3]="undf...";
					}
					//document.getElementById("autobot_state").innerHTML+=this.db_matrix[i][0]+": "+this.db_matrix[i][3]+"<br>";
					//console.log(this.db_matrix[i][0]+": "+this.db_matrix[i][3]);
					this.hub_handler.parser_data(this.db_matrix);
					//!!!yandex_map_add_point_gr(this.db_matrix['longitude'][3],this.db_matrix['latitude'][3],10.3);
					/*if(i=='longitude' && this.db_matrix['NOS'][3]>4){
						yandex_map_add_point_gr(this.db_matrix['latitude'][3],this.db_matrix['longitude'][3],10.3);
						//console.log(this.db_matrix['longitude'][3]);
						if(auto_boat_config['auto_move_map_to_boat']){
							yandex_map_center_map_to(this.db_matrix['latitude'][3],this.db_matrix['longitude'][3],0);
						}
					}*/
				}				
			}
			error_event(message){
				this.hub_handler.error_event(message);
			}
		//Сброс данных

		//чуть

		//чуть
		
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//NMEA
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MATRAS1
	/*
	Старая функция исправить!!!
	*/
	class datafall_gr{
		//Инициализация
			constructor() {
				this.period=15;				//установка при обнаружении $, сброс про обнаружении конца строки
				this.period_cnt=0;
				this.fall_data="";
				this.datafall_array=new Array();
				
				this.start_point=0;
				this.end_point=0;
			}
		//Парсинг
			parser_data(handler,start_point,end_point){
				for(var i=start_point;i<end_point;i++){	//обходим все поступившие данные
					this.period_cnt++;
					for(var j=0;j<7;j++){
						if(((handler.charCodeAt(i)>>j)%2)){
							this.fall_data+="1";
						}else{
							this.fall_data+="0";
						}
						if(this.period_cnt==this.period){
							this.datafall_array.push(this.fall_data);//!!!
							this.fall_data="";
							this.period_cnt=0;
						}
					}
				}
			}
		//Сброс данных
			clear_data_array(){
				this.datafall_array=new Array();
			}
			
		//чуть
		
		//чуть
		
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//xmlhttprq_stream_gr
	/*
	!!!В случае перезагрузки потока обеспечивать сброс указателей...
	Принимает в качестве параметра(parameter) структуру:
		url:'/cgi-bin/stream_usart.sh',
		mime_type:'text/plain; charset=x-user-defined',
		status_div_name:"Arduino uart:",
		parser: autoboat,//new raw_parser_gr(message_hub),
		flush_en:true,
		auto_start:true,
		status_en:true,
		status_timer:1000,
		status_div:"xhr_status_div",
		status_div_status_css:"xmlhttprq_stream_gr_status",
		status_div_stat_css:"xmlhttprq_stream_gr_stat",
		reload_en:true,
		reload_time:1000
	Выводит статистику, обеспечивает перезагрузкуи прочие параметры для потока.
	Передает полученные данные из потока в обработчик - "parser":parameter.parser.parser_data(this.responseText);
		Функция должна сама обеспечивать обработку даннных с учетом содержания указателя на данные типа NMEA,JSON и RAW.
	В случае если сервер генирирует JSON или подобные не обходимо обеспечить автоперезагрузку потока(auto_start:true)
	*/
	class xmlhttprq_stream_gr {
		//Инициализация
			constructor(parameter) {
				//this.url=url;
				//this.parser=parser;
				var this_of_class=this;
				var this_parameter=parameter;
				this.parameter=parameter;
				this.xmlhttprq = new XMLHttpRequest();
			
				//this.xmlhttprq.open('GET', parameter.url, true);//!!!
					this.is_post=('post_data' in parameter) ? 1 : 0;
					
					
					('mime_type' 	in this.parameter) ? null : (this.parameter.mime_type='text/plain; charset=x-user-defined');
					('url_w' 		in this.parameter) ? null : (this.parameter.url_w='');
					this.is_flush_en=('flush_en' in this.parameter) ? (this.parameter.flush_en ? 1:0) : 0;
					this.is_auto_start=('auto_start' in this.parameter) ? (this.parameter.auto_start ? 1:0) : 1;	
					this.is_status_en=('status_en' in this.parameter) ? (this.parameter.status_en ? 1:0) : 0;
					this.is_reload_en=('reload_en' in this.parameter) ? (this.parameter.reload_en ? 1:0) : 0;
					this.is_timeout_en=('timeout_en' in this.parameter) ? (this.parameter.timeout_en ? 1:0) : 0;
					
					if(this.is_auto_start){
						this.open_c();
					}

					/*this.xmlhttprq.open( ((this.is_post) ? 'POST' : 'GET') , parameter.url, true);
					this.xmlhttprq.overrideMimeType(parameter.mime_type);				
					if('timeout_en'	in parameter){
						if(parameter.timeout_en){
							this.xmlhttprq.timeout = parameter.timeout_time;;
						}
					}
					this.xmlhttprq.send( ((this.is_post) ? parameter.post_data : null) );//!!!*/
				
				this.stat_bps=0;
				this.stat_rp=0;
				this.last_statusText="";
				this.last_readyState=0;
				
				if(this.is_status_en){
					this.status_div = document.createElement('div');
					this.stat_div = document.createElement('div');
					this.status_div.className = parameter.status_div_status_css;
					this.stat_div.className = parameter.status_div_stat_css;
					var main_status_div=document.createElement('div');
					main_status_div.appendChild(this.status_div);
					main_status_div.appendChild(this.stat_div);
					document.getElementById(parameter.status_div).appendChild(main_status_div);
				
					setInterval(function(){this_of_class.view_stat();},parameter.status_timer);
					
					//console.log(this.status_div);
				}
				
				this.xmlhttprq.onprogress=function(e){
					if(this_of_class.is_flush_en && this_of_class.xmlhttprq.readyState!=4){
						parameter.parser.parser_data(this.responseText);//!!!
					}
				}				
				
				this.xmlhttprq.onreadystatechange=function(){//this.check_stage();    
					if(this.readyState==4){//DONE
						parameter.parser.parser_data(this.responseText);//!!!
						
						this_of_class.stat_rp-=this.responseText.length;
						//console.log(e);
						if(this_of_class.is_reload_en){
							setTimeout(function(e) {this_of_class.open_c();},this_parameter.reload_time);
						}
					}
				}
				
				//this.tii=setInterval(function(){this_of_class.stat_div.innerHTML+=1},1000);

			}
		//чуть
			view_stat(){
				this.status_div.innerHTML=this.parameter.name+":";
				this.status_div.innerHTML+=""+this.xmlhttprq.statusText;
				this.status_div.innerHTML+="("+this.xmlhttprq.readyState+")";
				this.status_div.innerHTML+="  <a onclick='xhrsc.find(elem  => elem.parameter.name==\""+this.parameter.name+"\").test();'>test</a>";
				this.status_div.innerHTML+="  <a onclick='xhrsc.find(elem  => elem.parameter.name==\""+this.parameter.name+"\").close_c();'>Close</a>";
				this.status_div.innerHTML+="  <a onclick='xhrsc.find(elem  => elem.parameter.name==\""+this.parameter.name+"\").open_c();'>Open</a>";
				this.status_div.innerHTML+="  <a onclick='xhrsc.find(elem  => elem.parameter.name==\""+this.parameter.name+"\").freeze_c();'>Freeze</a>";
				this.status_div.innerHTML+="  <a onclick='xhrsc.find(elem  => elem.parameter.name==\""+this.parameter.name+"\").reload_en_inv_c();'>Reload_inv</a>";				
				
				this.stat_bps=this.stat_bps*0.95+8*((this.xmlhttprq.responseText.length-this.stat_rp)/1)*0.05;
				this.stat_rp=this.xmlhttprq.responseText.length;
				if(this.stat_bps<1000){
					this.stat_div.innerHTML='Скорость: '+(this.stat_bps.toFixed(2))+' бит/с.';//bit per second
				}else{
					this.stat_div.innerHTML='Скорость: '+((this.stat_bps/1000).toFixed(2))+' Kбит/с.';//bit per second
				}
				//console.log(this.name);
				//console.log(this_of_class);
				//console.log(this.parameter);
			}
		//чуть
			test(){
				console.log("Test;");
				return 1;
			}
			close_c(){
				this.parameter.reload_en=false;
				this.xmlhttprq.abort();
			}
			open_c(){
				this.xmlhttprq.open( ((this.is_post) ? 'POST' : 'GET') , this.parameter.url, true);
				this.xmlhttprq.overrideMimeType(this.parameter.mime_type);				
				//if('timeout_en'	in this.parameter){
					//if(this.parameter.timeout_en){
					this.xmlhttprq.timeout =(this.is_timeout_en) ? (this.parameter.timeout_time) : null;
					//}
				//}
				this.xmlhttprq.send( ((this.is_post) ? this.parameter.post_data : null) );//!!!
			}
			freeze_c(){
				this.close_c();
				setTimeout(function(e) {e.open_c();},5000,this);
			}
			reload_en_inv_c(){
				if(this.parameter.reload_en==false){
					this.parameter.reload_en==true;
				}else{
					this.parameter.reload_en==false;
				}
			}
			//close()//stop()
			//open()//start()
			//freeze()
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//paper_js_gr
	class paper_js_gr{
			////test_paper.activate()
			//Инициализация
			constructor(inner) {
				this.inner=inner;
				this.paper_image = new paper.PaperScope();//new paper.install(window);
				this.paper_image.PaperScope();
				this.paper_image.setup(inner);
				this.children = this.paper_image.project.activeLayer.children;
				
				/*this.i=0;
				for(this.i = 0; this.i < 10; this.i++){    
					this.x = Math.floor(Math.random()*(this.canvas_width-50))+20;
					this.y = Math.floor(Math.random()*(this.canvas_height-50))+20;
					this.text = new paper.PointText(new this.paper_image.paper.Point(this.x, this.y))
					this.text.fillColor = 'black';
					this.text.content =  Math.floor(Math.random()*(100));
					this.text.fontSize = '20px';
					this.text.fontFamily = "arial";
				}*/
				this.paper_image.view.draw();
			}
			//
			push_graph(value,size){//add_obj
				//this.canvas_width  = 500;// document.getElementById(this.inner).width;// 500;// $("#canvas").width();
				//this.canvas_height = 300;// document.getElementById(this.inner).height;//300 $("#canvas").height();
				
				this.paper_image.activate();
				this.move();
				
				var x=500-10;
				var y=300-value-10;
				
				var graph_point=new this.paper_image.Path.Rectangle(new this.paper_image.Point(x, y), size,size);
				graph_point.fillColor='#FF0000';
				this.paper_image.view.draw();
				//this.mashtab();				
			}
			//
			mashtab(){
				this.paper_image.activate();
				var matoj=0;
				for (var i=0;i<this.children.length;i++){
					matoj+=this.children[i].position.y;
				}
				console.log(matoj/(i+1));
				this.paper_image.view.draw();
			}
			//
			move(){
				this.paper_image.activate();
				for (var i=0;i<this.children.length;i++){
					this.children[i].position.x-=5;//this.children[i].width;//5;
					if(this.children[i].position.x<=11){
						this.children[i].remove();
					}
				}
				this.paper_image.view.draw();
			}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//nrf24l01p_js_gr
	class nrf24l01p_js_gr{
			//Инициализация
			constructor() {
				
			}
			//
			get_config(){
				
			}
			
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//...
	function hide_view_inner_gr(inner_html){
		//document.getElementById(inner).visibility    hidden   visible
		//document.getElementById(inner).position      absolute unset
		//document.getElementById(inner).zIndex			0 		unset
		//alert(document.getElementById(inner).style.visibility);
		//alert(document.getElementById(inner).style.position);
		//alert(document.getElementById(inner).style.zIndex);
		//console.log(document.getElementById(inner_html).style);
		
		if(document.getElementById(inner_html).style.visibility=="visible" || document.getElementById(inner_html).style.position=="unset" ||
		   document.getElementById(inner_html).style.zIndex=="unset" || document.getElementById(inner_html).style.visibility=="" ||
		   document.getElementById(inner_html).style.position=="" ||  document.getElementById(inner_html).style.zIndex==""){
			document.getElementById(inner_html).style.visibility="hidden";
			document.getElementById(inner_html).style.position="absolute";
			document.getElementById(inner_html).style.zIndex=-1;
		}else{
			document.getElementById(inner_html).style.visibility="visible";
			document.getElementById(inner_html).style.position="unset";
			document.getElementById(inner_html).style.zIndex="unset";
		}
	}//////////////////////////////////////////
	///////////////////////////////////////////
	function hiden_change_inner_gr(inner_html){
		if(document.getElementById(inner_html).style.visibility=="visible"){
			document.getElementById(inner_html).style.visibility="hidden";
		}else{
			document.getElementById(inner_html).style.visibility="visible";
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//...
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
	}////////////////////////////////////
	/////////////////////////////////////
	function byte_arr_from_float_gr(buf){
		var float32	= new Float32Array(1);
		float32[0] 	= buf;
		var float32_ba = new Uint8Array(float32.buffer);
		//console.log(float32_ba);
		return float32_ba;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//create_table
	function create_table_from_array_gr(arr_in,div){
		
		var table = document.createElement("table");
		var tr,td,text,temp;
        table.setAttribute("border", "2px");
		var arr=new Array();

		var i=0;
		do{
			if(Array.isArray(arr_in)){
				arr=arr_in[i];
				if(i>0){
					tr = document.createElement("tr");
					td = document.createElement("td");
					td.setAttribute("colspan", 2);
					text = document.createTextNode("---");
					td.appendChild(text);
					tr.appendChild(td);
					table.appendChild(tr);
				}
			}else{
				arr=arr_in;
			}
				for(var key in arr) {
					tr = document.createElement("tr");
					td = document.createElement("td");
					text = document.createTextNode(key);
					td.appendChild(text);
					tr.appendChild(td);
				
					if(arr[key].length>0 && Array.isArray(arr[key])){
						td.setAttribute("rowspan", arr[key].length);
						for(var k in arr[key]) {
							td = document.createElement("td");
							text = document.createTextNode(arr[key][k]);
							td.appendChild(text);
							tr.appendChild(td);
							table.appendChild(tr);
							
							tr = document.createElement("tr");
							table.appendChild(tr);
						}
						table.removeChild(tr);
					}else{
						td = document.createElement("td");
						text = document.createTextNode(arr[key]);
						td.appendChild(text);
						tr.appendChild(td);
						table.appendChild(tr);
					}
				}
			i++;
		} while(i<arr_in.length)
		//}

		document.getElementById(div).appendChild(table);
	}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function key_array_to_inner(array,inner){
	document.getElementById(inner).innerHTML="";
	var stream=array;
	for(var key in stream) {
		document.getElementById(inner).innerHTML+=key+": "+stream[key]+"<br>";
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if (!Array.isAssociativeArray) {
  Array.isAssociativeArray = function(arg) {
    return Object.prototype.toString.call(arg) === '[object Object]';
  };
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*window.onerror = function (msg, url, line) {
	//alert(msg + "\n" + url + "\n" + "\n" + line);
	//document.getElementById("error_log").innerHTML+=msg + "\n" + url + "\n" + "\n" + line;
	return true;
};*/
//...