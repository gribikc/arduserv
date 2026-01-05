#pragma once
class Button {
  private:
    int pin;              // Пин кнопки
    bool mode;            // Режим кнопки: true - подтяжка к VCC (нажатие = LOW), false - подтяжка к GND (нажатие = HIGH)
    bool state;           // Текущее стабильное состояние
    bool lastReading;     // Последнее считанное значение
    int count;            // Счетчик одинаковых состояний
    int threshold;        // Порог срабатывания для защиты от дребезга
    
    bool wasPressed;      // Флаг, что кнопка была нажата
    bool pressEventSent;  // Флаг, что событие нажатия уже отправлено
    bool releaseEventSent; // Флаг, что событие отпускания уже отправлено
    unsigned long pressTime;  // Время начала нажатия
    unsigned long lastHoldEvent;  // Код последнего события удержания
    
    // Пороги удержания (в миллисекундах)
    unsigned long holdDelay500 = 500;
    unsigned long holdDelay1000 = 1000;
    unsigned long holdDelay5000 = 5000;

  public:
    // Конструктор
    Button(int buttonPin, bool pullupMode = false, int debounceThreshold = 20) {
      pin = buttonPin;
      mode = pullupMode;
      threshold = debounceThreshold;
      state = mode ? HIGH : LOW; // Исходное состояние (отпущена)
      lastReading = state;
      count = 0;
      wasPressed = false;
      pressEventSent = false;
      releaseEventSent = false;
      pressTime = 0;
      lastHoldEvent = 0;
      
      // Настройка пина
      if (mode) {
        pinMode(pin, INPUT_PULLUP); // Включение внутренней подтяжки к VCC
      } else {
        pinMode(pin, INPUT); // Для кнопки с подтяжкой к GND
      }
    }

    // Обновление состояния с защитой от дребезга
    bool update() {
      bool currentReading = digitalRead(pin);

      if (currentReading == lastReading) {
        count++;
      } else {
        // Новое значение - сбрасываем счетчик
        count = 1;
        lastReading = currentReading;
      }

      // Если набрали нужное количество одинаковых показаний
      if (count >= threshold) {
        if (state != lastReading) {
          state = lastReading; // Меняем состояние
        }
        count = threshold; // Фиксируем счетчик
      }

      return state;
    }

    // Основной метод обработки событий кнопки
    // Возвращает код события:
    // 0 - нет события
    // 1 - кнопка нажата (переход из отпущена в нажата)
    // 2 - кнопка отпущена (переход из нажата в отпущена)
    // 3 - удержание 500 мс
    // 4 - удержание 1000 мс (1 сек)
    // 5 - удержание 5000 мс (5 сек)
    uint8_t doWork() {
      uint8_t event = 0;
      bool currentState = update();
      bool pressed = mode ? (currentState == LOW) : (currentState == HIGH);
      unsigned long currentTime = millis();

      // Определение нажатия
      if (pressed && !wasPressed) {
        wasPressed = true;
        pressTime = currentTime;
        lastHoldEvent = 0;
        pressEventSent = false; // Сброс флага нажатия
        releaseEventSent = false; // Сброс флага отпускания
      }
      
      // Определение отпускания
      if (!pressed && wasPressed) {
        wasPressed = false;
        if (!releaseEventSent) {
          event = 2; // Событие: кнопка отпущена
          releaseEventSent = true;
        }
        lastHoldEvent = 0;
        return event; // Возвращаем событие отпускания сразу
      }
      
      // Если кнопка нажата, отправляем событие нажатия (один раз)
      if (pressed && wasPressed && !pressEventSent) {
        event = 1; // Событие: кнопка нажата
        pressEventSent = true;
        // Не возвращаем сразу, чтобы можно было обработать и удержание
      }
      
      // Обработка удержания
      if (pressed && wasPressed) {
        unsigned long holdTime = currentTime - pressTime;
        
        // Проверка порогов удержания
        if (holdTime >= holdDelay5000 && lastHoldEvent < 5) {
          event = 5;
          lastHoldEvent = 5;
        } else if (holdTime >= holdDelay1000 && lastHoldEvent < 4) {
          event = 4;
          lastHoldEvent = 4;
        } else if (holdTime >= holdDelay500 && lastHoldEvent < 3) {
          event = 3;
          lastHoldEvent = 3;
        }
      }

      return event;
    }

    // Быстрый доступ к текущему состоянию (true - нажата, false - отпущена)
    bool getState() {
      bool currentState = update();
      return mode ? (currentState == LOW) : (currentState == HIGH);
    }

    // Проверка, нажата ли кнопка в данный момент
    bool isPressed() {
      return getState();
    }

    // Проверка, отпущена ли кнопка в данный момент
    bool isReleased() {
      return !getState();
    }

    // Проверка, была ли кнопка нажата и отпущена (одиночный клик)
    bool wasClicked() {
      static bool wasClickEvent = false;
      uint8_t event = doWork();
      
      if (event == 1) {
        wasClickEvent = true;
      } else if (event == 2 && wasClickEvent) {
        wasClickEvent = false;
        return true;
      }
      
      return false;
    }

    // Установка порогов удержания (в миллисекундах)
    void setHoldThresholds(unsigned long h500, unsigned long h1000, unsigned long h5000) {
      holdDelay500 = h500;
      holdDelay1000 = h1000;
      holdDelay5000 = h5000;
    }

    // Получение времени удержания (в миллисекундах)
    unsigned long getHoldTime() {
      if (isPressed() && wasPressed) {
        return millis() - pressTime;
      }
      return 0;
    }
    
    // Сброс всех состояний (например, при смене режима)
    void reset() {
      wasPressed = false;
      pressEventSent = false;
      releaseEventSent = false;
      lastHoldEvent = 0;
    }
};

// Пример использования:
/*
Button myButton(2); // Кнопка на пине 2 с подтяжкой к VCC (по умолчанию)

void setup() {
  Serial.begin(9600);
}

void loop() {
  uint8_t event = myButton.doWork();
  
  switch(event) {
    case 0:
      // Нет события - ничего не делаем
      break;
    case 1:
      Serial.println("Кнопка нажата");
      break;
    case 2:
      Serial.println("Кнопка отпущена");
      break;
    case 3:
      Serial.println("Удержание 500 мс");
      break;
    case 4:
      Serial.println("Удержание 1 сек");
      break;
    case 5:
      Serial.println("Удержание 5 сек");
      break;
  }
  
  delay(10); // Небольшая задержка для стабильности
}
*/