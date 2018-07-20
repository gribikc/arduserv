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

var sys_data_param;
var test_cnt_stream_param;

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
	//HUB
		message_hub=new valid_db_gr(message_parsing_array);//хаб сообщений
	//HUB_
	//STREAM
		//Системная информация RPi
			sys_data_param={
				url:'/cgi-bin/sys_inf.sh',
				mime_type:'text/plain; charset=x-user-defined',
				status_div_name:"SYS:",
				parser: new nmea_parser_gr(message_hub),
				
				flush_en:true,
				auto_start:true,
				
				status_en:true,
				status_timer:1000,
				status_div:"xhr_status_div",
				status_div_status_css:"xmlhttprq_stream_gr_status",
				status_div_stat_css:"xmlhttprq_stream_gr_stat",
				
				reload_en:true,
				reload_time:1000,
				
			};
			new xmlhttprq_stream_gr(sys_data_param);//'/cgi-bin/sys_inf.sh',sys_stream_nmea,"xhr_status_div","SYS:");//17*8*3=408
		//Системная информация RPi_
		//Тестовый счетчик
			test_cnt_stream_param={
				url:'/cgi-bin/test_counter.sh',
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
				reload_time:1000,
				
			};
			new xmlhttprq_stream_gr(test_cnt_stream_param);//'/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112
		//Тестовый счетчик_
		//JSON_TEST
			test_json_param={
				url: 'php_core_gr/myTutorials.txt',
				mime_type: 'text/plain; charset=x-user-defined',
				status_div_name: "JSON_TEST:",
				parser: new nmea_parser_gr(message_hub),
				
				flush_en: false,
				auto_start: true,
				
				status_en: true,
				status_timer: 1000,
				status_div: "xhr_status_div",
				status_div_status_css: "xmlhttprq_stream_gr_status",
				status_div_stat_css: "xmlhttprq_stream_gr_stat",
				
				reload_en: false,
				reload_time: 1000,
				
			};
			new xmlhttprq_stream_gr(test_json_param);
		//JSON_TEST_
	//STREAM_
	//PAPER JS
		test_paper_cnt=new paper_js_gr('canvas2');//!!!
		test_paper=new paper_js_gr('canvas3');
}
