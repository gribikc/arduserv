'use strict';
class json_routing_sets_read_gr {
    //Инициализация
        constructor(param) {
            this.param=param;
            this.main_div=document.getElementById('routing_sets');
            this.div=document.createElement('div');
            this.main_div.appendChild(this.div);
            this.save_div=document.getElementById('routing_safe');
            
            this.routing_sets=new Array();
            
            document.getElementById('map').onclick=this.update_map_data;

            this.edit_mode=0;
            this.edit_id=0;

            this.db=new db_query_gr({db_name:this.param.db_name,table_name:this.param.table_name,
                on_save:this,//on_save(arr)
                on_load:this,//parser_data(arr)
            });
            this.db.load();
        }

        mode_edit(mode,id){
            if(mode==1){
                this.edit_mode=1;
                this.edit_id=id;
            }else{
                this.edit_mode=0;
                this.edit_id=id;
            }
        }

        on_save(arr){
            console.log(arr);
            this.db.load();
        }
    //Парсинг
        parser_data(arr){
            this.routing_sets=arr;

            this.div.innerHTML='';
            this.div.innerHTML+='<br>';
            for(var i=0;i<arr.length;i++){
                this.div.innerHTML+=arr[i]['name'];
                this.div.innerHTML+=' ('+arr[i]['description'].substr(0,10)+'...) ';
                this.div.innerHTML+=' Зап...ь';
                this.div.innerHTML+=' <a href=\"javascript:autoboat_routing_sets.view_route('+i+');\">Пос...</a>';
                this.div.innerHTML+=' <a href=\"javascript:autoboat_routing_sets.edit_route('+i+');\">Ред...</a>';
                this.div.innerHTML+=' Уда...';
                this.div.innerHTML+='<br>';
            }
        }
    //Карта
        view_route(id){
            this.mode_edit(0,0);
            var points=this.routing_sets[id]['points'];
            this.clear_map();
            fx_yandex_map_addnew_trip_polint_gr(points);
            yandex_map_center_map_to(points[0],points[1],0);
            
            this.update_route_data(id);
            document.getElementById('routing_safe_pc').value=points.length;
        }
        edit_route(id){
            this.mode_edit(0,id);
            var points=this.routing_sets[id]['points'];
            this.clear_map();				
            for(var i=0;i<points.length;i++){
                fx_yandex_map_addnew_trip_point_gr(points[i][0],points[i][1]);
            }
            yandex_map_center_map_to(points[0],points[1],0);
            
            this.update_route_data(id);
            this.update_map_data()
        }
        clear_map(){
            this.mode_edit(0,0);

            fx_yandex_map_delete_all_trip_point_gr();
            
            this.update_map_data();
        }
        update_route_data(id){
            document.getElementById('routing_safe_name').value=this.routing_sets[id]['name'];
            document.getElementById('routing_safe_teg').value=this.routing_sets[id]['tag'];
            document.getElementById('routing_safe_catalog').value=this.routing_sets[id]['catalog'];
            document.getElementById('routing_safe_start_point').value=this.routing_sets[id]['start_point'];
            document.getElementById('routing_safe_loop_point').value=this.routing_sets[id]['start_point'];
            document.getElementById('routing_safe_description').value=this.routing_sets[id]['description'];
        }
        update_map_data(){
            document.getElementById('routing_safe_pc').value=trip_point_arr.length;
        }
    //Сохранить/Перезагрузить
        routing_add_to_array(){
            //console.log(trip_point_arr);
            var arr_push={};
            arr_push['name']=document.getElementById('routing_safe_name').value;
            arr_push['tag']=document.getElementById('routing_safe_teg').value;
            arr_push['catalog']=document.getElementById('routing_safe_catalog').value;
            arr_push['description']=document.getElementById('routing_safe_description').value;
            arr_push['start_point']=document.getElementById('routing_safe_start_point').value;
            arr_push['loop_point']=document.getElementById('routing_safe_loop_point').value;
            arr_push['points']=new Array();
            
            var cord=new Float32Array(2);
            for(var i=0;i<trip_point_arr.length;i++){
                cord=trip_point_arr[i]['point'].geometry.getCoordinates();
                arr_push['points'].push(cord);
            }

            this.routing_sets[this.edit_id]=(arr_push);//autoboat_routing_sets. ???
            this.routing_save_to_db();

            this.mode_edit(0,0);
            clear_map();
        }
        routing_save_to_db(){
            let data=JSON.stringify(autoboat_routing_sets.routing_sets,null, '\t');
            this.db.save(data);
        }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class json_config_read_gr{
    //Инициализация
        constructor(param) {
            this.param=param;

            this.db=new db_query_gr({db_name:this.param.db_name,table_name:this.param.table_name,
                on_save:this,//on_save(arr)
                on_load:this,//parser_data(arr)
            });
            this.db.load();
        }
    //Парсинг
        on_save(arr){
            this.db.load();
        }
        parser_data(arr){
            create_table_from_array_gr(arr,'main_settings_edit');
        }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function test_send_data1(){
	xmlhttprq_test = new XMLHttpRequest();
	xmlhttprq_test.open('POST', 'http://localhost:3128/W/COM/28/57600/', true);//, true
	xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
	xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
	var uint8 = new Uint8Array(2);
	uint8[0] = 1;
	uint8[1] = 2;
	xmlhttprq_test.send(uint8);
	//!!!xmlhttprq_test.abort();
	//xmlhttprq_test.send();
}