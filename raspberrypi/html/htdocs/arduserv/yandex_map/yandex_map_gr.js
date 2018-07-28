var myMap;
ymaps.ready(init);

function init() {
    // Создаем карту.
    myMap = new ymaps.Map("map", {
            center: [56.155172, 30.585121],
            zoom: 15
        }, {
            searchControlProvider: 'yandex#search'
        });
}
function yandex_map_add_deep_gr(x,y,deep){
	// Создаем круг.
    var myCircle = new ymaps.Circle([
        // Координаты центра круга.
        [55.76, 37.64],
        // Радиус круга в метрах.
        1
    ], {
        // Описываем свойства круга.
        // Содержимое балуна.
        balloonContent: "",
        // Содержимое хинта.
        hintContent: ""
    }, {
        // Задаем опции круга.
        // Включаем возможность перетаскивания круга.
        draggable: true,
        // Цвет заливки.
        // Последний байт (77) определяет прозрачность.
        // Прозрачность заливки также можно задать используя опцию "fillOpacity".
        fillColor: "#DB709350",
        // Цвет обводки.
        strokeColor: "#FFFFFF",
        // Прозрачность обводки.
        strokeOpacity: 0,
        // Ширина обводки в пикселях.
        strokeWidth: 0
    });

    // Добавляем круг на карту.
    myMap.geoObjects.add(myCircle);
}