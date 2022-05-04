'use strict';
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//autoboat
	class izm_gr{
		//Инициализация
		constructor(){
			this.data = new google.visualization.DataTable();
			this.options = {
				chart: {
				  title: 'Box Office Earnings in First Two Weeks of Opening',
				  subtitle: 'in millions of dollars (USD)'
				},
				width: 900,
				height: 500,
				vAxis:{format: 'scientific'},
				vAxis:{gridlines:{multiple:1000000}},
				vAxis:{viewWindowMode:'pretty'}
				//vAxis:{gridlines:{interval:1}}
			  };


			this.chart = new google.charts.Line(document.getElementById('linechart_material'));
						this.data.addColumn('number', 'Time');
			this.data.addColumn('number', 'Diametr');
			this.array=[];
			this.cnt=1;
		}
		
		//////////
		parser_data(stream){
			//console.log(stream+'');
			//this.array=this.array.concat(stream);
			//this.intervalID = setInterval(this.myCallback, 1000/(this.array.length+1), this);

			
			for(var i=0;i<stream.length;i++){
				this.data.addRows([[this.cnt,stream[i]]]);
				this.cnt++;
			}
			if(this.data.Wf.length>2000){
				this.data.Wf.splice(0, this.data.Wf.length-2000);
			}
			
			
			this.chart.draw(this.data, google.charts.Line.convertOptions(this.options));
		}
		
		/*myCallback(t){
			t.data.addRows([[t.cnt,t.array[0]]]);
			t.array.splice(0, 1);
			t.cnt++;
			if(t.data.Wf.length>2000){
				t.data.Wf.splice(0, 1);
			}
			
			t.chart.draw(t.data, google.charts.Line.convertOptions(t.options));
		}*/
		
		//////////
		error_event(message){
			console.log(message+'');
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
				auto_boat_config=arr;
				create_table_from_array_gr(arr,'main_settings_edit');
			}
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