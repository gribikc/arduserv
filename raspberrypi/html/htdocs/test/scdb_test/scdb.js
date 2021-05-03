let xhrsc=[];

let db=new Object();
let scdb=new Object();

function parse_and_sava_db(){
	db.save({arr:scdb.parser_form()});
}
function load_db(mode){
	db_name=document.getElementById("i_db_name").value;
	tb_name=document.getElementById("i_tb_name").value;

	db=new db_query_gr({db_name:db_name,table_name:tb_name,
		on_save:function(data){
			db.load();
		},
		on_load:function(data){
			(mode=="edit") ? scdb.create_form(data) : scdb.create_view_tree(data);
		},
		on_error:function(data){
			scdb.error(data);
		}
	});
	db.load();
}


function main_init(){
	if(wpp_gr.url_get_params["db"]){
		document.getElementById("i_db_name").value=wpp_gr.url_get_params["db"];
	}
	if(wpp_gr.url_get_params["tb"]){
		document.getElementById("i_tb_name").value=wpp_gr.url_get_params["tb"];
	}

	scdb=new scdb_gr(0,'tbl_db');
	if(wpp_gr.url_get_params["db"] && wpp_gr.url_get_params["tb"]){
		load_db();
	}else{
		document.getElementById("i_db_name").value="test";
		document.getElementById("i_tb_name").value="fname";
	}
}
