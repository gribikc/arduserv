'use strict';
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
	class scdb_gr{
		constructor(hub,div){
			this.hub_handler=hub;
			this.div=div;
		}
		//////////
		parser_data(stream){
			console.log(stream);
			//console.log(JSON.stringify(stream),null, '\t');
			
			//var div_p = document.createElement("div");
			//document.getElementById(this.div).appendChild(div_p);
			var div_p = document.getElementById(this.div);
			create_div_from_array_to_db_gr("conf",stream,div_p);
			
			var arr=new Object();//Object//Array//
			
			var div_p = document.getElementById(this.div);
			arr=create_array_from_div_to_db_gr(div_p);
			console.log(arr);
			var div_p = document.getElementById('tbl_db2');
			create_div_from_array_to_db_gr("conf",arr,div_p);
			
			//console.log(JSON.stringify(Object.assign({},arr),null, '\t'));
			//console.log(JSON.stringify(Object.assign({},arr),null, '\t'));
			
			//if(JSON.stringify(Object.assign({},stream))==JSON.stringify(Object.assign({},arr))){
			//	console.log("equal!!!");
			//}else{
			//	console.log("NOT equal!!!");
			//}
			
			//save_db(arr);
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	function save_db(arr){
		var xmlhttprq_test = new XMLHttpRequest();
		xmlhttprq_test.open('POST', 'http://127.0.0.1:3128/db/w/test/fname.json', true);//, true
		xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
		xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		xmlhttprq_test.send(JSON.stringify(arr,null, '\t'));
		console.log(JSON.stringify(arr,null, '\t'));
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*function create_div_from_array_to_db_gr(pre_fix,name,arr,div){
		var i=0;
		
		for(var key in arr) {
			var div_c = document.createElement("div");
			div.appendChild(div_c);
			div_c.id=key;
			if(Array.isArray(arr[key]) || Array.isAssociativeArray(arr[key])){
				create_div_from_array_to_db_gr(pre_fix+"|",key,arr[key],div_c);//!!!div_c
			}else{
				div_c.innerHTML=arr[key];//div_c.innerHTML+=pre_fix+"-"+name+"["+i+"]["+key+"]:"+arr[key];
			}
		}
		i++;
	}*/
	function create_div_from_array_to_db_gr(name,arr,inner){
		var i=0;
		var ul=document.createElement("ul");
		inner.appendChild(ul);
		
		for(var key in arr) {
			var li = document.createElement("li");
			ul.appendChild(li);
				var div_c = document.createElement("div");
				li.appendChild(div_c);
					var input_n=document.createElement("input");
					div_c.appendChild(input_n);
						input_n.name='name';
						input_n.value=key;
					var input_v=document.createElement("input");
					div_c.appendChild(input_v);
						input_v.name='value';
						input_v.value=arr[key];
				var div_r = document.createElement("div");
				//li.appendChild(div_r);
				//	div_r.innerHTML+="ADE";

			if(Array.isArray(arr[key]) || Array.isAssociativeArray(arr[key])){				
				div_c.removeChild(input_v);
				create_div_from_array_to_db_gr(key,arr[key],li);
			}
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*function create_array_from_div_to_db_gr(div){
		//document.getElementById("tbl_db").children[0]
		//childElementCount: 4
		//id: ""
		//localName: "div"
		//console.log(div.children[0].children);
		
		var arr=new Array();//Object//Array//
		var i=0;
		var a_cnt=0;
		var is_num=0;
		
		for(i=0;i<div.childElementCount;i++){
			is_num=0;
			if(div.children[i].id==i){
				is_num=1;
				a_cnt++;
			}
			
			if(div.children[i].childElementCount>0){
				arr[div.children[i].id]=(create_array_from_div_to_db_gr(div.children[i]));
			}else{
				if((is_num)){
					arr.push(div.children[i].innerText);
				}else{
					if(isFinite(div.children[i].innerText)){
						arr[div.children[i].id]=Number(div.children[i].innerText);
					}else{
						arr[div.children[i].id]=div.children[i].innerText;
					}
				}
			}
		}
		
		if(a_cnt!=div.childElementCount){
			arr=Object.assign({},arr);
		}
		return arr;
	}*/
	/*function create_array_from_div_to_db_gr(inner){
		var arr=new Array();

		for(var i=0;i<inner.childElementCount;i++){
			if(inner.children[i].tagName=='LI'){
				arr[i]=new Object();
				//arr[i]['name']=inner.children[i].tagName;
				arr[i]=create_array_from_div_to_db_gr(inner.children[i]);
			}else if(inner.children[i].tagName=='INPUT'){
				arr[i]=new Array();
				//arr=new Object();
				arr[i][inner.children[i].name]=inner.children[i].value;
				//arr[i]['parent']=create_array_from_div_to_db_gr(inner.children[i]);
			}else{
				arr.push( create_array_from_div_to_db_gr(inner.children[i]) );
			}
		}

		return arr;
	}*/
	function create_array_from_div_to_db_gr(inner){
		var arr=new Object();
		var k=0;

		for(var i=0;i<inner.childElementCount;i++){
			if(inner.children[i].tagName=='UL'){
				//arr=new Object();
				//arr[i]['name']=inner.children[i].tagName;
				//arr[i]=create_array_from_div_to_db_gr(inner.children[i]);
				//arr.push(create_array_from_div_to_db_gr(inner.children[i]));
				//if(i!=0){
				//	arr[i]=create_array_from_div_to_db_gr(inner.children[i]);
				//}else{
				//	arr=create_array_from_div_to_db_gr(inner.children[i]);
				//}
				
				arr[i]=create_array_from_div_to_db_gr(inner.children[i]);
				//var arr_new=create_array_from_div_to_db_gr(inner.children[i]);
				//for (let key in arr_new) {
				//	arr[key]=arr_new[key];
				//}
			}else if(inner.children[i].tagName=='LI'){
				//arr[i]=create_array_from_div_to_db_gr(inner.children[i]);
				var arr_new=create_array_from_div_to_db_gr(inner.children[i]);
				for (let key in arr_new) {
					arr[key]=arr_new[key];
				}
			}else if(inner.children[i].tagName=='DIV'){
				arr=create_array_from_div_to_db_gr(inner.children[i]);
				//var arr_new=create_array_from_div_to_db_gr(inner.children[i]);
				//for (let key in arr_new) {
				//	arr[key]=arr_new[key];
				//}
			}else if(inner.children[i].tagName=='INPUT'){
				k++;
				//arr[i]=new Array();
				if(inner.children[i].name=='name' && i==(inner.childElementCount-1)){
					arr[inner.children[i].value]=inner.children[i].name;
				}else{
					arr[inner.children[i].value]=inner.children[i+1].value;
					i++;
				}
				//arr[i]=new Array();
				//arr[i][inner.children[i].name]=inner.children[i].value;
			}else{
				console.log('Error:',inner.children[i].tagName);
			}
		}
		return arr;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
