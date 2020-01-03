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
					if(config['auto_move_map_to_boat']){
						yandex_map_center_map_to(stream['latitude'][3],stream['longitude'][3],0);
					}
				}
			}
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
					auto_boat_config=arr;
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
			constructor() {}
		//Парсинг
			parser_data(arr){
				//console.log(arr);
				//if(Array.isArray(arr)){
					auto_boat_routing_sets=arr;
					create_table_from_array_gr(auto_boat_routing_sets,'routing_sets');
				//}
			}
	}
	
	function autoboat_save_routing_sets_send_db(){
		var xmlhttprq_test = new XMLHttpRequest();
		xmlhttprq_test.open('POST', 'http://localhost:3128/w/db/autoboat/routing_sets.json', true);//, true
		xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
		xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		xmlhttprq_test.send(JSON.stringify(auto_boat_routing_sets,null, '\t'));
		//console.log(auto_boat_routing_sets);
		//console.log(JSON.stringify(auto_boat_routing_sets,null, ' '));
	}

	function autoboat_routing_sets_test(){
		//console.log(trip_point_arr);
		var arr_push={};
		arr_push['name']="test name";
		arr_push['description']="test description";
		arr_push['start_point']=0;
		arr_push['loop_point']=3;
		arr_push['points']=new Array();
		
		var cord=new Float32Array(2);
		for(var i=0;i<trip_point_arr.length;i++){
			cord=trip_point_arr[i]['point'].geometry.getCoordinates();
			arr_push['points'].push(cord);
		}
		
		
		auto_boat_routing_sets.push(arr_push);
		//console.log(auto_boat_routing_sets);
		autoboat_save_routing_sets_send_db();
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
