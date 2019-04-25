var myMap;
var deep_points_arr = new Array();
var just_point_arr = new Array();

var trip_point_arr = new Array();

ymaps.ready(init);


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
function init() {
    // Создаем карту.
    myMap = new ymaps.Map("map", {
            center: [56.34131, 30.520045],//center: [56.155172, 30.585121],
            zoom: 15
        }, {
            searchControlProvider: 'yandex#search'
        });	
	
    myMap.events.add('click', function (e) {
		if(myMap.balloon.isOpen()){
			myMap.balloon.close();//Закрыть активный балун
		}else{
			var coords = e.get('coords');
			on_yandex_map_click_gr(coords[0].toPrecision(10),coords[1].toPrecision(10));
		}
    });
		
	add_text_to_map();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
function yandex_map_add_deep_gr(x,y,deep){
	//console.log('Длинна массива: '+deep_points_arr.length);
	for(var i=0;i<deep_points_arr.length;i++){
		if(deep_points_arr[i]['x']==x && deep_points_arr[i]['y']==y){
			/*if(deep_points_arr[i]['deep']==deep){
				//console.log('Полное совпадение');
			}else{
				console.log('Не совпала глубина:'+deep_points_arr[i]['deep']+'-_-'+deep);
			}*/
			//console.log('<HZRF');
			return;
		}
	}
	
	var arr_push={x:x,y:y,deep:deep};
	// Создаем круг.
    var myCircle = new ymaps.Circle([
        // Координаты центра круга.
        [x, y],
        // Радиус круга в метрах.
        1
    ], {
        // Описываем свойства круга.
        // Содержимое балуна.
        balloonContent: deep+" м.",
        // Содержимое хинта.
        hintContent: ""
    }, {
        // Задаем опции круга.
        // Включаем возможность перетаскивания круга.
        draggable: false,
        // Цвет заливки.
        // Последний байт (77) определяет прозрачность.
        // Прозрачность заливки также можно задать используя опцию "fillOpacity".
        fillColor: "rgb("+deep*30+","+deep*30+","+deep*0+")",//#DB7093"
		fillOpacity: "50",
        // Цвет обводки.
        strokeColor: "#FFFFFF",
        // Прозрачность обводки.
        strokeOpacity: 0,
        // Ширина обводки в пикселях.
        strokeWidth: 0
    });

	//myCircle.events.add('click', function (e) {alert(deep);})
	
    // Добавляем круг на карту.
    myMap.geoObjects.add(myCircle);
	//arr_push.push=myCircle;
	deep_points_arr.push(arr_push);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
function yandex_map_center_map_to(x,y,mode){
	if(mode==1){
		x=just_point_arr[just_point_arr.length-1]['x'];
		y=just_point_arr[just_point_arr.length-1]['y'];
	}
	//myMap.setCenter([x, y]);
	myMap.panTo([x, y],{duration:2000,flying:false,safe:true});
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
function yandex_map_add_point_gr(x,y,deep){
	if(x==0 && y==0){
		return;
	}
	//console.log('Длинна массива: '+deep_points_arr.length);
	for(var i=0;i<just_point_arr.length;i++){
		if(just_point_arr.length>=50){
			//console.log(just_point_arr[i]);
			myMap.geoObjects.remove(just_point_arr[i]['point']);
			just_point_arr.shift();
			//continue;
		}
		if(just_point_arr[i]['x']==x && just_point_arr[i]['y']==y){
			/*if(deep_points_arr[i]['deep']==deep){
				//console.log('Полное совпадение');
			}else{
				console.log('Не совпала глубина:'+deep_points_arr[i]['deep']+'-_-'+deep);
			}*/
			//console.log('<HZRF');
			return;
		}
	}

	var arr_push={x:x,y:y,deep:deep,point:0};
	// Создаем круг.
    var myCircle = new ymaps.Circle([
        // Координаты центра круга.
        [x, y],
        // Радиус круга в метрах.
        0.3
    ], {
        // Описываем свойства круга.
        // Содержимое балуна.
        balloonContent: deep+" м.",
        // Содержимое хинта.
        hintContent: ""
    }, {
        // Задаем опции круга.
        // Включаем возможность перетаскивания круга.
        draggable: false,
        // Цвет заливки.
        // Последний байт (77) определяет прозрачность.
        // Прозрачность заливки также можно задать используя опцию "fillOpacity".
        fillColor: "rgb("+255+","+0+","+0+")",//#DB7093"//fillColor: "rgb("+deep*30+","+deep*30+","+deep*0+")",//#DB7093"
		fillOpacity: "50",
        // Цвет обводки.
        strokeColor: "#FFFFFF",
        // Прозрачность обводки.
        strokeOpacity: 0,
        // Ширина обводки в пикселях.
        strokeWidth: 0
    });

	//myCircle.events.add('click', function (e) {alert(deep);})
	
    // Добавляем круг на карту.
    myMap.geoObjects.add(myCircle);
	//arr_push.push=myCircle;
	arr_push['point']=myCircle;
	just_point_arr.push(arr_push);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
function add_text_to_map(){

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
function on_yandex_map_click_gr(x,y){
	//alert(coords[0].toPrecision(10)+';'+coords[1].toPrecision(10));
	/*
		1) Начало ввода маршрута
			0. Очистка переменных и точек карты		F(x)
			1. добавление точки маршрута 			F(x)+//fx_yandex_map_addnew_trip_point_gr
			2. удаление точки маршрута				F(x)+//fx_yandex_map_delete_trip_point_gr
			3. вставка точки между					F(x)+//fx_yandex_map_middle_trip_point_gr
			4. переcчет индексов массива			F(x)+//fx_yandex_map_repair_trip_point_gr
		2) Завершение ввода маршрута
			0. настройка параметров(стартовая точка, точка кольца, ...)
			1. сохранение или передача массива		F(x),F(x)
		3) Загрузка точек массива из ранее сохраненного
			0. переход в 1) если надо
	*/
	//console.log(x+';'+y);
	
	fx_yandex_map_addnew_trip_point_gr(x,y);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
function fx_yandex_map_addnew_trip_point_gr(x,y){
	var arr_push={x:0,y:0,deep:0,point:0};
	var myPlacemark = new ymaps.Placemark(
		[x, y],{
			balloonContent: "	<a onclick='fx_yandex_map_middle_trip_point_gr("+trip_point_arr.length+");'>Вставить точку перед:"+trip_point_arr.length+"</a><br><br> \
								<a onclick='fx_yandex_map_delete_trip_point_gr("+trip_point_arr.length+");'>Удалить точку:"+trip_point_arr.length+"</a>",
			//<a onclick='fx_yandex_map_repair_trip_point_gr();'>тест</a>
			iconContent: trip_point_arr.length,

		},{
			draggable: true,
			preset: 'islands#redIcon'
		}
	);

	// Добавляем круг на карту.
    myMap.geoObjects.add(myPlacemark);
	arr_push['point']=myPlacemark;
	trip_point_arr.push(arr_push);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
function fx_yandex_map_delete_trip_point_gr(id){
	myMap.balloon.close();
	
	myMap.geoObjects.remove(trip_point_arr[id]['point']);
	//delete trip_point_arr[id];
	trip_point_arr.splice(id,1);
	fx_yandex_map_repair_trip_point_gr();	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
function fx_yandex_map_repair_trip_point_gr(){
	myMap.balloon.close();
	
	for(var i=0;i<trip_point_arr.length;i++){
		//console.log( trip_point_arr[i] );
		//console.log( trip_point_arr[i]['point']['properties']['_data']['iconContent'] );//.properties._data.iconContent
		//trip_point_arr[i]['point']['properties']['_data']['iconContent']=i;
		//trip_point_arr[i]['point']['properties']['_data']['balloonContent']="<br><a onclick='fx_yandex_map_delete_trip_point_gr("+i+");'>Удалить точку</a>";
		trip_point_arr[i]['point'].properties.set('iconContent', i);
		trip_point_arr[i]['point'].properties.set('balloonContent', "	<a onclick='fx_yandex_map_middle_trip_point_gr("+i+");'>Вставить точку перед:"+i+"</a><br><br> \
																		<a onclick='fx_yandex_map_delete_trip_point_gr("+i+");'>Удалить точку:"+i+"</a>");

	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
function fx_yandex_map_middle_trip_point_gr(id){
	if(id==0){return;}
	
	
	//console.log(trip_point_arr[id]['point']['geometry']['_coordinates']);//geometry._coordinates
	//var coords = trip_point_arr[id]['point']['geometry']['_coordinates'];
	var x,y;
	//x=trip_point_arr[id]['point']['geometry']['_coordinates'][0];
	//y=trip_point_arr[id]['point']['geometry']['_coordinates'][1];
	//coords = trip_point_arr[id-1]['point']['geometry']['_coordinates'];
	var st=new Float32Array(2);
	var rd=new Float32Array(2);
	st=trip_point_arr[id]['point'].geometry.getCoordinates();
	rd=trip_point_arr[id-1]['point'].geometry.getCoordinates();
	
	x=( parseFloat(rd[0])+parseFloat(st[0]) )/2;
	y=( parseFloat(rd[1])+parseFloat(st[1]) )/2;
	
	console.log(x,y);

	fx_yandex_map_addnew_trip_point_gr(x,y);
	
	trip_point_arr.splice( id, 0,trip_point_arr[trip_point_arr.length-1] );//trip_point_arr.splice( (trip_point_arr.length-1),1 )
	trip_point_arr.splice((trip_point_arr.length-1),1);
	
	fx_yandex_map_repair_trip_point_gr();
	
}