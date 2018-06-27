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
				//this.url=url;
				//this.parser=parser;
				this.xmlhttprq = new XMLHttpRequest();
				
				this.xmlhttprq.open('GET', url, true);
				this.xmlhttprq.overrideMimeType('text/plain; charset=x-user-defined');				
				this.xmlhttprq.send();
				
				this.xmlhttprq.onprogress=function(){
					//console.log(this.responseText);
					parser.parser_data(this.responseText);

				}
				
				this.xmlhttprq.onreadystatechange=function(){//this.check_stage()
					//console.log(this.readyState);
					if(this.readyState==4){//DONE
						this.open('GET', url, true);
						this.overrideMimeType('text/plain; charset=x-user-defined');					
						setTimeout(function(e) {e.send()},300,this);//this.send()
					}
				}
			}
		//чуть
		//чуть
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
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
//
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
//