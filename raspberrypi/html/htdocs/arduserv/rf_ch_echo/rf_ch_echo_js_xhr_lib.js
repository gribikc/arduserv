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

var ECHO_CH_RF;


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//$(document).ready(function(){
function main_init(){

	//HUB

	//_HUB
	//STREAM
		//arduino_uart
			bap_uart_stream_param={
				url   : (document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/R/COM/3/115200/',//'http://localhost:3128/R/COM/28/57600/',//'http://192.168.0.122:3128/R/BT/HC-06/',//http://172.20.10.4:3128/R/BT/HC-06///http://192.168.0.122:3128/R/BT/HC-06/',//'/cgi-bin/stream_usart.sh',
				url_w : (document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/W/COM/3/115200/',//'http://localhost:3128/W/COM/28/57600/',
				mime_type:'text/plain; charset=x-user-defined',
				status_div_name:"ECHO_RF:",
				parser: new echo_ch_rf_gr(),//new raw_parser_gr(message_hub),
				
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

}
