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

var hystory_load=function(stream){
	var options_id=document.getElementById('terminal_history').options;
	for(var i=0;i<stream.length;i++){
		var newOption = new Option(stream[i], "");
		document.getElementById('terminal_history').options[i]=newOption;
	}
	document.getElementById('terminal_addr').value=stream[0];
}
var get_history=function(){
	new single_shot_gr({url:"http://localhost:3128/htdocs/db/terminal/history.json",callback:hystory_load });
}

function terminal_addr_change(){
	var options_id=document.getElementById('terminal_history').options;
	document.getElementById('terminal_addr').value=options_id[options_id.selectedIndex].text;
}

var hystory_save=function(stream){
	var options_id=document.getElementById('terminal_history').options;
	var N=options_id.length;
	var arr=new Array();
	arr[0]=document.getElementById('terminal_addr').value;
	for(var i=0;i<N;i++){
		arr[i+1]=document.getElementById('terminal_history').options[i].text;
	}
	console.log(arr);
	bubble_sort(arr);
	new singl_shot_send_gr({url:"http://localhost:3128/db/w/terminal/history.json",data:JSON.stringify(arr),callback:get_history });
}


function terminal_open(){
	hystory_save();
	try{socket.stop();}catch(exception){}

	terminal_stream_param={
		url			: document.getElementById('terminal_addr').value,
		//url		:	,//"ws://127.0.0.1:3129/sys/gen/",
		//url		:	"ws://127.0.0.1:3129/sys/gen/1000/cnt/10",
		//parser	:	new nt_json_stream_gr(serial_list,{collected:1}),
		parser	:	terminal,// //new nt_json_gr(serial_list,{collected:0}),

		auto_start:true,

		reload_en:true,
		reload_time:1000
	}

	socket=new web_sock_stream_gr(terminal_stream_param);
	terminal.add_socket(socket);

}
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
function main_init(){
		terminal=new terminal_gr();
	//load history
		//new single_shot_gr({url:"http://localhost:3128/htdocs/db/terminal/history.json",callback:hystory_load });
		get_history();
	//

}
