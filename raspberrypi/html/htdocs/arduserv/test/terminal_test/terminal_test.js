'use strict';
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
	class terminal_gr{
		constructor(hub){
			this.parser_data_array=new Array();
			this.hub_handler=hub;
			this.start_point=0;
			this.end_point=0;
			this.json_begin_point=0;
			this.json_begin_point_valid=0;

			this.speed=0;

			this.message_cnt=0;
			this.socket;

			this.type_view="txt";
		}
		////////////////////
		change_view(){
			this.type_view=(this.type_view=="txt")?this.type_view=="hex":this.type_view="txt";
		}
		parser_data(stream){
			//console.log(stream);
			var inner =document.getElementById('terminal_in_div');
			var div = document.createElement("div");
			//div.style+="clear: left";
				var div_pre = document.createElement("div");
				div_pre.innerHTML=":"+this.message_cnt+"#";
				div_pre.style+="float: left;";
				//div.appendChild(div_pre);

				var div_data = document.createElement("div");
				if(this.type_view=="txt"){
					if(typeof stream=="object"){
						var view   = new Uint8Array(stream);
						//div_data.innerHTML=view;
						for(var i=0;i<view.length;i++){
							div_data.innerHTML+=String.fromCharCode(view[i]);
						}
					}else{
						div_data.innerHTML=stream;
					}
				}else{
					if(typeof stream=="object"){
						var view   = new Uint8Array(stream);
						for(var i=0;i<view.length;i++){
							div_data.innerHTML+=" "+view[i].toString(16)+",";
						}
					}else{
						for(var i=0;i<stream.length;i++){
							div_data.innerHTML+=" "+stream.charCodeAt(i).toString(16)+",";
						}
					}
				}
			    div.appendChild(div_data);
			inner.appendChild(div);

			while(inner.childElementCount>30){
				inner.children[0].remove();
			}

			this.message_cnt++;
		}
		///////////////////
		add_socket(socket){
			this.socket=socket;
		}
		////////////
		send_data(){
			this.socket.websocket.send(document.getElementById('terminal_out_input').value);
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
