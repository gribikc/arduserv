var config=new Object();
	//////////////////////////////////////////////
	config['dev_name']='HC-08';
	config['remoute_serv_ip']='prot';//'192.168.1.44';//192.168.0.138//192.168.3.176//172.20.10.2
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
var pid_data;
var eeprom;
function main_init(){
	prog=new izm_gr();
	pid_data=new pid_gr();
	eeprom=new eeprom_gr({div:"eeprom_edit_div"});
	//_HUB
	//STREAM
		//
			izm_stream_param={
				url   : config['dev_url']+"/get_izm_data",
				url_w : config['dev_url']+"/get_izm_data",
				mime_type:'text/plain; charset=x-user-defined',
				name:"IZM:",

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
			new xmlhttprq_stream_gr(izm_stream_param);
		//
			pid_stream_param={
				url   : config['dev_url']+"/get_pid_data",
				url_w : config['dev_url']+"/get_pid_data",
				mime_type:'text/plain; charset=x-user-defined',
				name:"PID:",

				parser: new nt_json_gr(pid_data),
				
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
			new xmlhttprq_stream_gr(pid_stream_param);
		//
	//_STREAM		
		
	generate_show_hide_menu_from_div('main_wiev_div','main_list_of_all');
	//create_table_from_array_gr(config,'main_div_setings');
}
