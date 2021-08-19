var autoboat;

//var db_routing_sets;
var autoboat_routing_sets;

//var db_config;
var data_config;
///////////////////////////////////////////////////////////
var config=new Object();
	//////////////////////////////////////////////
	config['dev_name']='HC-08';
	config['remoute_serv_ip']='192.168.3.176';//'192.168.1.44';//192.168.0.138//192.168.3.176//172.20.10.2
	config['remoute_serv_port']='80';
	//////////////////////////////////////////////
	config['dev_url']=	 (document.location.protocol=="file:") ? ("http://"+config['remoute_serv_ip']+":"+config['remoute_serv_port']) : "" ,
	//////////////////////////////////////////////
	//config['auto_move_map_to_boat']=true;
	config['map']=new Object();
	config['map']['auto_move_map_to_boat']=true;
	config['map']['point_of_position']=300;
	//////////////////////////////////////////////
	config['ssf']=false;
	//////////////////////////////////////////////
	wpp_gr.web_server_def	=config['dev_url'];
	wpp_gr.data_server_def	=config['dev_url'];
	wpp_gr.db_server_def	=config['dev_url'];
	wpp_gr.db_read_prefix="/db/";// esp32:"/db/",CTW:"/htdocs/db/"
	wpp_gr.db_write_prefix="/db/w/";
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//$(document).ready(function(){
function main_init(){
	autoboat=new autoboat_gr();
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
				url   : config['dev_url']+"/status",//config['dev_url'],
				url_w : config['dev_url']+"/write",
				mime_type:'text/plain; charset=x-user-defined',
				name:"BAP:",
				//parser: autoboat,//new raw_parser_gr(message_hub),
				parser: new nt_raw_parser_gr(autoboat,{collected:0,db_matrix:message}),
				
				flush_en:false,
				auto_start:true,
				
				status_en:false,
				status_timer:1000,
				status_div:"xhr_status_div",
				status_div_status_css:"xmlhttprq_stream_gr_status",
				status_div_stat_css:"xmlhttprq_stream_gr_stat",
				
				reload_en:true,
				reload_time:1000
			};
			new xmlhttprq_stream_gr(bap_uart_stream_param);//'/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112
			
			//WS
				terminal_stream_param={
					url			: "ws://127.0.0.1:3129/dev/com/r/3/115200",//"ws://127.0.0.1:3129/sys/gen/",
					parser	:	new nt_raw_parser_gr(autoboat,{collected:1,db_matrix:message}),// //new nt_json_gr(serial_list,{collected:0}),
					auto_start:true,
					reload_en:true,
					reload_time:1000
				}		
				//var socket=new web_sock_stream_gr(terminal_stream_param);
			//WS

		//CONFIG READ
			data_config=new json_config_read_gr({db_name:"autoboat",table_name:"config"});
		//_CONFIG READ
		//routing_sets
			autoboat_routing_sets=new json_routing_sets_read_gr({db_name:"autoboat",table_name:"routing_sets"});
		//_routing_sets
	//_STREAM

		
	generate_show_hide_menu_from_div('main_wiev_div','main_list_of_all');
	create_table_from_array_gr(config,'main_div_setings');
}

