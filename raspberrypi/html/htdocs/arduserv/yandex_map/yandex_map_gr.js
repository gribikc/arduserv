var myMap;
var deep_points_arr = new Array();

ymaps.ready(init);



function init() {
    // Создаем карту.
    myMap = new ymaps.Map("map", {
            center: [56.155172, 30.585121],
            zoom: 15
        }, {
            searchControlProvider: 'yandex#search'
        });
		
	add_text_to_map();
}
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

function add_text_to_map(){

}