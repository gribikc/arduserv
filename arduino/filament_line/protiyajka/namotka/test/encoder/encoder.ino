#define X_Lim   9
#define Y_Lim   10
#define Z_Lim   11

#define CLK X_Lim                         // Указываем к какому выводу CLK энкодер подключен к Arduino
#define DT Y_Lim                          // Указываем к какому выводу DT энкодер подключен к Arduino
#define SW Z_Lim                          // Указываем к какому выводу SW энкодер подключен к Arduino

class Encoder {
private:
    // Используем прямую работу с портами для максимальной скорости
    volatile uint8_t *portCLK, *portDT, *portSW;
    uint8_t maskCLK, maskDT, maskSW;
    
    int32_t absoluteCounter;
    int8_t relativeCounter;
    
    uint8_t lastStateCLK : 1;
    uint8_t buttonState : 1;
    uint8_t lastButtonState : 1;
    uint8_t buttonWasPressed : 1;
    uint8_t lastHoldEvent : 3;
    
    unsigned long buttonPressTime;
    unsigned long lastDebounceTime;
    unsigned long lastProcessTime; // Время последней обработки
    
    // Константы времени как статические константы
    static const unsigned long debounceDelay = 50;
    static const unsigned long holdDelay500 = 500;
    static const unsigned long holdDelay1000 = 1000;
    static const unsigned long holdDelay5000 = 5000;
    static const unsigned long minProcessInterval = 2; // Минимальный интервал между обработками (мс)

public:
    // Конструктор
    Encoder(uint8_t clk, uint8_t dt, uint8_t sw) : 
        absoluteCounter(0),
        relativeCounter(0),
        lastStateCLK(0),
        buttonState(HIGH),
        lastButtonState(HIGH),
        buttonWasPressed(false),
        lastHoldEvent(0),
        buttonPressTime(0),
        lastDebounceTime(0),
        lastProcessTime(0)
    {
        // Прямой доступ к портам для максимальной скорости чтения
        portCLK = portInputRegister(digitalPinToPort(clk));
        maskCLK = digitalPinToBitMask(clk);
        portDT = portInputRegister(digitalPinToPort(dt));
        maskDT = digitalPinToBitMask(dt);
        portSW = portInputRegister(digitalPinToPort(sw));
        maskSW = digitalPinToBitMask(sw);
        
        pinMode(clk, INPUT);
        pinMode(dt, INPUT);
        pinMode(sw, INPUT_PULLUP);
        
        lastStateCLK = (*portCLK & maskCLK) ? 1 : 0;
    }

    // Оптимизированный метод обработки с защитой от частых вызовов
    uint8_t doWork() {
        unsigned long currentTime = millis();
        
        // Защита от слишком частых вызовов
        if (currentTime - lastProcessTime < minProcessInterval) {
            return 0;
        }
        lastProcessTime = currentTime;
        
        uint8_t event = 0;

        // Обработка вращения энкодера
        uint8_t currentStateCLK = (*portCLK & maskCLK) ? 1 : 0;
        if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {
            uint8_t dtState = (*portDT & maskDT) ? 1 : 0;
            if (dtState != currentStateCLK) {
                absoluteCounter--;
                relativeCounter--;
            } else {
                absoluteCounter++;
                relativeCounter++;
            }
            event = 2;
        }
        lastStateCLK = currentStateCLK;

        // Обработка кнопки
        uint8_t reading = (*portSW & maskSW) ? HIGH : LOW;
        
        if (reading != lastButtonState) {
            lastDebounceTime = currentTime;
        }

        if ((currentTime - lastDebounceTime) > debounceDelay) {
            if (reading != buttonState) {
                buttonState = reading;
                
                if (buttonState == LOW) {
                    buttonPressTime = currentTime;
                    lastHoldEvent = 0;
                    buttonWasPressed = true;
                    event = 3;
                } else {
                    if (buttonWasPressed) {
                        event = 4;
                        buttonWasPressed = false;
                    }
                    lastHoldEvent = 0;
                }
            }
        }

        lastButtonState = reading;

        // Обработка удержания
        if (buttonState == LOW && buttonWasPressed) {
            unsigned long holdTime = currentTime - buttonPressTime;
            uint8_t newHoldEvent = lastHoldEvent;
            
            if (holdTime >= holdDelay5000 && lastHoldEvent < 7) {
                newHoldEvent = 7;
            } else if (holdTime >= holdDelay1000 && lastHoldEvent < 6) {
                newHoldEvent = 6;
            } else if (holdTime >= holdDelay500 && lastHoldEvent < 5) {
                newHoldEvent = 5;
            }
            
            if (newHoldEvent != lastHoldEvent) {
                event = newHoldEvent;
                lastHoldEvent = newHoldEvent;
            }
        }

        return event;
    }

    // Метод для принудительной обработки (игнорируя таймаут)
    uint8_t doWorkForce() {
        lastProcessTime = 0; // Сбрасываем таймер
        return doWork();
    }

    // Быстрый inline метод для получения абсолютного значения
    inline int32_t getAbsolute() const {
        return absoluteCounter;
    }

    // Быстрый inline метод для относительного изменения
    inline int8_t getRelative() {
        int8_t result = relativeCounter;
        relativeCounter = 0;
        return result;
    }

    // Быстрая установка абсолютного значения
    inline void setAbsolute(int32_t value) {
        absoluteCounter = value;
    }

    // Быстрый сброс
    inline void resetRelative() {
        relativeCounter = 0;
    }
    
    // Дополнительный метод для проверки, нажата ли кнопка в данный момент
    inline bool isButtonPressed() const {
        return buttonState == LOW;
    }
    
    // Метод для изменения минимального интервала обработки
    //inline void setMinInterval(unsigned long interval) {
    //    minProcessInterval = interval;
    //}
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