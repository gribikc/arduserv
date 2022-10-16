'use strict';
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class eeprom_gr{
		//Инициализация
		constructor(param){
			this.param=param;
			new single_shot_gr({url:config['dev_url']+"/eeprom_read",callback:new nt_json_gr(this) });
		}
		
		//////////
		parser_data(stream){
			//console.log(this.param);
			document.getElementById(this.param.div).innerHTML="";
			create_tree_form_from_array_gr(stream,document.getElementById(this.param.div),0);
			
			//new single_shot_gr({url:config['dev_url']+"/eeprom_read",callback:this });
			/*eeprom_stream_param={
				url   : config['dev_url']+"/eeprom_read",
				url_w : config['dev_url']+"/eeprom_write",
				mime_type:'text/plain; charset=x-user-defined',
				name:"EEPROM:",

				parser: new nt_json_gr(this),
				
				flush_en:false,
				auto_start:true,
				
				status_en:false,
				
				reload_en:false,
				reload_time:1000
			};
			new xmlhttprq_stream_gr(eeprom_stream_param);*/
		}
		
		//////////
		error_event(message){
			console.log(message+'');
		}

	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class izm_gr{
		//Инициализация
		constructor(){
			this.data_plotly= [
			  {
				x: [],
				y: [],
				type: 'scatter'
			  }
			];

			this.speedometr={time:0,cnt:0,speed:0};
			
			this.array=[];
			this.cnt=1;
			this.izm_stat={min:-10000,max:100000,avg:0};
		}
		
		//////////
		parser_data(stream){
			//console.log(stream+'123');
			//this.array=this.array.concat(stream);
			//this.intervalID = setInterval(this.myCallback, 1000/(this.array.length+1), this);
			//mma_izm

			var time=performance.now();
			if(stream.length>0){
				this.speedometr.cnt+=stream.length;
				if(this.speedometr.cnt>10){
					if(this.speedometr.time!=0){
						this.speedometr.speed=1000*this.speedometr.cnt/(time-this.speedometr.time);
					}
					
					this.speedometr.time=time;
					this.speedometr.cnt=0;
				}

			}

			
			for(var i=0;i<stream.length;i++){//обработка данных для статистики и графика
				this.data_plotly[0].y.push(stream[i]);
				this.data_plotly[0].x.push(this.cnt++);
				
				this.cnt++;
				if(this.izm_stat.min>stream[i] || this.izm_stat.min<=-10000){
					this.izm_stat.min=stream[i];
				}
				if(this.izm_stat.max<stream[i] || this.izm_stat.max>=100000){
					this.izm_stat.max=stream[i];
				}
				this.izm_stat.avg=this.izm_stat.avg*0.999+stream[i]*0.001
			}
			
			if(this.data_plotly[0].y.length>2000){//обрезаем лишнее
				this.data_plotly[0].y.splice(0,this.data_plotly[0].y.length);
				this.data_plotly[0].x.splice(0,this.data_plotly[0].x.length);
			}

			document.getElementById("mma_izm").innerHTML="тек:"+stream[stream.length-1]+"<br>мин: "+this.izm_stat.min+"<br>срд: "+this.izm_stat.avg+"<br>мак: "+this.izm_stat.max+"<br>ips:"+this.speedometr.speed;

			Plotly.newPlot('linechart_izm', this.data_plotly);

		}
		
		//////////
		error_event(message){
			console.log(message+'');
		}

	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class pid_gr{
	//Инициализация
	constructor(){
		this.data_plotly= [
		  {
			x: [],
			y: [],
			type: 'scatter'
		  }
		];
		
		this.speedometr={time:0,cnt:0,speed:0};
		
		this.cnt=1;
	}
	
	//////////
	parser_data(stream){		
		for(var i=0;i<stream.length;i++){
			this.data_plotly[0].y.push(stream[i]);
			this.data_plotly[0].x.push(this.cnt++);
			this.cnt++;
		}
		if(this.data_plotly[0].y.length>2000){
			this.data_plotly[0].y.splice(0,this.data_plotly[0].y.length);
			this.data_plotly[0].x.splice(0,this.data_plotly[0].x.length);
		}
		
		Plotly.newPlot('linechart_pid_div', this.data_plotly);
	}

	//////////
	error_event(message){
		console.log(message+'');
	}

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	function send_form_data(url,form_name,array){
		let formData;
		if(form_name!=""){
			formData = new FormData(document.getElementById(form_name));
		}else{
			formData = new FormData();
		}
		for(var index in array){
			formData.append(index, array[index]);
			//console.log(index+":"+array[index]);
		}

		var xmlhttprq_test = new XMLHttpRequest();
		
		if(document.location.protocol=="file:"){
			url="http://"+config['remoute_serv_ip']+":"+config['remoute_serv_port']+url;
		}
		
		var type_xnr="POST";
		if(array==""){///!!!
			type_xnr="GET";
		}
		
		xmlhttprq_test.open(type_xnr, url, true);//, true
		//xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
		//xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		xmlhttprq_test.send(formData);
	}
	

	function autoboat_save_settings_send_db(){
		var xmlhttprq_test = new XMLHttpRequest();
		xmlhttprq_test.open('POST', 'http://192.168.0.131/w/db/autoboat/config.json', true);//, true
		xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
		xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		xmlhttprq_test.send(JSON.stringify(auto_boat_config));
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	function test_send_data1(){
		var xmlhttprq_test = new XMLHttpRequest();
		xmlhttprq_test.open('POST', 'http://192.168.0.131/write?get_par0=123&get_par1=456&get_par2=789', true);//, true
		//xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
		//xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		//xmlhttprq_test.setRequestHeader('Content-Type', 'multipart/form-data;boundary="boundary"');
		//xmlhttprq_test.setRequestHeader('Content-Type', 'multipart/form-data;');
		//xhr.setRequestHeader("Content-Type", "text/plain;charset=UTF-8"); 
		//xhr.setRequestHeader('Content-Type', 'application/json');
		var uint8 = new Uint8Array(9);
		uint8[0] = 0;
		uint8[1] = 10;
		uint8[2] = 20;
		uint8[3] = 30;
		uint8[4] = 0;
		uint8[5] = 100;
		uint8[6] = 200;
		uint8[7] = 33;
		uint8[8] = 44;
		//let hello = new Uint8Array([72, 101, 108, 108, 111]); // "hello" в бинарной форме
		//let blob = new Blob([uint8, ' ', 'world'], {type: 'text/plain'});//text/plain
		//var a=uint8;
		var a=uint8.toString(10).toUpperCase();
		//var params = encodeURIComponent(uint8);
		xmlhttprq_test.send(a);//uint8//blob
		//!!!xmlhttprq_test.abort();
		//xmlhttprq_test.send();
	}	