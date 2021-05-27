//'use strict';
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//$(document).ready(function(){
//terminal=new terminal();
let terminal=new Object();
let socket=new Object();
let hystory_db=new Object();

////////////////////////////////////
	var hystory_save=function(stream){
		var options_id=document.getElementById('terminal_history').options;
		var N=options_id.length;
		var arr=new Array();
		arr[0]=document.getElementById('terminal_addr').value;
		for(var i=0;i<N;i++){
			arr[i+1]=document.getElementById('terminal_history').options[i].text;
		}
		bubble_sort(arr);
		//new singl_shot_send_gr({url:"http://localhost:3128/db/w/terminal/history.json",data:JSON.stringify(arr),callback:get_history });
		hystory_db.save({arr:arr});
		//console.log(arr);
	}
	//
	var on_hystory_load=function(stream){
		var options_id=document.getElementById('terminal_history').options;
		for(var i=0;i<stream.length;i++){
			var newOption = new Option(stream[i], "");
			document.getElementById('terminal_history').options[i]=newOption;
		}
		document.getElementById('terminal_addr').value=stream[0];
		//console.log(stream);
	}
	//
	var on_hystory_save=function(){
		hystory_db.load();
	}
//////////////////////////////////

function terminal_addr_change(){
	var options_id=document.getElementById('terminal_history').options;
	document.getElementById('terminal_addr').value=options_id[options_id.selectedIndex].text;
}

function terminal_open(){
	hystory_save();
	try{socket.stop();}catch(exception){}

	terminal_stream_param={
		url			: document.getElementById('terminal_addr').value,//"ws://127.0.0.1:3129/sys/gen/",
		parser	:	terminal,// //new nt_json_gr(serial_list,{collected:0}),
		auto_start:true,
		reload_en:true,
		flush_en:true,
		//mime_type:'text/plain; charset=x-user-defined',
		reload_time:1000
	}
	
	new xmlhttprq_stream_gr(terminal_stream_param);//http://127.0.0.1:3128/sys/gen/1000/bin/

	//socket=new web_sock_stream_gr(terminal_stream_param);
	//terminal.add_socket(socket);

}

function terminal_chvin(){
	terminal.change_view();
}
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
function main_init(){
		hystory_db=new db_query_gr({db_name:"terminal",table_name:"history",on_save:on_hystory_save,on_load:on_hystory_load});
		hystory_db.load();
		terminal=new terminal_gr();
}
