let nmea;// = new nmea_gr();
let datafall;// = new datafall_gr();
let sys_data;//=new xmlhttprq_stream_gr();
let message_db;

let test_paper;

var xhr;// = new XMLHttpRequest();
var xhr_read_point=0;
var xhr_date = new Date;
var xhr_fps=0;
var xhr_bps=0;
var xhr_temp;

var message_parsing_array=new Array();
	var arr_push={
		type:'nmea',
		mark:'$SYST0',
		matrix:[
			[0],
			[
				1,
				"sys_info_termo",
				"Температура процессора ",
				function(a) { test_paper.push_graph(a/1000,5); return a/1000;},//test_paper.push_graph(a/1000,5);
				" градусов."
			],
			[0]
		]
	};
	message_parsing_array.push(arr_push);
	
	var arr_push={
		type:'nmea',
		mark:'$TSTCNT',
		matrix:[
			[0],
			[
				1,
				"test_counter_div",
				"Тестовый счетчик ",
				function(a) { test_paper_cnt.push_graph(a*1,5); return a;},//test_paper_cnt.push_graph(a*1,5);
				" насчитано."
			],
			[0]
		]
	};
	message_parsing_array.push(arr_push);
	
	



//$(document).ready(function(){
function main_init(){
	//STREAM
		message_hub=new valid_db_gr(message_parsing_array);//хаб сообщений

		sys_stream_nmea = new nmea_gr(message_hub);//
		sys_data=new xmlhttprq_stream_gr('/cgi-bin/sys_inf.sh',sys_stream_nmea,"xhr_status_div","SYS:");//17*8*3=408
		
		test_cnt_nmea = new nmea_gr(message_hub);//
		test_cnt_stream=new xmlhttprq_stream_gr('/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112
		
		//usb_arduino_nmea = new nmea_gr(message_hub);//
		//usb_arduino_stream=new xmlhttprq_stream_gr('/cgi-bin/stream_usart.sh',usb_arduino_nmea);
	
	//PAPER JS
		test_paper_cnt=new paper_js_gr('canvas2');//!!!
		test_paper=new paper_js_gr('canvas3');
}
