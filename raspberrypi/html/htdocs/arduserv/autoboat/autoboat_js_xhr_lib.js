
var autoboat;
var autoboat_routing_sets;
var auto_boat_routing_sets=new Array();
///////////////////////////////////////////////////////////
var config=new Object();
	config['dev_name']='HC-08';
	config['remoute_serv_ip']='192.168.1.44';
	config['db_config_name']='config.json';
	config['db_routing_sets']='routing_sets.json';
	//////////////////////////////////////////////
	config['dev_url']=	( (document.location.protocol=="file:" ? "http://"+config['remoute_serv_ip']+":3128" : "" )+"/dev/bt/r/"+config['dev_name']+"/"),
	config['dev_url_w']=( (document.location.protocol=="file:" ? "http://"+config['remoute_serv_ip']+":3128" : "" )+"/dev/bt/w/"+config['dev_name']+"/"),
	//////////////////////////////////////////////
	//config['auto_move_map_to_boat']=true;
	config['map']=new Object();
	config['map']['auto_move_map_to_boat']=true;
	config['map']['point_of_position']=300;
	
	config['ssf']=false;
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
	function generate_show_hide_menu_from_div(main_div_name,control_div_name){
		var main_div = document.getElementById(main_div_name);
		var control_div = document.getElementById(control_div_name);
		var elementChildrens = main_div.children;
		for (var i=0, child; child=elementChildrens[i]; i++) {
			var new_div = document.createElement('a');
			new_div.onclick=function changeContent() {
				//console.log(this.name);
				view_main_menu_hide_all('main_list_of_all','main_wiev_div',1)
				hide_view_inner_gr(this.name);
			}		
			
			control_div.appendChild(new_div);
			new_div.classList.add('mini_icon_mm_gr');//mini_icon_mm_gr//menu_up_a_gr
			new_div.innerHTML=child.dataset['name'];
			new_div.name=child.id;
		}
	}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
	function view_main_menu_hide_all(div_menu,div_main,sw){
		var inner_count=document.getElementById("main_wiev_div").childElementCount;
		var vis_ch_tg=0;
		if(sw==0){
			document.getElementById(div_main).style.position='absolute';
			document.getElementById(div_main).style.visibility='hidden';
			document.getElementById(div_main).style.display='none'
			
			document.getElementById(div_menu).style.position='unset';
			document.getElementById(div_menu).style.visibility='';
			document.getElementById(div_menu).style.display=''
			for(i=0;i<inner_count;i++){
				inner=document.getElementById("main_wiev_div").children[i];
				inner.style.position="absolute";
				inner.style.visibility="hidden";
				inner.style.zIndex=-1;
			}
		}else{
			document.getElementById(div_menu).style.position='absolute';
			document.getElementById(div_menu).style.visibility='hidden';
			document.getElementById(div_menu).style.display='none'
			
			document.getElementById(div_main).style.position='unset';
			document.getElementById(div_main).style.visibility='';
			document.getElementById(div_main).style.display=''
		}
	}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
	function next_prev_main_wiev_div_in(rf){
		/*
			При переключении скрывать все и открывать только один или 
			если открыто несколько то закрывать первый открывать следующий...
		*/
		var i;
		var inner;
		var inner_count=document.getElementById("main_wiev_div").childElementCount;
		var vis_ch_tg=0;
		for(i=0;i<inner_count;i++){
			//document.getElementById("main_wiev_div").children[i].
			inner=document.getElementById("main_wiev_div").children[i];
			if(vis_ch_tg==1){
				inner.style.visibility="hidden";
				inner.style.zIndex=-1;
				inner.style.position="absolute";
				//inner.style.display="none";
			}else if(inner.style.visibility=="visible"	|| inner.style.position=="unset" 	||
					 inner.style.zIndex=="unset"       	|| inner.style.visibility=="" 		||
					 inner.style.position==""          	|| inner.style.zIndex==""){
				inner.style.visibility="hidden";
				inner.style.zIndex=-1;
				inner.style.position="absolute";
				//inner.style.display="none";
				
				//console.log(i);
				
				vis_ch_tg=1;
				if(rf=='f'){
					if( !(inner=document.getElementById("main_wiev_div").children[i+1]) ){
						inner=document.getElementById("main_wiev_div").children[0];
					}
					i++;
				}else{
					if( !(inner=document.getElementById("main_wiev_div").children[i-1]) ){
						inner=document.getElementById("main_wiev_div").children[inner_count-1];
						inner_count--;
					}
				}
				
				vis_ch_tg=1;
				inner.style.visibility="visible";
				inner.style.zIndex="unset";
				inner.style.position="unset";
				//inner.style.display="";
			}
		}
	}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
	function test_send_data1(){
		xmlhttprq_test = new XMLHttpRequest();
		xmlhttprq_test.open('POST', 'http://localhost:3128/W/COM/28/57600/', true);//, true
		xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
		xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		var uint8 = new Uint8Array(2);
		uint8[0] = 1;
		uint8[1] = 2;
		xmlhttprq_test.send(uint8);
		//!!!xmlhttprq_test.abort();
		//xmlhttprq_test.send();
	}	
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//$(document).ready(function(){
function main_init(){
	autoboat=new autoboat_gr();
	autoboat_routing_sets=new json_routing_sets_read_gr();

	//HUB
			var message=new Array();
			message[0]=new Object();
			message[0]['header']=[0xAA,0xBB];
			message[0]['footer']=[0xCC,0xDD];
			message[0]['message_len']=95;
			message[0]['message']={
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

		//autoboat
	//_HUB
	//STREAM
		//arduino_uart
			bap_uart_stream_param={
				url   : config['dev_url'],
				url_w : config['dev_url_w'],
				mime_type:'text/plain; charset=x-user-defined',
				name:"BAP:",
				//parser: autoboat,//new raw_parser_gr(message_hub),
				parser: new raw_parser_gr(autoboat,message),
				
				flush_en:true,
				auto_start:true,
				
				status_en:true,
				status_timer:1000,
				status_div:"xhr_status_div",
				status_div_status_css:"xmlhttprq_stream_gr_status",
				status_div_stat_css:"xmlhttprq_stream_gr_stat",
				
				reload_en:true,
				reload_time:1000
			};
			new xmlhttprq_stream_gr(bap_uart_stream_param);//'/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112
		//_arduino_uart
		//CONFIG READ
			config_request_param={
				url   : (document.location.protocol=="file:" ? "http://192.168.1.44:3128" : "" ) + '/htdocs/db/autoboat/config.json',//'http://localhost:3128/R/COM/28/57600/',//'http://192.168.0.122:3128/R/BT/HC-06/',//http://172.20.10.4:3128/R/BT/HC-06///http://192.168.0.122:3128/R/BT/HC-06/',//'/cgi-bin/stream_usart.sh',
				url_w : (document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/w/db/autoboat/config.json',//'http://localhost:3128/W/COM/28/57600/',
				mime_type:'text/plain; charset=x-user-defined',
				name:"CRP:",
				parser:  new json_parser_gr(new json_config_read_gr()),//new raw_parser_gr(message_hub),
				
				flush_en:false,
				auto_start:true,
				
				status_en:true,//!!!
				status_timer:1000,
				status_div:"xhr_config_div",
				status_div_status_css:"xmlhttprq_stream_gr_status",
				status_div_stat_css:"xmlhttprq_stream_gr_stat",
				
				reload_en:false,
				reload_time:1000
			};
			//new xmlhttprq_stream_gr(config_request_param);//'/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112
		//_CONFIG READ
		//routing_sets
			routing_sets_param={
				url   : (document.location.protocol=="file:" ? "http://192.168.1.44:3128" : "" ) + '/htdocs/db/autoboat/routing_sets.json',//'http://localhost:3128/R/COM/28/57600/',//'http://192.168.0.122:3128/R/BT/HC-06/',//http://172.20.10.4:3128/R/BT/HC-06///http://192.168.0.122:3128/R/BT/HC-06/',//'/cgi-bin/stream_usart.sh',
				url_w : (document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/w/db/autoboat/routing_sets.json',//http://localhost:3128/W/COM/28/57600/',
				mime_type:'text/plain; charset=x-user-defined',
				name:"RPR:",
				parser: new json_parser_gr(autoboat_routing_sets),//new raw_parser_gr(message_hub),
				
				flush_en:false,
				auto_start:true,
				
				status_en:true,//!!!
				status_timer:1000,
				status_div:"xhr_routing_sets_div",
				status_div_status_css:"xmlhttprq_stream_gr_status",
				status_div_stat_css:"xmlhttprq_stream_gr_stat",
				
				reload_en:false,
				reload_time:1000
			};
			new xmlhttprq_stream_gr(routing_sets_param);//'/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112
		//_routing_sets
	//_STREAM
	//PAPER JS
		//test_paper_cnt=new paper_js_gr('canvas2');//!!!
		//test_paper=new paper_js_gr('canvas3');
		
		
	generate_show_hide_menu_from_div('main_wiev_div','main_list_of_all');
}
