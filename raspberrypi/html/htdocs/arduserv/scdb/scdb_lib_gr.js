'use strict';
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
	class scdb_gr{
		constructor(hub){
			this.hub_handler=hub;
		}
		//////////
		parser_data(type,stream){
			console.log(stream);
			create_table_from_array_to_db_gr(stream,"tbl_db")
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	function autoboat_save_routing_sets_send_db(){
		var xmlhttprq_test = new XMLHttpRequest();
		xmlhttprq_test.open('POST', 'http://127.0.0.1:3128/htdocs/db/test/fname.json', true);//, true
		xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
		xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		xmlhttprq_test.send(JSON.stringify(auto_boat_routing_sets,null, '\t'));
		//console.log(auto_boat_routing_sets);
		//console.log(JSON.stringify(auto_boat_routing_sets,null, ' '));
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	function create_table_from_array_to_db_gr(arr_in,div){
		
		var table = document.createElement("table");
		var tr,td,text,temp;
        table.setAttribute("border", "2px");
		var arr=new Array();
		var i=0;
		
			tr = document.createElement("tr");
				td = document.createElement("td");
				text = document.createTextNode('Имя');
				td.appendChild(text);
				tr.appendChild(td);
				
				td = document.createElement("td");
				text = document.createTextNode('Тип');
				td.appendChild(text);
				tr.appendChild(td);
				
				td = document.createElement("td");
				text = document.createTextNode('Описание');
				td.appendChild(text);
				tr.appendChild(td);
				
				td = document.createElement("td");
				text = document.createTextNode('значение');
				td.appendChild(text);
				tr.appendChild(td);
			table.appendChild(tr);
		
		
		for(i=0;i<arr_in.length;i++){
			tr = document.createElement("tr");
				td = document.createElement("td");
				text = document.createTextNode(arr_in[i]['name_of_gr']);
				td.appendChild(text);
				tr.appendChild(td);
				
				td = document.createElement("td");
				text = document.createTextNode(arr_in[i]['type_of_gr']);
				td.appendChild(text);
				tr.appendChild(td);
				
				td = document.createElement("td");
				text = document.createTextNode(arr_in[i]['description_of_gr']);
				td.appendChild(text);
				tr.appendChild(td);
				
				td = document.createElement("td");
				text = document.createTextNode(arr_in[i]['value_of_gr']);
				td.appendChild(text);
				tr.appendChild(td);
			table.appendChild(tr);
		}

		/*var i=0;
		do{
			if(Array.isArray(arr_in)){
				arr=arr_in[i];
				if(i>0){
					tr = document.createElement("tr");
					td = document.createElement("td");
					td.setAttribute("colspan", 2);
					text = document.createTextNode("---");
					td.appendChild(text);
					tr.appendChild(td);
					table.appendChild(tr);
				}
			}else{
				arr=arr_in;
			}
				for(var key in arr) {
					tr = document.createElement("tr");
					td = document.createElement("td");
					text = document.createTextNode(key);
					td.appendChild(text);
					tr.appendChild(td);
				
					if(arr[key].length>0 && Array.isArray(arr[key])){
						td.setAttribute("rowspan", arr[key].length);
						for(var k in arr[key]) {
							td = document.createElement("td");
							text = document.createTextNode(arr[key][k]);
							td.appendChild(text);
							tr.appendChild(td);
							table.appendChild(tr);
							
							tr = document.createElement("tr");
							table.appendChild(tr);
						}
						table.removeChild(tr);
					}else{
						td = document.createElement("td");
						text = document.createTextNode(arr[key]);
						td.appendChild(text);
						tr.appendChild(td);
						table.appendChild(tr);
					}
				}
			i++;
		} while(i<arr_in.length)*/
		//}

		document.getElementById(div).appendChild(table);
	}