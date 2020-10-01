//'use strict';
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
//terminal=new terminal();
let terminal=new Object();
let socket=new Object();

function main_init(){
	//terminal=new terminal();
		terminal=new terminal_gr();
			terminal_stream_param={
				url		:	"ws://127.0.0.1:3129/sys/gen/",
				url		:	"ws://127.0.0.1:3129/sys/gen/1000/cnt/10",
				//parser	:	new nt_json_stream_gr(serial_list,{collected:1}),
				parser	:	terminal,// //new nt_json_gr(serial_list,{collected:0}),

				auto_start:true,

				reload_en:true,
				reload_time:1000
			}

			socket=new web_sock_stream_gr(terminal_stream_param);
			terminal.add_socket(socket);
		//_arduino_uart
	///////////////////
}
