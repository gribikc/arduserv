'use strict';
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//autoboat
	class tr_gr{
		//Инициализация
		constructor(){

		}
		//////////
		parser_data(stream){
			//console.log(stream);
			if(stream['fix']==0){return;}
			key_array_to_inner(stream,'main_div_status');
		}
		error_event(message){
			console.log(message+'tr_gr');
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//autoboat
	class GR_rasspisanie{
		//Инициализация
		constructor(id){
			this.this=this;
			this.main_div=document.getElementById(id);
			this.create_form_for_new();
		}
		
		create_form_for_new(){//Время: 12:30 Длительность: 5мин. Повтор:ПН ВТ СР ЧТ ПТ СБ ВС
			this.form_m=document.createElement('FORM');
	
			this.main_div.appendChild(this.form_m);
			
				this.form_m.innerHTML+="Время: "
					var selecthour = document.createElement("select");
					this.form_m.appendChild(selecthour);
					selecthour.name="hour";
					for (var i = 0; i <= 23; i++) {
						var option = document.createElement("option");
						option.value = i;
						option.text = i;
						selecthour.appendChild(option);
					}
					//selecthour[3].selected=true;
					this.form_m.innerHTML+=" час.<br>"
					
				this.form_m.innerHTML+=" Длительность:"
					var selectlong = document.createElement("select");
					this.form_m.appendChild(selectlong);
					selectlong.name="dura";
					for (var i = 1; i <= 59; i++) {
						var option = document.createElement("option");
						option.value = i;
						option.text = i;
						selectlong.appendChild(option);
					}
					this.form_m.innerHTML+=" мин.<br>"
					
				this.form_m.innerHTML+=" Повторять:"
					var days=['ПН','ВТ','СР','ЧТ','ПТ','СБ','ВС',];
					for(var i=0;i<7;i++){
						this.form_m.innerHTML+="  &nbsp;&nbsp;&nbsp;&nbsp;"+days[i]+":";
						var checkbox = document.createElement('input');
						checkbox.type = "checkbox";
						checkbox.name = "rpt"+i;
						checkbox.value = 1;
						this.form_m.appendChild(checkbox);
					}
					this.form_m.innerHTML+="<br>"
					
				this.form_m.innerHTML+=" Разрешить:"
					var checkbox = document.createElement('input');
					checkbox.type = "checkbox";
					checkbox.name = "ena";
					checkbox.value = 1;
					checkbox.checked=true;
					this.form_m.appendChild(checkbox);
					
				//form_m.onclick="send_form_data('/gps_off','','');";
				var submit_button = document.createElement('input');
					submit_button.type = "button";
					submit_button.value="Добавить";
					submit_button.onclick=()=> {
						send_form_data('/task_add',this.form_m,'');
					}
					this.form_m.appendChild(submit_button);						
		}
		//////////
		parser_data(stream){
			//console.log(stream);
			if(stream['fix']==0){return;}
			key_array_to_inner(stream,'main_div_status');
		}
		error_event(message){
			console.log(message+'tr_gr');
		}
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	
	function send_form_data(url,form_name,array){
		let formData;
		if(form_name!=null && typeof(form_name)=="object"){
			formData = new FormData(form_name);
		}else if(form_name!=""){
			formData = new FormData(document.getElementById(form_name));//document.getElementById(form_name)
		}else{
			formData = new FormData();
		}
		
		for(var index in array){
			formData.append(index, array[index]);
		}
	
		var type_xnr="POST";
		if(array=="" && formData.length==0){///!!!
			type_xnr="GET";
		}

		var xmlhttprq_test = new XMLHttpRequest();
		if(document.location.protocol=="file:"){
			url="http://"+config['remoute_serv_ip']+":"+config['remoute_serv_port']+url;
		}
		xmlhttprq_test.open(type_xnr, url, true);//, true
		//xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
		//xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		xmlhttprq_test.send(formData);
	}