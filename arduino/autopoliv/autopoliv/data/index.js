	var prog;
///////////////////////////////////////////////////////////
var config=new Object();
	//////////////////////////////////////////////
	config['remoute_serv_ip']='192.168.0.108';//'192.168.1.44';
	config['remoute_serv_port']=80;
	//////////////////////////////////////////////
	config['dev_url']=		( (document.location.protocol=="file:" ? "http://"+config['remoute_serv_ip'] : "" ) );
	config['dev_url_w']=	( (document.location.protocol=="file:" ? "http://"+config['remoute_serv_ip'] : "" ) );
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//$(document).ready(function(){
function main_init(){
	prog=prog=new tr_gr();
	//_HUB
	//STREAM
		//arduino_uart
			bap_uart_stream_param={
				url   : config['dev_url']+"/status",//'http://192.168.0.131/status', //config['dev_url'],
				url_w : config['dev_url_w']+"/write",//'http://192.168.0.131/write',
				mime_type:'text/plain; charset=x-user-defined',
				name:"BAP:",
				parser: new nt_json_gr(prog),//new json_parser_gr(prog),
				
				flush_en:false,
				auto_start:true,
				
				status_en:false,
				status_timer:1000,
				status_div:"xhr_status_div",
				status_div_status_css:"xmlhttprq_stream_gr_status",
				status_div_stat_css:"xmlhttprq_stream_gr_stat",
				
				reload_en:true,
				reload_time:1000
			};
			new xmlhttprq_stream_gr(bap_uart_stream_param);//'/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112
		//_arduino_uart
	//_STREAM
	//PAPER JS
		//test_paper_cnt=new paper_js_gr('canvas2');//!!!
		//test_paper=new paper_js_gr('canvas3');
		
		
	generate_show_hide_menu_from_div('main_wiev_div','main_list_of_all');
	create_table_from_array_gr(config,'main_div_setings');
}
