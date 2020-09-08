'use strict';
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//xmlhttprq_stream_gr
	/*
	!!!В случае перезагрузки потока обеспечивать сброс указателей...
	Принимает в качестве параметра(parameter) структуру:
		url:'/cgi-bin/stream_usart.sh',
		mime_type:'text/plain; charset=x-user-defined',
		status_div_name:"Arduino uart:",
		parser: autoboat,//new raw_parser_gr(message_hub),
		flush_en:true,
		auto_start:true,
		status_en:true,
		status_timer:1000,
		status_div:"xhr_status_div",
		status_div_status_css:"xmlhttprq_stream_gr_status",
		status_div_stat_css:"xmlhttprq_stream_gr_stat",
		reload_en:true,
		reload_time:1000
	Выводит статистику, обеспечивает перезагрузкуи прочие параметры для потока.
	Передает полученные данные из потока в обработчик - "parser":parameter.parser.parser_data(this.responseText);
		Функция должна сама обеспечивать обработку даннных с учетом содержания указателя на данные типа NMEA,JSON и RAW.
	В случае если сервер генирирует JSON или подобные не обходимо обеспечить автоперезагрузку потока(auto_start:true)
	*/
	class xmlhttprq_stream_gr {
		//Инициализация
			constructor(parameter) {
				//this.url=url;
				//this.parser=parser;
				var this_of_class=this;
				var this_parameter=parameter;
				this.parameter=parameter;
				this.xmlhttprq = new XMLHttpRequest();
			
				//this.xmlhttprq.open('GET', parameter.url, true);//!!!
					this.is_post=('post_data' in parameter) ? 1 : 0;
					
					
					('mime_type' 	in this.parameter) ? null : (this.parameter.mime_type='text/plain; charset=x-user-defined');
					('url_w' 		in this.parameter) ? null : (this.parameter.url_w='');
					this.is_flush_en=('flush_en' in this.parameter) ? (this.parameter.flush_en ? 1:0) : 0;
					this.is_auto_start=('auto_start' in this.parameter) ? (this.parameter.auto_start ? 1:0) : 1;	
					this.is_status_en=('status_en' in this.parameter) ? (this.parameter.status_en ? 1:0) : 0;
					this.is_reload_en=('reload_en' in this.parameter) ? (this.parameter.reload_en ? 1:0) : 0;
					this.is_timeout_en=('timeout_en' in this.parameter) ? (this.parameter.timeout_en ? 1:0) : 0;
					
					if(this.is_auto_start){
						this.open_c();
					}

					/*this.xmlhttprq.open( ((this.is_post) ? 'POST' : 'GET') , parameter.url, true);
					this.xmlhttprq.overrideMimeType(parameter.mime_type);				
					if('timeout_en'	in parameter){
						if(parameter.timeout_en){
							this.xmlhttprq.timeout = parameter.timeout_time;;
						}
					}
					this.xmlhttprq.send( ((this.is_post) ? parameter.post_data : null) );//!!!*/
				
				this.stat_bps=0;
				this.stat_rp=0;
				this.last_statusText="";
				this.last_readyState=0;
				
				if(this.is_status_en){
					this.status_div = document.createElement('div');
					this.stat_div = document.createElement('div');
					this.status_div.className = parameter.status_div_status_css;
					this.stat_div.className = parameter.status_div_stat_css;
					var main_status_div=document.createElement('div');
					main_status_div.appendChild(this.status_div);
					main_status_div.appendChild(this.stat_div);
					document.getElementById(parameter.status_div).appendChild(main_status_div);
				
					setInterval(function(){this_of_class.view_stat();},parameter.status_timer);
					
					//console.log(this.status_div);
				}
				
				this.xmlhttprq.abort=function(e){
					console.log("xmlhttprq_stream_gr:abort",this.parameter.name,e);
				}
				this.xmlhttprq.error=function(e){
					console.log("xmlhttprq_stream_gr:error",this.parameter.name,e);
				}
				
				this.xmlhttprq.onprogress=function(e){
					if(this_of_class.is_flush_en && this_of_class.xmlhttprq.readyState!=4){
						parameter.parser.parser_data(this.responseText);//!!!
					}
				}				
				
				this.xmlhttprq.onreadystatechange=function(){//this.check_stage();    
					if(this.readyState==4){//DONE
						parameter.parser.parser_data(this.responseText);//!!!
						
						this_of_class.stat_rp-=this.responseText.length;
						//console.log(e);
						if(this_of_class.is_reload_en){
							setTimeout(function(e) {this_of_class.open_c();},this_parameter.reload_time);
						}
					}
				}
				
				//this.tii=setInterval(function(){this_of_class.stat_div.innerHTML+=1},1000);

			}
		//чуть
			view_stat(){
				this.status_div.innerHTML=this.parameter.name+":";
				this.status_div.innerHTML+=""+this.xmlhttprq.statusText;
				this.status_div.innerHTML+="("+this.xmlhttprq.readyState+")";
				this.status_div.innerHTML+="  <a onclick='xhrsc.find(elem  => elem.parameter.name==\""+this.parameter.name+"\").test();'>test</a>";
				this.status_div.innerHTML+="  <a onclick='xhrsc.find(elem  => elem.parameter.name==\""+this.parameter.name+"\").close_c();'>Close</a>";
				this.status_div.innerHTML+="  <a onclick='xhrsc.find(elem  => elem.parameter.name==\""+this.parameter.name+"\").open_c();'>Open</a>";
				this.status_div.innerHTML+="  <a onclick='xhrsc.find(elem  => elem.parameter.name==\""+this.parameter.name+"\").freeze_c();'>Freeze</a>";
				this.status_div.innerHTML+="  <a onclick='xhrsc.find(elem  => elem.parameter.name==\""+this.parameter.name+"\").reload_en_inv_c();'>Reload_inv</a>";				
				
				this.stat_bps=this.stat_bps*0.95+8*((this.xmlhttprq.responseText.length-this.stat_rp)/1)*0.05;
				this.stat_rp=this.xmlhttprq.responseText.length;
				if(this.stat_bps<1000){
					this.stat_div.innerHTML='Скорость: '+(this.stat_bps.toFixed(2))+' бит/с.';//bit per second
				}else{
					this.stat_div.innerHTML='Скорость: '+((this.stat_bps/1000).toFixed(2))+' Kбит/с.';//bit per second
				}
				//console.log(this.name);
				//console.log(this_of_class);
				//console.log(this.parameter);
			}
		//чуть
			test(){
				console.log("Test;");
				return 1;
			}
			close_c(){
				this.parameter.reload_en=false;
				this.xmlhttprq.abort();
			}
			open_c(){
				this.xmlhttprq.open( ((this.is_post) ? 'POST' : 'GET') , this.parameter.url, true);
				this.xmlhttprq.overrideMimeType(this.parameter.mime_type);				
				//if('timeout_en'	in this.parameter){
					//if(this.parameter.timeout_en){
					this.xmlhttprq.timeout =(this.is_timeout_en) ? (this.parameter.timeout_time) : null;
					//}
				//}
				this.xmlhttprq.send( ((this.is_post) ? this.parameter.post_data : null) );//!!!
			}
			freeze_c(){
				this.close_c();
				setTimeout(function(e) {e.open_c();},5000,this);
			}
			reload_en_inv_c(){
				if(this.parameter.reload_en==false){
					this.parameter.reload_en==true;
				}else{
					this.parameter.reload_en==false;
				}
			}
			//close()//stop()
			//open()//start()
			//freeze()
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class web_sock_stream_gr {
	//Инициализация
		constructor(parameter) {
			if (typeof MozWebSocket == 'function'){//type def for wat?wtf
					WebSocket = MozWebSocket;
			}
			
			var this_of_class=this;
			var this_parameter=parameter;
			this.parameter=parameter;
			this.websocket = null;
			
			this.wsUri = this.parameter.url;//"ws://192.168.0.101:3129/dev/gps/r";
			this.websocket = null;
			
			this.open_c(this);
		}
	//123
		open_c(e){
			if ( this.websocket && this.websocket.readyState == 1 ){
				this.websocket.close();
			}
			
			this.websocket = new WebSocket( this.wsUri );
			this.websocket.onopen = function (evt) {
				console.log("CONNECTED");
			};
			
			this.websocket.onclose = function (evt) {
				console.log("DISCONNECTED");
				if(e.parameter.reload_en){
					setTimeout(function() {e.open_c(e);},e.parameter.reload_time);
				}
			};
			
			this.websocket.onerror = function (evt) {
				console.log('ERROR: ' + evt.data);
				if(e.parameter.reload_en){
					setTimeout(function() {e.open_c(e);},e.parameter.reload_time);
				}
			};
			
			this.websocket.onmessage = function (evt) {
				e.parameter.parser.parser_data(evt.data);
			};
		}
	//
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
