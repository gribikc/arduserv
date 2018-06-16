'use strict';
//messageDB_HUB
	class valid_db_gr{
		//Инициализация
			constructor(db) {
				this.db_array=db;
			}
		//Парсинг
			parser_data(type,arr){
				for(var j=0;j<arr.length;j++){
					for(var i=0;i<this.db_array.length;i++){
						if(type==this.db_array[i].type && arr[j][0]==this.db_array[i].mark){//проверяем тип сообщения и индентификатор
							for(var k=0;k<arr[j].length;k++){
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
//NMEA
	class nmea_gr {
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
					this.hub_handler.parser_data('nmea',this.parser_nmea_array);
					this.parser_nmea_array=new Array();
				}
			}

		//Сброс данных
			clear_nmea_array(){
				this.parser_nmea_array=new Array();
			}
		//чуть

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
//xmlhttprq_stream_gr
	class xmlhttprq_stream_gr {
		//Инициализация
			constructor(url,parser) {
				this.a='qwerty';
				this.xmlhttprq = new XMLHttpRequest();
				
				this.xmlhttprq.open('GET', url, true);
				this.xmlhttprq.overrideMimeType('text/plain; charset=x-user-defined');

				this.xmlhttprq.onprogress=function(){
					//console.log(this.responseText);
					parser.parser_data(this.responseText);

				}
				
				this.xmlhttprq.send();
			}
		//чуть
		
		//чуть
		
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//xmlhttprq_stream_gr

