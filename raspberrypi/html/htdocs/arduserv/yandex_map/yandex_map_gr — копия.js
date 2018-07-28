//var myMap;

// Дождёмся загрузки API и готовности DOM.
ymaps.ready(yandex_map_init_gr);

function yandex_map_init_gr () {
    // Создание экземпляра карты и его привязка к контейнеру с
    // заданным id ("map").
    var myMap = new ymaps.Map('map', {
        // При инициализации карты обязательно нужно указать
        // её центр и коэффициент масштабирования.
        center: [55.76, 37.64], // Москва
        zoom: 10,
		controls: ['zoomControl', 'typeSelector',  'fullscreenControl','RulerControl']//'searchControl''routeButtonControl'
    }, {
        searchControlProvider: 'yandex#search'
    });
	
	    // Создаем круг.
    var myCircle = new ymaps.Circle([
        // Координаты центра круга.
        [55.76, 37.60],
        // Радиус круга в метрах.
        10000
    ], {
        // Описываем свойства круга.
        // Содержимое балуна.
        balloonContent: "Радиус круга - 10 км",
        // Содержимое хинта.
        hintContent: "Подвинь меня"
    }, {
        // Задаем опции круга.
        // Включаем возможность перетаскивания круга.
        draggable: true,
        // Цвет заливки.
        // Последний байт (77) определяет прозрачность.
        // Прозрачность заливки также можно задать используя опцию "fillOpacity".
        fillColor: "#DB709377",
        // Цвет обводки.
        strokeColor: "#990066",
        // Прозрачность обводки.
        strokeOpacity: 0.8,
        // Ширина обводки в пикселях.
        strokeWidth: 5
    });

    // Добавляем круг на карту.
    myMap.geoObjects.add(myCircle);

	yandex_map_add_deep_gr();
	
}
function yandex_map_add_deep_gr(){
	// Создаем круг.
	var myCircle = new ymaps.Circle([
		// Координаты центра круга.
		[55.76, 37.60],
		// Радиус круга в метрах.
		10000
	], {
		// Описываем свойства круга.
		// Содержимое балуна.
		balloonContent: "",
		// Содержимое хинта.
		hintContent: ""
	}, {
		// Задаем опции круга.
		// Включаем возможность перетаскивания круга.
		draggable: false,
		// Цвет заливки.
		// Последний байт (77) определяет прозрачность.
		// Прозрачность заливки также можно задать используя опцию "fillOpacity".
		fillColor: "#DB709377",
		// Цвет обводки.
		strokeColor: "#990066",
		// Прозрачность обводки.
		strokeOpacity: 0.8,
		// Ширина обводки в пикселях.
		strokeWidth: 5
	});

	// Добавляем круг на карту.
	myMap.geoObjects.add(myCircle);
}