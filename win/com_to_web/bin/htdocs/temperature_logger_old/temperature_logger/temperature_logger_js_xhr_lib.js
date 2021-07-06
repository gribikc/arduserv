
let xhrsc=[];



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////	
//1.3.6.1.4.1.23512.1001.112.2.4.0 -прочитать состав
//1.3.6.1.4.1.23512.1001.112.2.3.0 -записать dev_id и прочитать режим его работы
//1.3.6.1.4.1.23512.1001.112.9.4.0 -записать dev_id,channel_id и прочитать состояние демодулятора
var oid_arr=new Object();
	oid_arr['temperature']=new Object();
	oid_arr['temperature']['oid']="1.3.6.1.4.1.23512.1001.112.80.8080.211.1.0";
	oid_arr['temperature']['type']="RO";
	
	oid_arr['sostav']=new Object();
	oid_arr['sostav']['oid']="1.3.6.1.4.1.23512.1001.112.2.4.0";
	oid_arr['sostav']['type']="RO";

	oid_arr['dev_work_mode']=new Object();
	oid_arr['dev_work_mode']['oid']="1.3.6.1.4.1.23512.1001.112.2.3.0";
	oid_arr['dev_work_mode']['type']="RW";
	oid_arr['dev_work_mode']['req_arr']=new Object();
	oid_arr['dev_work_mode']['req_arr']['dev_id']=0;
	
	oid_arr['demod_state']=new Object();
	oid_arr['demod_state']['oid']="1.3.6.1.4.1.23512.1001.112.9.4.0";
	oid_arr['demod_state']['type']="RW";
	oid_arr['demod_state']['req_arr']=new Object();
	oid_arr['demod_state']['req_arr']['dev_id']=0;
	oid_arr['demod_state']['req_arr']['channel_id']=0;
	
	//1.3.6.1.4.1.23512.1001.112.9.1.0
	
	
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
	function test_send_data1(id){
		xmlhttprq_test = new XMLHttpRequest();
		xmlhttprq_test.open('POST', 'http://127.0.0.1:3128/dev/com/w/8/115200', true);//, true
		xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
		xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		var uint8 = new Uint8Array(64);
		uint8[0] = 0xAB;
		uint8[1] = 0xCD;
		uint8[2] = id;
		for(var i=3;i<61;i++){
			uint8[i]=0;
		}
		uint8[62] = 0xEF;
		uint8[63] = 0x2A;
		xmlhttprq_test.send(uint8);
		//!!!xmlhttprq_test.abort();
		//xmlhttprq_test.send();
	}	
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//$(document).ready(function(){
function main_init(){
	//STREAM
		//arduino_uart
			termo_and_pressure={//location.hostname
				url   : (document.location.protocol=="file:" ? "http://127.0.0.1:3128" : "" ) +"/dev/com/r/6/115200", //(document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/R/COM/28/57600/',//'http://localhost:3128/R/COM/28/57600/',//'http://192.168.0.122:3128/R/BT/HC-06/',//http://172.20.10.4:3128/R/BT/HC-06///http://192.168.0.122:3128/R/BT/HC-06/',//'/cgi-bin/stream_usart.sh',
				//url   : (document.location.protocol=="file:" ? "http://127.0.0.1:3128" : "" ) +"/dev/bt/r/grardusand/",
				//url:"http://192.168.0.100:3128/dev/bt/r/grardusand/",
				url_w : "127.0.0.1:3128/W/GPS/",//(document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/W/COM/28/57600/',//'http://localhost:3128/W/COM/28/57600/',
				mime_type:'text/plain; charset=x-user-defined',
				name:"SP",
				//parser: new json_stream_parser_gr(simple_test_gr),//new raw_parser_gr(message_hub),
				  parser: new json_stream_parser_gr(new arduino_termo_pressure_gr()),
				
				flush_en:true,
				auto_start:true,
				
				status_en:false,
				status_timer:1000,
				status_div:"xhr_status_div",
				status_div_status_css:"xmlhttprq_stream_gr_status",
				status_div_stat_css:"xmlhttprq_stream_gr_stat",
				
				reload_en:true,
				reload_time:1000
			};
			xhrsc.push(new xmlhttprq_stream_gr(termo_and_pressure));//'/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112
		//_arduino_uart
	///////////////////
	///////////////////
		//xhrsc.push(new xmlhttprq_stream_gr(new get_temperature_request_param('P107',"/sys/udp/172.18.26.107/161/",'test_sh0',{}).params));
		//xhrsc.push(new xmlhttprq_stream_gr(new get_temperature_request_param('P122',"/sys/udp/172.18.26.122/161/",'test_sh1',{}).params));
		//xhrsc.push(new xmlhttprq_stream_gr(new get_temperature_request_param('P118',"/sys/udp/172.18.26.118/161/",'test_sh2',{}).params));
		//xhrsc.push(new xmlhttprq_stream_gr(new get_temperature_request_param('P230',"/sys/udp/192.168.27.230/161/",'test_sh3',{}).params));
		//xhrsc.push(new xmlhttprq_stream_gr(new get_temperature_request_param('P239',"/sys/udp/192.168.27.239/161/",'test_sh4',{}).params));
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*var que_arr=new Object();
			que_arr['dev_id']=5;
		new xmlhttprq_stream_gr(new set_snmp_param("/sys/udp/192.168.27.230/161/",oid_arr['dev_work_mode']['oid'],que_arr,new array_to_to_to_gr()).params);
		/////////////////////////////////////////////////////////////////
		setTimeout(function() {
				new xmlhttprq_stream_gr(new get_snmp_param("/sys/udp/192.168.27.230/161/",oid_arr['dev_work_mode']['oid'],new array_data_to_log_gr()).params);
			},1000);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		var que_arr=new Object();
			que_arr['dev_id']=5;
			que_arr['channel_id']=0;
		new xmlhttprq_stream_gr(new set_snmp_param("/sys/udp/192.168.27.230/161/",oid_arr['demod_state']['oid'],que_arr,new array_to_to_to_gr()).params);
		/////////////////////////////////////////////////////////////////
		setTimeout(function() {
				new xmlhttprq_stream_gr(new get_snmp_param("/sys/udp/192.168.27.230/161/",oid_arr['demod_state']['oid'],new array_data_to_log_gr()).params);
			},1000);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		new xmlhttprq_stream_gr(new get_snmp_param("/sys/udp/192.168.27.230/161/",oid_arr['sostav']['oid'],new array_data_to_log_gr()).params);*/
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//var que_arr=new Object();
		//que_arr['dev_id']=5;
		//new set_get_snmp("/sys/udp/192.168.27.230/161/",oid_arr['dev_work_mode']['oid'],que_arr,new array_data_to_log_gr());
		//
		//var que_arr=new Object();
		//que_arr['dev_id']=5;
		//que_arr['channel_id']=0;
		//new set_get_snmp("/sys/udp/192.168.27.230/161/",oid_arr['demod_state']['oid'],que_arr,new array_data_to_log_gr());
		//
		//new xmlhttprq_stream_gr(new get_snmp_param("/sys/udp/192.168.27.230/161/",oid_arr['sostav']['oid'],new array_data_to_log_gr()).params);
}
