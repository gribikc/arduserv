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


var message_parsing_array=new Array();
	var arr_push={
		type:'nmea',
		mark:'$TSTCNT',
		matrix:[
			[0],
			[
				1,
				"test_counter_div",
				"Тестовый счетчик ",
				function(a) { return a;},//test_paper_cnt.push_graph(a*1,5);//test_paper_cnt.push_graph(a*1,5);
				" насчитано."
			],
			[0]
		]
	};
	message_parsing_array.push(arr_push);
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
				
				console.log(i);
				
				if(rf=='f'){
					if( !(inner=document.getElementById("main_wiev_div").children[i+1]) ){
						inner=document.getElementById("main_wiev_div").children[0];
					}else{
						i++;
					}
				}else{
					if( !(inner=document.getElementById("main_wiev_div").children[i-1]) ){
						inner=document.getElementById("main_wiev_div").children[inner_count-1];
					}else{
						i--;
					}
				}

				inner.style.visibility="visible";
				inner.style.position="unset";
				inner.style.zIndex="unset";
				

				vis_ch_tg=1;
			}
		}
	}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
auto_boat_config={
	auto_move_map_to_boat:false,
	
	ssf:false
};
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//$(document).ready(function(){
function main_init(){
	//
		//start_wiev();
	//HUB
		message_hub = new valid_db_gr(message_parsing_array);//хаб сообщений
		//autoboat
		autoboat=new autoboat_gr();
	//STREAM
		//Тестовый счетчик
			test_cnt_stream_param={
				url:'http://localhost:3128/R/COM/9/115200/',//'/cgi-bin/test_counter.sh',
				mime_type:'text/plain; charset=x-user-defined',
				status_div_name:"TSTCNT:",
				parser: new nmea_parser_gr(message_hub),
				
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
			new xmlhttprq_stream_gr(test_cnt_stream_param);//'/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112
		//_Тестовый счетчик_
		//arduino_uart
			arduino_uart_stream_param={
				url:'http://172.20.10.4:3128/R/BT/HC-06/',//http://192.168.0.122:3128/R/BT/HC-06/',//'/cgi-bin/stream_usart.sh',
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
			};
			new xmlhttprq_stream_gr(arduino_uart_stream_param);//'/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112
		//_arduino_uart
		//http://172.20.10.4:3128/
	//STREAM_
	//PAPER JS
		test_paper_cnt=new paper_js_gr('canvas2');//!!!
		test_paper=new paper_js_gr('canvas3');
}
