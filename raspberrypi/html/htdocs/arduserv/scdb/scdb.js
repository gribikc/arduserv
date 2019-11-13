let xhrsc=[];

function main_init(){
	
	//////////////////////////////
		simple_test_stream_param={//location.hostname
			//url   : (document.location.protocol=="file:" ? "http://172.18.26.112:3128" : "" ) +"/dev/com/r/34/115200", //(document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/R/COM/28/57600/',//'http://localhost:3128/R/COM/28/57600/',//'http://192.168.0.122:3128/R/BT/HC-06/',//http://172.20.10.4:3128/R/BT/HC-06///http://192.168.0.122:3128/R/BT/HC-06/',//'/cgi-bin/stream_usart.sh',
			url   : "http://172.18.26.112:3128/htdocs/db/test/fname.json",
			
			url_w : "127.0.0.1:3128/W/GPS/",//(document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/W/COM/28/57600/',//'http://localhost:3128/W/COM/28/57600/',
			mime_type:'text/plain; charset=x-user-defined',
			name:"DB",
			//parser: new json_stream_parser_gr(simple_test_gr),//new raw_parser_gr(message_hub),
			  parser: new json_parser_gr(new scdb_gr(0,'tbl_db')),
			
			flush_en:false,
			auto_start:true,
			
			status_en:true,
			status_timer:1000,
			status_div:"sys_status",
			status_div_status_css:"xmlhttprq_stream_gr_status",
			status_div_stat_css:"xmlhttprq_stream_gr_stat",
			
			reload_en:false,
			reload_time:1000
		};
		xhrsc.push(new xmlhttprq_stream_gr(simple_test_stream_param));
		
		simple_test_stream_param2={//location.hostname
			//url   : (document.location.protocol=="file:" ? "http://172.18.26.112:3128" : "" ) +"/dev/com/r/34/115200", //(document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/R/COM/28/57600/',//'http://localhost:3128/R/COM/28/57600/',//'http://192.168.0.122:3128/R/BT/HC-06/',//http://172.20.10.4:3128/R/BT/HC-06///http://192.168.0.122:3128/R/BT/HC-06/',//'/cgi-bin/stream_usart.sh',
			url   : "http://172.18.26.112:3128/htdocs/db/test/fname_2.json",
			
			url_w : "127.0.0.1:3128/W/GPS/",//(document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/W/COM/28/57600/',//'http://localhost:3128/W/COM/28/57600/',
			mime_type:'text/plain; charset=x-user-defined',
			name:"DB",
			//parser: new json_stream_parser_gr(simple_test_gr),//new raw_parser_gr(message_hub),
			  parser: new json_parser_gr(new scdb_gr(0,'tbl_db2')),
			
			flush_en:false,
			auto_start:true,
			
			status_en:true,
			status_timer:1000,
			status_div:"sys_status",
			status_div_status_css:"xmlhttprq_stream_gr_status",
			status_div_stat_css:"xmlhttprq_stream_gr_stat",
			
			reload_en:false,
			reload_time:1000
		};
		//xhrsc.push(new xmlhttprq_stream_gr(simple_test_stream_param2));
	//////////////////////////////////////////////////////////////////
}