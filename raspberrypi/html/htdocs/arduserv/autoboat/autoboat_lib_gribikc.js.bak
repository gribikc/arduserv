'use strict';
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//autoboat
	class autoboat_gr{
		//Инициализация
		constructor(){
			this.parser_data_array=new Array();
			this.start_point=0;
			this.end_point=0;

			this.MESSAGE_LEN=64;
			this.HEADER=[0xAA,0xBB];
			this.FOOTER=[0xCC,0xDD];
			
			this.telemetry_message={
				hour:["Час",0,57,0],				//-57
				min:["Мин",0,56,0],					//-56
				sec:["Сек",0,55,0],					//-55
				NOS:["NOS",0,54,0],					//-54
				SIV:["SIV",0,53,0],					//-53
				SSNR:["SSNR",0,52,0],				//-52
				HDOP:["HDOP",1,51,0],				//-51...-48(float)
				altitude:["Высота",1,47,0],			//-47...-44(float)
				height:["Высота",1,43,0],			//-43...-40(float)
				latitude:["Широта",2,37,0],			//-37(byte)-37...-34(float)
				longitude:["Долгота",2,33,0],		//-33(byte)-32...-29(float)
				direction:["Направление",1,28,0],		//-28...-25(float)
				compass:["Компас",1,24,0],			//-24...-21(float)
				speed:["Скорость",1,20,0],			//-20...-17(float)
				pilot_error:["ERR",1,16,0],		//-16...-13(float)
				tiller_position:["Положение",1,12,0]	//-12...-9(float)
			}
		}
		parser_data(stream){
			this.end_point=stream.length;
			if(this.start_point>=this.end_point){
				this.start_point=0;
			}
			for(var i=this.start_point;i<this.end_point;i++){
				//console.log(stream.charCodeAt(i)&0xFF);
				if(this.start_point>=31){
					if(	(stream.charCodeAt(i)&0xFF)   ==0xDD && (stream.charCodeAt(i-1)&0xFF) ==0xCC && 
						(stream.charCodeAt(i-62)&0xFF)==0xBB && (stream.charCodeAt(i-63)&0xFF)==0xAA){							//console.log(stream.charCodeAt(i-28)&0xFF);
						//console.log(stream.charCodeAt(i-61)&0xFF);
						//console.log(stream.charCodeAt(i-61)&0xFF);
						if((stream.charCodeAt(i-61)&0xFF)==0x03){
							this.telemetry_parser(stream,i);
						}
					}
				}
			}
			this.start_point=this.end_point;
		}
		//////////
		telemetry_parser(stream,end_byte){
			//console.log(stream.charCodeAt(end_byte-60)&0xFF);
			//console.log(stream.charCodeAt(end_byte-55)&0xFF);
			document.getElementById("autobot_state").innerHTML="";
			for(var i in this.telemetry_message){
				if(this.telemetry_message[i][1]==0){
					this.telemetry_message[i][3]=stream.charCodeAt(end_byte-this.telemetry_message[i][2])&0xFF;
				}else{
					this.telemetry_message[i][3]=0;
				}
				document.getElementById("autobot_state").innerHTML+=this.telemetry_message[i][0]+": "+this.telemetry_message[i][3]+"<br>";
			}
			//console.log(this.telemetry_message);
			var k=3.1234567890123456789;
			//console.log(readBytes(k,1));
		}		
		//////////		
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
