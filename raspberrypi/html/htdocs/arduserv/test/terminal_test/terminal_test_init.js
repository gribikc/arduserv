
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
	function test_send_data1(){
		xmlhttprq_test = new XMLHttpRequest();
		xmlhttprq_test.open('POST', 'http://192.168.0.101:3128/W/COM/28/57600/', true);//, true
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

		//autoboat
		//terminal=new terminal();
	//_HUB
	//STREAM
		//arduino_uart
			/*gps_stream_param={//location.hostname
				url   : (document.location.protocol=="file:" ? "http://127.0.0.1:3128" : "" ) +"/dev/com/l/", //(document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/R/COM/28/57600/',//'http://localhost:3128/R/COM/28/57600/',//'http://192.168.0.122:3128/R/BT/HC-06/',//http://172.20.10.4:3128/R/BT/HC-06///http://192.168.0.122:3128/R/BT/HC-06/',//'/cgi-bin/stream_usart.sh',
				url_w : "http://192.168.0.44:3128/W/GPS/",//(document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/W/COM/28/57600/',//'http://localhost:3128/W/COM/28/57600/',
				mime_type:'text/plain; charset=x-user-defined',
				status_div_name:"GPS:",
				//parser: new json_stream_parser_gr(gps),//new raw_parser_gr(message_hub),
				parser: new nt_json_gr(serial_list,{collected:0}),

				flush_en:false,
				auto_start:true,

				status_en:false,
				status_timer:1000,
				status_div:"xhr_status_div",
				status_div_status_css:"xmlhttprq_stream_gr_status",
				status_div_stat_css:"xmlhttprq_stream_gr_stat",

				reload_en:true,
				reload_time:5000
			};
			new xmlhttprq_stream_gr(gps_stream_param);//'/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112*/
			terminal_stream_param={
				url		:	"ws://127.0.0.1:3129/sys/gen/",
				//parser	:	new nt_json_stream_gr(serial_list,{collected:1}),
				parser	:	new terminal(),// //new nt_json_gr(serial_list,{collected:0}),

				auto_start:true,

				reload_en:true,
				reload_time:1000
			}
			new web_sock_stream_gr(terminal_stream_param);
		//_arduino_uart
	///////////////////
}
