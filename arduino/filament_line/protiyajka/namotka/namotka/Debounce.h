class Debounce {
  private:
    int pin;              // Пин кнопки
    bool state;           // Текущее стабильное состояние
    bool lastReading;     // Последнее считанное значение
    int count;            // Счетчик одинаковых состояний
    int threshold;        // Порог срабатывания

  public:
    // Конструктор
    Debounce(int buttonPin, int thresholdCount = 5) {
      pin = buttonPin;
      threshold = thresholdCount;
      state = digitalRead(pin);
      lastReading = state;
      count = 0;
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

    // Быстрый доступ к текущему состоянию
    bool getState() {
      return state;
    }
};