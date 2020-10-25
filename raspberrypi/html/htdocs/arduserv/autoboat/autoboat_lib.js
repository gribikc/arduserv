'use strict';
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//autoboat
	class autoboat_gr{
		//var
		//BBAA0100020000000000000000000000000000000000000000CCDD
		//var upr_cmd = new Array();
		//upr_cmd.push(nav_start : new Uint8Array([0xBB,0xAA,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]) );
		//var uint8 = new Uint8Array([0xBB,0xAA,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
		//Инициализация
		constructor(){
			this.upr_cmd = new Array();
				//												    0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x10 0x11 0x12 0x13 0x14 0x15 0x16 0x17 0x18 0x19 0x20 0x21 0x22 0x23 0x24 0x25 0x26
				//                                                   -26  -25  -24  -23  -22  -21  -20  -19  -18  -17  -16  -15  -14  -13  -12  -11  -10   -9   -8   -7   -6   -5   -4   -3   -2   -1    0
				//												     HEADER  ,0x01, ID , CMD,---------------------------------------------DATA----------------------------------------,CRCL,CRCH,  FOOTER
				this.upr_cmd['nav_ap_stop']=		new Uint8Array([0xBB,0xAA,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);//!!!
				this.upr_cmd['nav_ap_start']=		new Uint8Array([0xBB,0xAA,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				//this.upr_cmd['nav_nnm']=			new Uint8Array([0xBB,0xAA,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				this.upr_cmd['nav_ap_reset']=		new Uint8Array([0xBB,0xAA,0x01,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				//this.upr_cmd['nav_nnm']=			new Uint8Array([0xBB,0xAA,0x01,0x00,0xXX,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				this.upr_cmd['nav_apt_kompass']=	new Uint8Array([0xBB,0xAA,0x01,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				this.upr_cmd['nav_apt_point']=		new Uint8Array([0xBB,0xAA,0x01,0x00,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				this.upr_cmd['nav_apt_line']=		new Uint8Array([0xBB,0xAA,0x01,0x00,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				this.upr_cmd['nav_apt_circle']=		new Uint8Array([0xBB,0xAA,0x01,0x00,0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);

				this.upr_cmd['nav_set_pidparam']=	new Uint8Array([0xBB,0xAA,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				this.upr_cmd['nav_set_rumpel']=		new Uint8Array([0xBB,0xAA,0x01,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);
				this.upr_cmd['nav_set_track']=		new Uint8Array([0xBB,0xAA,0x01,0x01,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);

				this.upr_cmd['nav_send_point']=		new Uint8Array([0xBB,0xAA,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0xDD]);

			
			this.parser_data_array=new Array();
			this.start_point=0;
			this.end_point=0;
		}
		//////////
		parser_data(stream){
			//console.log(stream);
			document.getElementById("autobot_state").innerHTML="";
			for(var key in stream){
				document.getElementById("autobot_state").innerHTML+=stream[key][0]+": "+stream[key][3]+"<br>";
				if(key=='longitude' && stream['NOS'][3]>4){
					yandex_map_add_point_gr(stream['latitude'][3],stream['longitude'][3],10.3);
					//console.log(stream['longitude'][3]);
					if(config['map']['auto_move_map_to_boat']){
						yandex_map_center_map_to(stream['latitude'][3],stream['longitude'][3],0);
					}
				}
			}
			//over_map
			document.getElementById("over_map").innerHTML="";
			document.getElementById("over_map").innerHTML+="Скорость:"+stream['speed'][3].toFixed(1)+" км/ч.<br>";
			document.getElementById("over_map").innerHTML+="Курс:"+stream['direction'][3]+"<br>";
			document.getElementById("over_map").innerHTML+=stream['hour'][3]+":"+stream['min'][3]+":"+stream['sec'][3];
		}
		error_event(message){
			console.log(message+'autoboat_gr');
		}
		//////////
		send_cmd(name,url,mode){
			//console.log(name);
			//console.log(url);
			//console.log(this.upr_cmd[name]);//[name]
			var send_data=new Uint8Array();
			var float_byte_array;
			switch(name){
				/////////
				//////////////////////
				case 'nav_set_rumpel':
					send_data=this.upr_cmd[name];
					var incr=document.getElementById(name+"_value_gr").value;
					if(mode=='left'){
						incr=incr*(-1);
					}
					float_byte_array=byte_arr_from_float_gr(incr);
					send_data[5]=float_byte_array[0];
					send_data[6]=float_byte_array[1];
					send_data[7]=float_byte_array[2];
					send_data[8]=float_byte_array[3];
				break
				/////
				/////////////////////
				case 'nav_set_track':
					send_data=this.upr_cmd[name];
					var incr=document.getElementById(name+"_value_gr").value;
					if(mode=='left'){
						incr=incr*(-1);
					}
					float_byte_array=byte_arr_from_float_gr(incr);
					send_data[5]=float_byte_array[0];
					send_data[6]=float_byte_array[1];
					send_data[7]=float_byte_array[2];
					send_data[8]=float_byte_array[3];
				break
				/////
				////////////////////////
				case 'nav_set_pidparam':
					send_data=this.upr_cmd[name];
					var incr=document.getElementById(name+"_ke_value_gr").value;
					float_byte_array=byte_arr_from_float_gr(incr);
					send_data[5]=float_byte_array[0];
					send_data[6]=float_byte_array[1];
					send_data[7]=float_byte_array[2];
					send_data[8]=float_byte_array[3];
					
					var incr=document.getElementById(name+"_kp_value_gr").value;
					float_byte_array=byte_arr_from_float_gr(incr);
					send_data[9 ]=float_byte_array[0];
					send_data[10]=float_byte_array[1];
					send_data[11]=float_byte_array[2];
					send_data[12]=float_byte_array[3];
					
					var incr=document.getElementById(name+"_ki_value_gr").value;
					float_byte_array=byte_arr_from_float_gr(incr);
					send_data[13]=float_byte_array[0];
					send_data[14]=float_byte_array[1];
					send_data[15]=float_byte_array[2];
					send_data[16]=float_byte_array[3];
				break
				/////
				////////
				default:
					send_data[0]=0;
				break;
			}
			
			var xmlhttprq_test = new XMLHttpRequest();
			xmlhttprq_test.open('POST', url, true);//, true
			xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
			xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
			//var uint8 = new Uint8Array(2);
			//uint8[0] = 1;
			//uint8[1] = 2;
			xmlhttprq_test.send(send_data);//this.upr_cmd[name]
			//console.log(send_data);
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class json_config_read_gr{
		//Инициализация
			constructor() {}
		//Парсинг
			parser_data(arr){
				//console.log(arr);
				//if(Array.isArray(arr)){
					//auto_boat_config=arr;
					//!!!update_config_data();
					create_table_from_array_gr(arr,'main_settings_edit');
				//}else{
				//	console.error("Настройки не получены");
				//	console.log(arr);
				//}
			}
	}

	function autoboat_save_settings_send_db(){
		var xmlhttprq_test = new XMLHttpRequest();
		xmlhttprq_test.open('POST', 'http://localhost:3128/w/db/autoboat/config.json', true);//, true
		xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
		xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		xmlhttprq_test.send(JSON.stringify(auto_boat_config));
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class json_routing_sets_read_gr{
		//Инициализация
			constructor() {
				this.main_div=document.getElementById('routing_sets');
				this.div=document.createElement('div');
				this.main_div.appendChild(this.div);
				this.save_div=document.getElementById('routing_safe');
				
				this.routing_sets=new Array();
				
				document.getElementById('map').onclick=this.update_map_data;
			}
		//Парсинг
			parser_data(arr){
				this.routing_sets=arr;

				this.div.innerHTML+='<br>';
				for(var i=0;i<arr.length;i++){
					this.div.innerHTML+=arr[i]['name'];
					this.div.innerHTML+=' ('+arr[i]['description'].substr(0,10)+'...) ';
					this.div.innerHTML+=' Зап...';
					this.div.innerHTML+=' <a href=\"javascript:autoboat_routing_sets.view_route('+i+');\">Пос...</a>';
					this.div.innerHTML+=' <a href=\"javascript:autoboat_routing_sets.edit_route('+i+');\">Ред...</a>';
					this.div.innerHTML+=' Уда...';
					this.div.innerHTML+='<br>';
				}
			}
		//Карта
			view_route(id){
				var points=this.routing_sets[id]['points'];
				this.clear_map();
				fx_yandex_map_addnew_trip_polint_gr(points);
				yandex_map_center_map_to(points[0],points[1],0);
				
				this.update_route_data(id);
				document.getElementById('routing_safe_pc').value=points.length;
			}
			edit_route(id){
				var points=this.routing_sets[id]['points'];
				this.clear_map();				
				for(var i=0;i<points.length;i++){
					fx_yandex_map_addnew_trip_point_gr(points[i][0],points[i][1]);
				}
				yandex_map_center_map_to(points[0],points[1],0);
				
				this.update_route_data(id);
				this.update_map_data()
			}
			clear_map(){
				fx_yandex_map_delete_all_trip_point_gr();
				
				this.update_map_data();
			}
			update_route_data(id){
				document.getElementById('routing_safe_name').value=this.routing_sets[id]['name'];
				document.getElementById('routing_safe_teg').value=this.routing_sets[id]['tag'];
				document.getElementById('routing_safe_catalog').value=this.routing_sets[id]['catalog'];
				document.getElementById('routing_safe_start_point').value=this.routing_sets[id]['start_point'];
				document.getElementById('routing_safe_loop_point').value=this.routing_sets[id]['start_point'];
				document.getElementById('routing_safe_description').value=this.routing_sets[id]['description'];
			}
			update_map_data(){
				document.getElementById('routing_safe_pc').value=trip_point_arr.length;
			}
		//Сохранить/Перезагрузить
			routing_add_to_array(){
				//console.log(trip_point_arr);
				var arr_push={};
				arr_push['name']=document.getElementById('routing_safe_name').value;
				arr_push['tag']=document.getElementById('routing_safe_teg').value;
				arr_push['catalog']=document.getElementById('routing_safe_catalog').value;
				arr_push['description']=document.getElementById('routing_safe_description').value;
				arr_push['start_point']=document.getElementById('routing_safe_start_point').value;
				arr_push['loop_point']=document.getElementById('routing_safe_loop_point').value;
				arr_push['points']=new Array();
				
				var cord=new Float32Array(2);
				for(var i=0;i<trip_point_arr.length;i++){
					cord=trip_point_arr[i]['point'].geometry.getCoordinates();
					arr_push['points'].push(cord);
				}

				autoboat_routing_sets.routing_sets.push(arr_push);
				this.routing_save_to_db();
			}
			routing_save_to_db(){
				var xmlhttprq_test = new XMLHttpRequest();
				xmlhttprq_test.open('POST', 'http://192.168.1.44:3128/db/w/autoboat/routing_sets.json', true);//, true
				xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
				xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
				xmlhttprq_test.send(JSON.stringify(autoboat_routing_sets.routing_sets,null, '\t'));
			}
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	function generate_show_hide_menu_from_div(main_div_name,control_div_name){
		var main_div = document.getElementById(main_div_name);
		var control_div = document.getElementById(control_div_name);
		var elementChildrens = main_div.children;
		for (var i=0, child; child=elementChildrens[i]; i++) {
			var new_div = document.createElement('a');
			new_div.onclick=function changeContent() {
				view_main_menu_hide_all('main_list_of_all','main_wiev_div',1);
				full_view_inner_gr(document.getElementById(this.name));
			}		
			
			control_div.appendChild(new_div);
			new_div.classList.add('mini_icon_mm_gr');//mini_icon_mm_gr//menu_up_a_gr
			new_div.innerHTML=child.dataset['name'];
			new_div.name=child.id;
		}
	}
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	function view_main_menu_hide_all(div_menu,div_main,sw){
		var inner_count=document.getElementById("main_wiev_div").childElementCount;
		var vis_ch_tg=0;
		if(sw==0){
			full_hide_inner_gr(document.getElementById(div_main));
			full_view_inner_gr(document.getElementById(div_menu));
			for(var i=0;i<inner_count;i++){
				full_hide_inner_gr(document.getElementById("main_wiev_div").children[i]);
			}
		}else{
			full_hide_inner_gr(document.getElementById(div_menu));
			full_view_inner_gr(document.getElementById(div_main));
		}
	}
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	function next_prev_main_wiev_div_in(rf){
		/*
			При переключении скрывать все и открывать только один или 
			если открыто несколько то закрывать первый открывать следующий...
		*/
		var i;
		var inner;
		var inner_count=document.getElementById("main_wiev_div").childElementCount;
		var vis_ch_tg=0;
		for(i=0;i<inner_count;i++){
			inner=document.getElementById("main_wiev_div").children[i];
			if(vis_ch_tg==1){
				full_hide_inner_gr(inner);
			}else if(inner.style.visibility=="visible"	|| inner.style.position=="unset" 	||
					 inner.style.zIndex=="unset"       	|| inner.style.visibility=="" 		||
					 inner.style.position==""          	|| inner.style.zIndex==""){
				full_hide_inner_gr(inner);
				vis_ch_tg=1;
				if(rf=='f'){
					if( !(inner=document.getElementById("main_wiev_div").children[i+1]) ){
						inner=document.getElementById("main_wiev_div").children[0];
					}
					i++;
				}else{
					if( !(inner=document.getElementById("main_wiev_div").children[i-1]) ){
						inner=document.getElementById("main_wiev_div").children[inner_count-1];
						inner_count--;
					}
				}
				vis_ch_tg=1;
				full_view_inner_gr(inner);
			}
		}
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	function test_send_data1(){
		xmlhttprq_test = new XMLHttpRequest();
		xmlhttprq_test.open('POST', 'http://localhost:3128/W/COM/28/57600/', true);//, true
		xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
		xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		var uint8 = new Uint8Array(2);
		uint8[0] = 1;
		uint8[1] = 2;
		xmlhttprq_test.send(uint8);
		//!!!xmlhttprq_test.abort();
		//xmlhttprq_test.send();
	}	