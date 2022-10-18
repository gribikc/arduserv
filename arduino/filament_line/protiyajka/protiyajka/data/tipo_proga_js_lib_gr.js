'use strict';
/////////////////////////////////
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	function generate_show_hide_menu_from_div(main_div_name,control_div_name){
		var main_div = document.getElementById(main_div_name);
		var control_div = document.getElementById(control_div_name);
		var elementChildrens = main_div.children;
		for (var i=0, child; child=elementChildrens[i]; i++) {
			var new_div = document.createElement('a');
			new_div.onclick=function changeContent() {
				view_main_menu_hide_all('main_list_of_all','main_wiev_div',1);
				full_view_inner_gr(document.getElementById(this.name));
			}		
			
			control_div.appendChild(new_div);
			new_div.classList.add('mini_icon_mm_gr');//mini_icon_mm_gr//menu_up_a_gr
			new_div.innerHTML=child.dataset['name'];
			new_div.name=child.id;
		}
	}
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	function view_main_menu_hide_all(div_menu,div_main,sw){
		var inner_count=document.getElementById("main_wiev_div").childElementCount;
		var vis_ch_tg=0;
		if(sw==0){
			full_hide_inner_gr(document.getElementById(div_main));
			full_view_inner_gr(document.getElementById(div_menu));
			for(var i=0;i<inner_count;i++){
				full_hide_inner_gr(document.getElementById("main_wiev_div").children[i]);
			}
		}else{
			full_hide_inner_gr(document.getElementById(div_menu));
			full_view_inner_gr(document.getElementById(div_main));
		}
	}
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	function next_prev_main_wiev_div_in(rf){
		/*
			При переключении скрывать все и открывать только один или 
			если открыто несколько то закрывать первый открывать следующий...
		*/
		var i;
		var inner;
		var inner_count=document.getElementById("main_wiev_div").childElementCount;
		var vis_ch_tg=0;
		for(i=0;i<inner_count;i++){
			inner=document.getElementById("main_wiev_div").children[i];
			if(vis_ch_tg==1){
				full_hide_inner_gr(inner);
			}else if(inner.style.visibility=="visible"	|| inner.style.position=="unset" 	||
					 inner.style.zIndex=="unset"       	|| inner.style.visibility=="" 		||
					 inner.style.position==""          	|| inner.style.zIndex==""){
				full_hide_inner_gr(inner);
				vis_ch_tg=1;
				if(rf=='f'){
					if( !(inner=document.getElementById("main_wiev_div").children[i+1]) ){
						inner=document.getElementById("main_wiev_div").children[0];
					}
					i++;
				}else{
					if( !(inner=document.getElementById("main_wiev_div").children[i-1]) ){
						inner=document.getElementById("main_wiev_div").children[inner_count-1];
						inner_count--;
					}
				}
				vis_ch_tg=1;
				full_view_inner_gr(inner);
			}
		}
	}