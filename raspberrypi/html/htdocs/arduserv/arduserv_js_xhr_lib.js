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
				"center_div",
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
				"xhr_status_div",
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
		sys_data=new xmlhttprq_stream_gr('/cgi-bin/sys_inf.sh',sys_stream_nmea);
		
		test_cnt_nmea = new nmea_gr(message_hub);//
		test_cnt_stream=new xmlhttprq_stream_gr('/cgi-bin/test_counter.sh',test_cnt_nmea);
	
	//PAPER JS
		test_paper_cnt=new paper_js_gr('canvas2');//!!!
		test_paper=new paper_js_gr('canvas3');
		
		//console.log(test_paper);
		//test_paper.add_obj(50,50,5);
		//test_paper.add_obj(70,70,5);
		//test_paper.add_obj(150,150,5);
		//test_paper.move();



	nmea = new nmea_gr();
	datafall = new datafall_gr();	
	xhr = new XMLHttpRequest();
	open_hendler();
}
function open_hendler(){
	xhr.open('GET', '/cgi-bin/stream_usart.sh', true);
	xhr.overrideMimeType('text/plain; charset=x-user-defined');

	xhr.onprogress=function(e){
		xhr_parse_data();
	};
	xhr.send();
}
function xhr_parse_data(){
	xhr_status_div.innerHTML='Frame size:'+(xhr.responseText.length-xhr_read_point);
	xhr_status_div.innerHTML+='<br>Buffer size:'+xhr.responseText.length;
	
	var xhr_date_old=xhr_date;
	xhr_date = new Date;
	xhr_fps=xhr_fps*0.95+(1/((xhr_date-xhr_date_old)/1000))*0.05;
	xhr_status_div.innerHTML+='<br>FPS:'+(xhr_fps.toFixed(2));
	
	xhr_bps=xhr_bps*0.95+8*((xhr.responseText.length-xhr_read_point)/((xhr_date-xhr_date_old)/1000))*0.05;
	xhr_status_div.innerHTML+='<br>BPS:'+(xhr_bps.toFixed(2));//bit per second
	
	//NMEA
		nmea.parser_data(xhr.responseText,xhr_read_point,xhr.responseText.length);//передача и обработка потока

		center_div.innerHTML="LEN:"+nmea.parser_nmea_array.length;
		for(var i=0;i<nmea.parser_nmea_array.length;i++){
			if(i==0){
				nmea_status.innerHTML="";
			}
			nmea_status.innerHTML+=i+":"+nmea.parser_nmea_array[i];
		}

		if(nmea.parser_nmea_array.length>1){
			nmea.clear_nmea_array();//удаляем прочитанные сообщения
		}
	
	//DATAFALL
		datafall.parser_data(xhr.responseText,xhr_read_point,xhr.responseText.length);//передача и обработка потока
		
		for(var i=0;i<datafall.datafall_array.length;i++){
			datafall_div.innerHTML="LEN:"+datafall.datafall_array.length+"<br>";
			datafall_div.innerHTML+=datafall.datafall_array[i];
			datafall_div.innerHTML+="<br>";
			update_graphics(2,datafall.datafall_array[i]);
		}

		if(datafall.datafall_array.length>1){
			datafall.clear_data_array();//удаляем прочитанные сообщения
		}

	//END
		xhr_read_point=xhr.responseText.length;//двигаем указатель потока
}