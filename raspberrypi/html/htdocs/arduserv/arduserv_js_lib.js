'use strict';
//messageDB
	class valid_db_gr{
		//Инициализация
			constructor(db) {
				this.db_array=db;
			}
		//Парсинг
			parser_data(type,arr){
				console.log(this.db_array);
				console.log(arr);
				for(var j=0;j<arr.length;j++){
					for(var i=0;i<this.db_array.length;i++){
						console.log(type);
						console.log(arr[i]);
						console.log(this.db_array);
						if(type==this.db_array[i].type && arr[j][0]==this.db_array[i].mark){
							document.getElementById(this.db_array[i].inner).innerHTML=(arr[j][1])/1000;
							//document.getElementById('center_div').innerHTML+=this.db_array[i].mark;
						}
					}
				}
			}
	}
//NMEA
	class nmea_gr {
		//Инициализация
			constructor(hub) {
				this.parser_start_valid=0;				//установка при обнаружении $, сброс про обнаружении конца строки
				this.nmea_data;							//буфер для выдергивания сообщений
				this.parser_nmea_array=new Array();
				
				this.start_point=0;
				this.end_point=0;
				this.handler_str;
				this.next_track;
				
				this.hub_handler=hub;
			}
		
		//Парсинг
			parser_data(stream){//,start_point,end_point
				console.log(stream);
				//this.end_point=this.handler_str.responseText.length;
				this.end_point=stream.length;
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
							
							
							/*
							nmea_status.innerHTML="C:"+this.parser_nmea_array.length;
							nmea_status.innerHTML=this.nmea_data;					//вывод данных
							nmea_status.innerHTML+="<br>";						
							for(var j=0;j<nmea_array.length;j++){
								nmea_status.innerHTML+=j+":";
								nmea_status.innerHTML+=nmea_array[j];
								nmea_status.innerHTML+="<br>";
							}
							*/
						}
					}
				}
				this.start_point=this.end_point;
				if(this.parser_nmea_array.length>0 && 1){
					this.hub_handler.parser_data('nmea',this.parser_nmea_array);
					this.parser_nmea_array=new Array();
				}
			}

		//Сброс данных
			clear_nmea_array(){
				this.parser_nmea_array=new Array();
			}
		//чуть
			//capture_stream(handler){
			//	this.handler_str=handler;
			//	//console.log(handler);
			//}
		//чуть
		
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MATRAS1
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
//SYSMON
//NMEA
	class xmlhttprq_stream_gr {
		//Инициализация
			constructor(url,parser) {
				this.a='qwerty';
				this.xmlhttprq = new XMLHttpRequest();
				
				this.xmlhttprq.open('GET', url, true);
				this.xmlhttprq.overrideMimeType('text/plain; charset=x-user-defined');

				this.xmlhttprq.send();
				
				//parser.capture_stream(this.xmlhttprq);
				//this.xmlhttprq.onprogress=parser.parser_data();//!!!//parser(this.xmlhttprq,'abc');
				this.xmlhttprq.onprogress=function(){
					console.log(this.responseText);
					parser.parser_data(this.responseText);
				}
				
				//console.log(parser);
				//this.xmlhttprq.onprogress=function(){
				//	center_div.innerHTML=this.responseText/1000;
				//}
			}
		//чуть
		
		//чуть
		
	}


