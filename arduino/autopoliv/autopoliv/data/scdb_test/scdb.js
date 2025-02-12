let xhrsc=[];

let db=new Object();
let scdb=new Object();

wpp_gr.db_server_def="";
wpp_gr.db_read_prefix="/db/";
wpp_gr.db_write_prefix="/db/w/";

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
			(mode=="edit" || mode=="create") ? scdb.create_form(data) : scdb.create_view_tree(data);
		},
		on_error:function(data){
			scdb.error(data);
		}
	});
	if(mode!="create"){
		db.load();
	}
}

function create_db(){
	scdb.create_form({0:""});
	load_db("create");
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
