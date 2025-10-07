#define X_Lim   9
#define Y_Lim   10
#define Z_Lim   11

#define CLK X_Lim                         // Указываем к какому выводу CLK энкодер подключен к Arduino
#define DT Y_Lim                          // Указываем к какому выводу DT энкодер подключен к Arduino
#define SW Z_Lim                          // Указываем к какому выводу SW энкодер подключен к Arduino

class Encoder {
private:
    int pinCLK, pinDT, pinSW;
    int absoluteCounter;
    int relativeCounter;
    int lastStateCLK;
    
    // Переменные для обработки кнопки
    bool buttonState;
    bool lastButtonState;
    unsigned long buttonPressTime;
    uint8_t lastHoldEvent;
    unsigned long lastDebounceTime;
    bool buttonWasPressed;
    
    // Константы времени
    const unsigned long debounceDelay = 50;
    const unsigned long holdDelay500 = 500;
    const unsigned long holdDelay1000 = 1000;
    const unsigned long holdDelay5000 = 5000;

public:
    // Конструктор
    Encoder(int clk, int dt, int sw) : 
        pinCLK(clk), 
        pinDT(dt), 
        pinSW(sw), 
        absoluteCounter(0),
        relativeCounter(0),
        lastStateCLK(0),
        buttonState(HIGH),
        lastButtonState(HIGH),
        buttonPressTime(0),
        lastHoldEvent(0),
        lastDebounceTime(0),
        buttonWasPressed(false)
    {
        pinMode(pinCLK, INPUT);
        pinMode(pinDT, INPUT);
        pinMode(pinSW, INPUT_PULLUP);
        lastStateCLK = digitalRead(pinCLK);
    }

    // Основной метод обработки - возвращает код события
    uint8_t doWork() {
        uint8_t event = 0; // 0 - нет события
        
        // Обработка вращения энкодера
        int currentStateCLK = digitalRead(pinCLK);
        if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {
            if (digitalRead(pinDT) != currentStateCLK) {
                absoluteCounter--;
                relativeCounter--;
            } else {
                absoluteCounter++;
                relativeCounter++;
            }
            event = 2; // Событие вращения
        }
        lastStateCLK = currentStateCLK;

        // Обработка кнопки с антидребезгом
        int reading = digitalRead(pinSW);
        
        if (reading != lastButtonState) {
            lastDebounceTime = millis();
        }

        if ((millis() - lastDebounceTime) > debounceDelay) {
            if (reading != buttonState) {
                buttonState = reading;
                
                if (buttonState == LOW) {
                    // Кнопка нажата
                    buttonPressTime = millis();
                    lastHoldEvent = 0; // Сбрасываем флаги удержания
                    buttonWasPressed = true;
                    event = 3; // Событие нажатия
                } else {
                    // Кнопка отпущена
                    if (buttonWasPressed) {
                        event = 4; // Всегда генерируем событие отпускания
                        buttonWasPressed = false;
                    }
                    lastHoldEvent = 0; // Сбрасываем флаги удержания
                }
            }
        }

        lastButtonState = reading;

        // Обработка удержания кнопки (только если кнопка нажата)
        if (buttonState == LOW && buttonWasPressed) {
            unsigned long holdTime = millis() - buttonPressTime;
            uint8_t newHoldEvent = 0;
            
            if (holdTime >= holdDelay5000 && lastHoldEvent < 7) {
                newHoldEvent = 7; // Удержание 5+ секунд
            } else if (holdTime >= holdDelay1000 && lastHoldEvent < 6) {
                newHoldEvent = 6; // Удержание 1+ секунд
            } else if (holdTime >= holdDelay500 && lastHoldEvent < 5) {
                newHoldEvent = 5; // Удержание 0.5+ секунд
            }
            
            // Генерируем событие только если нашли новое событие удержания
            if (newHoldEvent > 0 && newHoldEvent != lastHoldEvent) {
                event = newHoldEvent;
                lastHoldEvent = newHoldEvent;
            }
        }

        return event;
    }

    // Получение абсолютного значения счетчика
    int getAbsolute() {
        return absoluteCounter;
    }

    // Получение относительного изменения с момента последнего чтения
    int getRelative() {
        int result = relativeCounter;
        relativeCounter = 0; // Сбрасываем после чтения
        return result;
    }

    // Установка абсолютного значения счетчика
    void setAbsolute(int value) {
        absoluteCounter = value;
    }

    // Сброс относительного счетчика
    void resetRelative() {
        relativeCounter = 0;
    }
};

// Использование класса
Encoder enc(X_Lim, Y_Lim, Z_Lim);

void setup() {
    Serial.begin(9600);
}

void loop() {
    uint8_t event = enc.doWork();
    
    switch (event) {
        case 0:
            // Нет события
            break;
        case 2:
            Serial.print("Rotation | Absolute: ");
            Serial.print(enc.getAbsolute());
            Serial.print(" | Relative: ");
            Serial.println(enc.getRelative());
            break;
        case 3:
            Serial.println("Button pressed");
            break;
        case 4:
            Serial.println("Button released");
            break;
        case 5:
            Serial.println("Button hold > 0.5s");
            break;
        case 6:
            Serial.println("Button hold > 1s");
            break;
        case 7:
            Serial.println("Button hold > 5s");
            break;
    }
    
    delay(1);
}