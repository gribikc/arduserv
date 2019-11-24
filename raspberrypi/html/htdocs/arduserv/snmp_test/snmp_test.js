let xhrsc=[];
			/////rfc1592
			/////       _______        ________________
			///// 0  1  2  3  4  5  6  7  8  9 10 11 12 
			/////F1 L1 T1 L2  V T2 L3  P  u  b  l  i  c                                     
var snmp_q_t = 	"30 33 02 01 01 04 06 70 75 62 6c 69 63 "+
			/////13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
			/////A0 Lx ________                            _____ _____ _____
				"a0 26 02 04 5d d6 91 4a 02 01 00 02 01 00 30 18 30 16 06 12 "+
			/////xx. 6. 1. 4. 1.
				"2b 06 01 04 01 81 b7 58 87 69 70 50 bf 10 81 53 01 00 "+
			/////NLV
				"05 00";//parseInt(hexString, 16);
	snmp_q_t=snmp_q_t.split(' ');
	var snmp_q_t_arr=new Uint8Array(snmp_q_t.length);
	for(var i=0;i<snmp_q_t.length;i++){
		snmp_q_t_arr[i]=parseInt(snmp_q_t[i],16);
	}
console.log(snmp_q_t_arr);
function main_init(){
	//////////////////////////////
		simple_test_stream_param={//location.hostname
			//url   : (document.location.protocol=="file:" ? "http://172.18.26.112:3128" : "" ) +"/dev/com/r/34/115200", //(document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/R/COM/28/57600/',//'http://localhost:3128/R/COM/28/57600/',//'http://192.168.0.122:3128/R/BT/HC-06/',//http://172.20.10.4:3128/R/BT/HC-06///http://192.168.0.122:3128/R/BT/HC-06/',//'/cgi-bin/stream_usart.sh',
			//url   : "http://127.0.0.1:3128/htdocs/db/test/fname_2.json",
			url   : "http://127.0.0.1:3128/sys/udp/127.0.0.1/161/",
			url_w : "127.0.0.1:3128/W/GPS/",//(document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/W/COM/28/57600/',//'http://localhost:3128/W/COM/28/57600/',
			mime_type:'text/plain; charset=x-user-defined',
			post_data:snmp_q_t_arr,
			name:"DB",
			//parser: new json_stream_parser_gr(simple_test_gr),//new raw_parser_gr(message_hub),
			  parser: new snmp_test_gr(),
			
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
	//////////////////////////////////////////////////////////////////
}