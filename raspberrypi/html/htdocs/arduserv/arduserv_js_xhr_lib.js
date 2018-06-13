let nmea;// = new nmea_gr();
let datafall;// = new datafall_gr();
let sys_data;//=new xmlhttprq_stream_gr();
let message_db;

var xhr;// = new XMLHttpRequest();
var xhr_read_point=0;
var xhr_date = new Date;
var xhr_fps=0;
var xhr_bps=0;
var xhr_temp;

var message_parsing_array=new Array();
message_parsing_array.push([{type:"nmea"},{mark:"$SYST0"},{inner:"center_div"}]);
//var arr = [ 1, 'Имя', { name: 'Петя' }, true ];

function main_init(){
	message_hub=new valid_db_gr(message_parsing_array);

	nmea = new nmea_gr(message_hub);
	datafall = new datafall_gr();
	
	sys_stream_nmea = new nmea_gr();
	sys_data=new xmlhttprq_stream_gr('/cgi-bin/sys_inf.sh',sys_stream_nmea);
	
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