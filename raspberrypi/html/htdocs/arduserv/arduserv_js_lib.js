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
			parser_data(type,arr){
				
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
					document.getElementById("gr_db_log_txa").innerHTML+=";Y:"+arr[j][1][1]+'\n';
				}
			}
	}

//messageDB_HUB
	class valid_db_gr{
		//Инициализация
			constructor(db) {
				this.db_array=db;
			}
		//Парсинг
			parser_data(type,arr){
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
//JSON
	class json_parser_gr {
		//Инициализация
			constructor(hub) {
				this.parser_data_array=new Array();
				this.hub_handler=hub;
			}
		//Парсинг
			parser_data(stream){
				this.parser_data_array=JSON.parse(stream);
								
				if(this.parser_data_array.length>0 && 1){
					this.hub_handler.parser_data('json',this.parser_data_array);					
					this.parser_data_array=new Array();
				}
			}
		//Сброс данных

		//чуть

		//чуть
		
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//NMEA
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
			constructor(parameter) {
				//this.url=url;
				//this.parser=parser;
				var this_of_class=this;
				var this_parameter=parameter;
				this.xmlhttprq = new XMLHttpRequest();
				
				this.xmlhttprq.open('GET', parameter.url, true);
				this.xmlhttprq.overrideMimeType(parameter.mime_type);				
				this.xmlhttprq.send();
				
				this.stat_bps=0;
				this.stat_rp=0;
				
				if(parameter.status_en==true){
					this.tii=setInterval(function(){this_of_class.view_stat();},parameter.status_timer);

					this.status_div = document.createElement('div');
					this.stat_div = document.createElement('div');
					document.getElementById(parameter.status_div).appendChild(this.status_div);
					document.getElementById(parameter.status_div).appendChild(this.stat_div);
					
					this.status_div.className = parameter.status_div_status_css;
					this.stat_div.className = parameter.status_div_stat_css;
					
					//console.log(this.status_div);
				}
				
				this.xmlhttprq.onprogress=function(e){
					//console.log(this.responseText);
					//console.log(this_of_class.xmlhttprq.readyState);
					if(this_parameter.flush_en==true || this_of_class.xmlhttprq.readyState==4){
						parameter.parser.parser_data(this.responseText);//!!!
					}
				}				
				
				this.xmlhttprq.onreadystatechange=function(){//this.check_stage();
					//console.log(this_of_class);
					//console.log(this.status_div);//.innerHTML=this.readyState;
					//console.log(e);//event
					//console.log(this);//XMLHttpRequest
					this_of_class.status_div.innerHTML=parameter.status_div_name;
					this_of_class.status_div.innerHTML+=""+this.statusText;
					this_of_class.status_div.innerHTML+="("+this.readyState+")";
					//readyState;
					if(this.readyState==4){//DONE
						parameter.parser.parser_data(this.responseText);//!!!
						this_of_class.stat_rp-=this.responseText.length;
						//console.log(e);
						if(this_parameter.reload_en==true){
							this.open('GET', this_parameter.url, true);
							this.overrideMimeType(this_parameter.mime_type);					
							setTimeout(function(e) {e.send();},this_parameter.reload_time,this);//this.send()
						}
					}
				}
				
				//this.tii=setInterval(function(){this_of_class.stat_div.innerHTML+=1},1000);

			}
		//чуть
			view_stat(){
				this.stat_bps=this.stat_bps*0.95+8*((this.xmlhttprq.responseText.length-this.stat_rp)/1)*0.05;
				this.stat_rp=this.xmlhttprq.responseText.length;
				this.stat_div.innerHTML='Скорость: '+(this.stat_bps.toFixed(2))+' бит/с.';//bit per second
				//console.log(this);
			}
		//чуть
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
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//...