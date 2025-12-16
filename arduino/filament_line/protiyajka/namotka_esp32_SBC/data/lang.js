const translations = {
	'en': {
		'upt_automatic_title'				: 'Automation Control',
		'upt_automatic_start'				: 'Start',
		'upt_automatic_stop'				: 'Stop' ,
		'upt_automatic_diameter_set'		: 'Set the diameter' ,
		'set'								: 'Set' ,
		'upt_automatic_diameter_AveragingIAD'	: 'Averaging' ,
		'motor_set'							: 'Сontrol Broach Motor' ,
		'motor_set_speed'					: 'RPS' ,
		'filament_diameter'					: 'Diameter of the filament' ,
		'motor_speed_graph'					: 'Motor speed' ,
		'eeprom_main'						: 'EEPROM Settings' ,
		'eeprom_read'						: 'Read' ,
		'eeprom_set_save'					: 'Save And Set' ,
		'eeprom_reset'						: 'Reset' ,
		
		'content': 'This is a sample text.',
		'footer': 'Choose your language'
	},
	'ru': {
		'upt_automatic_title'			: 'Управление Автоматикой',
		'upt_automatic_start'			: 'Старт',
		'upt_automatic_stop'			: 'Стоп',
		'upt_automatic_diameter_set'	: 'Уст. Диаметра' ,
		'set'							: 'Установит' ,
		'upt_automatic_diameter_AveragingIAD'	: 'Усреднение' ,
		'motor_set'	: 'Управление Мотором Протяжки' ,
		'motor_set_speed'				: 'Скорости об.сек' ,
		'filament_diameter'				: 'Диаметр филамента' ,
		'motor_speed_graph'				: 'Выход регулятора' ,
		'eeprom_main'					: 'Редактирование настроек EEPROM' ,
		'eeprom_read'					: 'Запросить' ,
		'eeprom_set_save'				: 'Установить и Сохранить' ,
		'eeprom_reset'					: 'Сброс EEPROM' ,
		
		'content': 'Это пример текста.',
		'footer': 'Выберите ваш язык'
	}
};

// Функция смены языка
function changeLanguage(lang) {
	// Сохраняем выбор языка в localStorage
	localStorage.setItem('selectedLanguage', lang);
	
	// Получаем все элементы с атрибутом data-translate
	const elements = document.querySelectorAll('[data-translate]');
	
	// Обновляем текст для каждого элемента
	elements.forEach(element => {
		const key = element.getAttribute('data-translate');
		if(element.nodeName=='INPUT'){
			element.value = translations[lang][key];
		}else{
			element.textContent = translations[lang][key];
			console.log(element.nodeName);
		}			
	});
}

// Инициализация языка при загрузке страницы
function initLanguage() {
	const savedLang = localStorage.getItem('selectedLanguage');
	const userLang = navigator.language.split('-')[0]; // Берем основной язык браузера
	//const defaultLang = savedLang || (translations[userLang] ? userLang : 'en');
	const defaultLang = savedLang || (translations[userLang] ? userLang : 'en');
	
	changeLanguage(defaultLang);
}

// Запускаем при загрузке страницы
//window.onload = initLanguage;
//initLanguage();