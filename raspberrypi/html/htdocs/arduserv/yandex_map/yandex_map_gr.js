var myMap;
var deep_points_arr = new Array();
var just_point_arr = new Array();

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