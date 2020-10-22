let xhrsc=[];

let db=new Object();
let scdb=new Object();

function sava_data(){
	db.save({arr:scdb.parser_form()});
}
function load_db(){
	db_name=document.getElementById("i_db_name").value;
	tb_name=document.getElementById("i_tb_name").value;
	
	db=new db_query_gr({db_name:db_name,table_name:tb_name,
		save_callback:function(data){
			db.load();
		},
		load_callback:function(data){
			scdb.create_form(data);
		}
	});
	db.load();
}

function main_init(){
	console.log( url_get_params_gr);
	if(url_get_params_gr["db"]){
		document.getElementById("i_db_name").value=url_get_params_gr["db"];
	}
	if(url_get_params_gr["tb"]){
		document.getElementById("i_tb_name").value=url_get_params_gr["tb"];
	}
	
	scdb=new scdb_gr(0,'tbl_db');
	if(url_get_params_gr["db"] && url_get_params_gr["tb"]){
		load_db();
	}else{
		document.getElementById("i_db_name").value="test";
		document.getElementById("i_tb_name").value="fname";
	}
}
