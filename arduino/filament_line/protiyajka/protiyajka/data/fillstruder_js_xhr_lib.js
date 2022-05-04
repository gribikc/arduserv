var config=new Object();
	//////////////////////////////////////////////
	config['dev_name']='HC-08';
	config['remoute_serv_ip']='192.168.0.108';//'192.168.1.44';//192.168.0.138//192.168.3.176//172.20.10.2
	config['remoute_serv_port']='80';
	//////////////////////////////////////////////
	config['dev_url']=	 (document.location.protocol=="file:") ? ("http://"+config['remoute_serv_ip']+":"+config['remoute_serv_port']) : "" ,
	//////////////////////////////////////////////
	//config['auto_move_map_to_boat']=true;
	config['map']=new Object();
	config['map']['auto_move_map_to_boat']=true;
	config['map']['point_of_position']=300;
	//////////////////////////////////////////////
	config['ssf']=false;
	
	wpp_gr.web_server_def	=config['dev_url'];
	wpp_gr.data_server_def	=config['dev_url'];
	wpp_gr.db_server_def	=config['dev_url'];
	wpp_gr.db_read_prefix="/db/";// esp32:"/db/",CTW:"/htdocs/db/"
	wpp_gr.db_write_prefix="/db/w/";

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//$(document).ready(function(){
var	prog;//=new izm_gr();
function main_init(){
	prog=new izm_gr();
	//_HUB
	//STREAM
		//
			bap_uart_stream_param={
				url   : config['dev_url']+"/status", //config['dev_url'],
				url_w : config['dev_url']+"/status",
				mime_type:'text/plain; charset=x-user-defined',
				name:"BAP:",
				//parser: autoboat,//new raw_parser_gr(message_hub),
				parser: new nt_json_gr(prog),
				
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
		//

	//_STREAM
	//PAPER JS
		//test_paper_cnt=new paper_js_gr('canvas2');//!!!
		//test_paper=new paper_js_gr('canvas3');
		
		
	generate_show_hide_menu_from_div('main_wiev_div','main_list_of_all');
	create_table_from_array_gr(config,'main_div_setings');
}
