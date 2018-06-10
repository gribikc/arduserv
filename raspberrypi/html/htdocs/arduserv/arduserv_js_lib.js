'use strict';

//NMEA
	class nmea_gr {
		//Инициализация
			constructor() {
				this.parser_start_valid=0;				//установка при обнаружении $, сброс про обнаружении конца строки
				this.nmea_data;							//буфер для выдергивания сообщений
				this.parser_nmea_array=new Array();
			}
		
		//Парсинг
			parser_data(handler,start_point,end_point){
				for(var i=start_point;i<end_point;i++){	//обходим все поступившие данные
					if(handler.charAt(i)=='$'){			//Обнаружели начало
						this.parser_start_valid=1;
						this.nmea_data="$";				//очищаем буфер
					}else{
						this.nmea_data+=handler.charAt(i);
						if(handler.charCodeAt(i)==10 && this.parser_start_valid==1){//Обнаружели конец////(xhr.responseText.charCodeAt(i-4)=="*" && xhr.responseText.charCodeAt(i-1)==13 || xhr.responseText.charCodeAt(i)==10 && nmea_start_point_valid==1
							this.parser_start_valid=0;

							var nmea_array=this.nmea_data.split(",");				//парсинг NMEA
							var temp=nmea_array[nmea_array.length-1].split("*");	//выделяем контрольную сумму
							nmea_array[nmea_array.length-1]=temp[0];
							nmea_array[nmea_array.length]=temp[1];
							this.parser_nmea_array.push(nmea_array);//!!!
							
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
			}

		//Сброс данных
			clear_nmea_array(){
				this.parser_nmea_array=new Array();
			}
		//чуть
		
		//чуть
		
	}

//MATRAS1
	class datafall_gr{
		//Инициализация
			constructor() {
				this.period=15;				//установка при обнаружении $, сброс про обнаружении конца строки
				this.period_cnt=0;
				this.fall_data="";
				this.datafall_array=new Array();
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


