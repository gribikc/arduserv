let xhrsc=[];

let db=new Object();
let scdb=new Object();

function sava_data(){
	db.save({arr:scdb.parser_form()});
}

function main_init(){
	scdb=new scdb_gr(0,'tbl_db')

	db=new db_query_gr({db_name:"terminal",table_name:"history",
		save_callback:function(data){
			db.load();
		},
		load_callback:function(data){
			scdb.create_form(data);
		}
	});
	db.load();
}
