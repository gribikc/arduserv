'use strict';
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class eeprom_gr{
		//Инициализация
		constructor(param){//конструктор должен принимать обьект див или его id
			this.param=param;
			
			if(typeof this.param.div == "string"){
				this.main_div_element=document.getElementById(this.param.div);
				this.full_div_patch=this.param.div;//сделать рекурсивный путь до документ!!!
			}else{//доделать
				this.main_div_element=this.param.div;
				this.full_div_patch=this.main_div_element.id;
			}

			this.global=find_father(eeprom_gr,function() {return window[member].param.div==this.dataset.keyname;});
			
			//Create HTML
				this.div_button = document.createElement("div");
				this.main_div_element.appendChild(this.div_button);

				this.div_form = document.createElement("div");
				this.main_div_element.appendChild(this.div_form);

				//Запросить
				this.upd_button = document.createElement("input");
				this.upd_button.type="button";
				this.upd_button.value="Запросить";
				this.upd_button.dataset.keyname=this.full_div_patch;
				this.upd_button.onclick = function() {
					var father=find_father(eeprom_gr,function() {return window[member].full_div_patch==this.dataset.keyname;});
					if(father){
						father[0].update_data();
					}
				};
				this.div_button.appendChild(this.upd_button);
				
				//Установить
				this.save_button = document.createElement("input");
				this.save_button.type="button";
				this.save_button.value="Установить и Сохранить";
				this.save_button.dataset.keyname=this.full_div_patch;
				this.save_button.onclick = function() {
					var father=find_father(eeprom_gr,function() {return window[member].full_div_patch==this.dataset.keyname;});
					if(father){
						father[0].save_data();
					}
				};
				this.div_button.appendChild(this.save_button);

				//Сброс
				this.save_button = document.createElement("input");
				this.save_button.type="button";
				this.save_button.value="Сброс EEPROM";
				this.save_button.dataset.keyname=this.full_div_patch;
				this.save_button.onclick = function() {
					var father=find_father(eeprom_gr,function() {return window[member].full_div_patch==this.dataset.keyname;});
					if(father){
						father[0].reset_eeprom();
					}
				};
				this.div_button.appendChild(this.save_button);

				//

			//END Create HTML

			this.update_data();
		}
		reset_eeprom(){
			new single_shot_gr({url:config['dev_url']+"/eeprom_reset"});
		}

		update_data(message){
			new single_shot_gr({url:config['dev_url']+"/eeprom_read",callback:new nt_json_gr(this) });
		}

		save_data(){
			var arr=create_array_from_form_gr(this.div_form)

			var formData = new FormData();
			for(var index in arr){
				formData.append(index, arr[index]);
			}

			//тут передаемь обьект с обьектом...!!!
			new singl_shot_send_gr({url:config['dev_url']+"/eeprom_write",data:formData,callback:{
					parser_data:function(message) {this.thather.on_save_data(message)},
					thather:this
				}});
				
			/*new singl_shot_send_gr({url:config['dev_url']+"/eeprom_write",
					callback:() => {
						console.log(this); // `this` указывает на объект Person
					}	
			});*/
		}

		on_save_data(message){
			console.log("Data save");
		}

		parser_data(stream){
			this.div_form.innerHTML="";
			create_tree_form_from_array_gr(stream,this.div_form,0);
		}

		error_event(message){
			console.log(this);
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

			Plotly.newPlot('linechart_izm', this.data_plotly);;
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
				
				if(this.izm_stat.min>stream[i] || this.izm_stat.min<=-10000){
					this.izm_stat.min=stream[i];
				}
				if(this.izm_stat.max<stream[i] || this.izm_stat.max>=100000){
					this.izm_stat.max=stream[i];
				}
				this.izm_stat.avg=this.izm_stat.avg*0.999+stream[i]*0.001
			}
			
			if(this.data_plotly[0].y.length>2000){//обрезаем лишнее
				this.data_plotly[0].y.splice(0,this.data_plotly[0].y.length-2000);
				this.data_plotly[0].x.splice(0,this.data_plotly[0].x.length-2000);
			}

			document.getElementById("mma_izm").innerHTML=	"тек:"+stream[stream.length-1]+
														"<br>мин: "+this.izm_stat.min+
														"<br>срд: "+this.izm_stat.avg+
														"<br>мак: "+this.izm_stat.max+
														"<br>ips:"+this.speedometr.speed;

			//Plotly.newPlot('linechart_izm', this.data_plotly);
			Plotly.redraw('linechart_izm');

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
		Plotly.newPlot('linechart_pid_div', this.data_plotly);
	}
	
	//////////
	parser_data(stream){		
		for(var i=0;i<stream.length;i++){
			this.data_plotly[0].y.push(stream[i]);
			this.data_plotly[0].x.push(this.cnt++);
		}
		if(this.data_plotly[0].y.length>2000){
			this.data_plotly[0].y.splice(0,this.data_plotly[0].y.length-2000);
			this.data_plotly[0].x.splice(0,this.data_plotly[0].x.length-2000);
		}
		
		//Plotly.newPlot('linechart_pid_div', this.data_plotly);
		Plotly.redraw('linechart_pid_div');
	}

	//////////
	error_event(message){
		console.log(message+'');
	}

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class read_state_gr{
	//Инициализация
	constructor(){
		this.update_data();
	}
	
	//////////
	parser_data(stream){		
		console.log(stream);
		document.getElementById("set_diametr_val").value=	stream.diametr;
		document.getElementById("set_iad_val").value=		stream.iad;
		document.getElementById("pid_kp").value=		stream.pid_kp;
		document.getElementById("pid_kd").value=		stream.pid_kd;
		document.getElementById("set_mot_speed").value=	stream.Mot_speed;
	}
	
	///////////
	update_data(message){
		new single_shot_gr({url:config['dev_url']+"/get_cur_settings",callback:new nt_json_gr(this) });
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