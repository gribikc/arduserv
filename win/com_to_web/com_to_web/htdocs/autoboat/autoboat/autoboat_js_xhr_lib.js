let nmea;// = new nmea_gr();
let datafall;// = new datafall_gr();
let sys_data;//=new xmlhttprq_stream_gr();
let message_db;

let test_paper;

//var xhr;// = new XMLHttpRequest();
//var xhr_read_point=0;
//var xhr_date = new Date;
//var xhr_fps=0;
//var xhr_bps=0;
//var xhr_temp;

var sys_data_param;
var test_cnt_stream_param;

var autoboat;


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////	
	function next_prev_main_wiev_div_in(rf){
		var i;
		var inner;
		var inner_count=document.getElementById("main_wiev_div").childElementCount;
		var vis_ch_tg=0;
		for(i=0;i<inner_count;i++){
			//document.getElementById("main_wiev_div").children[i].
			inner=document.getElementById("main_wiev_div").children[i];
			if(vis_ch_tg==1){
				inner.style.position="absolute";
				inner.style.visibility="hidden";
				inner.style.zIndex=-1;
			}else if(inner.style.visibility=="visible" || inner.style.position=="unset" ||
					 inner.style.zIndex=="unset"       || inner.style.visibility=="" ||
					 inner.style.position==""          || inner.style.zIndex==""){
				inner.style.position="absolute";
				inner.style.visibility="hidden";
				inner.style.zIndex=-1;
				
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
				inner.style.position="unset";
				inner.style.zIndex="unset";
			}
		}
	}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
var auto_boat_config={
	//map
	auto_move_map_to_boat:false,
	def_x_point:59.77883,
	def_y_point:30.77069,
	
	bap_stream_addr:[
		['http://localhost:3128/R/COM/28/57600/'],
		['http://192.168.0.122:3128/R/BT/HC-06/'],
		['http://172.20.10.4:3128/R/BT/HC-06'],
		['http://localhost:3128/R/COM/9/115200/'],
		['http://localhost:3128/R/COM/28/57600/']
	],
	
	ssf:false
};
var auto_boat_routing_sets={};
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

	//HUB
		config_hub = new json_config_read_gr();
		routing_sets_hub = new json_routing_sets_read_gr();
		//autoboat
		autoboat=new autoboat_gr();
	//STREAM
		//arduino_uart
			bap_uart_stream_param={
				url   :'http://localhost:3128/R/COM/28/57600/',//'http://localhost:3128/R/COM/28/57600/',//'http://192.168.0.122:3128/R/BT/HC-06/',//http://172.20.10.4:3128/R/BT/HC-06///http://192.168.0.122:3128/R/BT/HC-06/',//'/cgi-bin/stream_usart.sh',
				url_w :'http://localhost:3128/W/COM/28/57600/',//'http://localhost:3128/W/COM/28/57600/',
				mime_type:'text/plain; charset=x-user-defined',
				status_div_name:"BAP:",
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
			};
			new xmlhttprq_stream_gr(bap_uart_stream_param);//'/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112
		//_arduino_uart
		//http://172.20.10.4:3128/
		//CONFIG READ
			config_request_param={
				url   :'http://localhost:3128/htdocs/db/autoboat/config.json',//'http://localhost:3128/R/COM/28/57600/',//'http://192.168.0.122:3128/R/BT/HC-06/',//http://172.20.10.4:3128/R/BT/HC-06///http://192.168.0.122:3128/R/BT/HC-06/',//'/cgi-bin/stream_usart.sh',
				url_w :'http://localhost:3128/w/db/autoboat/config.json',//'http://localhost:3128/W/COM/28/57600/',
				mime_type:'text/plain; charset=x-user-defined',
				status_div_name:"CRP:",
				parser:  new json_parser_gr(config_hub),//new raw_parser_gr(message_hub),
				
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
			new xmlhttprq_stream_gr(config_request_param);//'/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112
		//CONFIG READ
		//routing_sets
			routing_sets_param={
				url   :'http://localhost:3128/htdocs/db/autoboat/routing_sets.json',//'http://localhost:3128/R/COM/28/57600/',//'http://192.168.0.122:3128/R/BT/HC-06/',//http://172.20.10.4:3128/R/BT/HC-06///http://192.168.0.122:3128/R/BT/HC-06/',//'/cgi-bin/stream_usart.sh',
				url_w :'http://localhost:3128/w/db/autoboat/routing_sets.json',//http://localhost:3128/W/COM/28/57600/',
				mime_type:'text/plain; charset=x-user-defined',
				status_div_name:"RPR:",
				parser:  new json_parser_gr(routing_sets_hub),//new raw_parser_gr(message_hub),
				
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
			//new xmlhttprq_stream_gr(routing_sets_param);//'/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112
		//CONFIG READ
	//STREAM_
	//PAPER JS
		//test_paper_cnt=new paper_js_gr('canvas2');//!!!
		//test_paper=new paper_js_gr('canvas3');
}
