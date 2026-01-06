#include "GR_step_driver.h"

// Структура параметров намотчика
struct WindingParams {
    float spoolWidth;     // Ширина шпули (мм)
    float targetDiameter; // Целевой диаметр намотки (мм)
    float mainSpeed;      // Скорость главного мотора (об/сек)
    float gearRatio;      // Передаточное отношение
    int32_t stepsPerRev;  // Шагов на оборот
    int32_t stepsPerMm;   // Шагов на мм
    
    WindingParams() : 
        spoolWidth(100.0f), 
        targetDiameter(10.0f), 
        mainSpeed(5.0f),
        gearRatio(1.0f),
        stepsPerRev(200),
        stepsPerMm(1600) {}
};

// Класс управления намотчиком
class WindingMachine {
  private:
    // Состояния машины
    enum State {
        STATE_IDLE = 0,        // Ожидание (пауза)
        STATE_WINDING = 1,     // Намотка
        STATE_PARKING = 2,     // Парковка (возврат в начало)
        STATE_HOMING = 3,      // Поиск нуля
        STATE_EMERGENCY = 4,   // Аварийная остановка
        STATE_CALIBRATION = 5  // Калибровка
    };
    
    GR_step_driver& mainMotor;
    GR_step_driver& layingMotor;

    State currentState;
    State previousState;

    //bool isInitialized;
    //bool isPaused;

    int parking_stage=0;
    bool is_parking=false;

    int work_mode=0;

  public:
    // Конструктор
    WindingMachine(GR_step_driver& main, GR_step_driver& laying):
        mainMotor(main),
        layingMotor(laying)
    {
        currentState = STATE_IDLE;
        previousState = STATE_IDLE;
        //isInitialized = false;
        //isPaused = false;
        
        is_parking = false;
        parking_stage=0;

        work_mode=0;
    }
    
    // Инициализация
    void begin() {
        //по идее тут остоновка двигателей
        //инициализация парковки
        //сброс обометров
        //типа мягкого-среднего сброса

        Serial.println("WM:begin()");sys_info.write("WM:begin()");
        main_mot.set_ob_sec(0);
        laying_mot.set_ob_sec(0);
        main_mot.odometr_reset();
        laying_mot.odometr_reset();
        is_parking=false;
        work_mode=0;
        parking_stage=0;

    }

    void play_pause(){
        if(!is_parking){
            return;
        }
        if(work_mode!=0){
            pause();
            return;
        }
        if(work_mode==0){
            play();
            return;
        }
    }

    void pause(){
        if(!is_parking){
            return;
        }
        if(work_mode!=0){
            work_mode=0;
            Serial.println("WM:Пауза намотки");sys_info.write("WM:Пауза намотки");
            main_mot.set_ob_sec(0);
            laying_mot.set_ob_sec(0);
            return;
        }
    }

    void play(){
        if(!is_parking){
            return;
        }
        if(work_mode==0){
            work_mode=1;
            Serial.println("WM:Старт намотки");sys_info.write("WM:Старт намотки");
            main_mot.set_ob_sec(eedat_upr.speed_main);
            laying_mot.set_ob_sec(eedat_upr.speed_main*eedat_upr.target_diametr);
            
            //laying_mot.go_to((eedat_upr.spool_width-eedat_upr.target_diametr*1)*8*200);//targett_d
            if(laying_mot.get_odometr()==0){
                laying_mot.go_to((eedat_upr.spool_width-eedat_upr.target_diametr*1)*8*200);
                Serial.println("WM:Идём в верх");sys_info.write("WM:Идём в верх");
            }else if(laying_mot.get_odometr()==(eedat_upr.spool_width-eedat_upr.target_diametr*1)*8*200){
                laying_mot.go_to(0);
                Serial.println("WM:Идём в низ");sys_info.write("WM:Идём в низ");
            }
            return;
        }
    }

    // Рабочий режим
    void doit() {
        if(!is_parking){
            Parking();
            return;
        }
 
        if(work_mode==1){ 
            if(laying_mot.get_ob_sec()==0.0f){
                if(laying_mot.get_odometr()==0){
                    laying_mot.go_to((eedat_upr.spool_width-eedat_upr.target_diametr*1)*8*200);
                }else{
                    laying_mot.go_to(0);
                }
                laying_mot.set_ob_sec(main_mot.get_ob_sec()*eedat_upr.target_diametr);
                Serial.print("WM:Програмный концевик(Мотор остановлен) ; Одометр:"); Serial.println(laying_mot.get_odometr());
                sys_info.write("WM:Програмный концевик(Мотор остановлен)");
            }
        }

        //if(work_model.w_mode==2){
        //    work_model.w_mode=1;
        //        //Старт намотки
        //        Serial.println("Старт намотки");
        //        main_mot.set_ob_sec(eedat_upr.speed_main);
        //        laying_mot.set_ob_sec(eedat_upr.speed_main*eedat_upr.target_diametr);
        //        laying_mot.go_to((eedat_upr.spool_width-eedat_upr.target_diametr*1)*8*200);//targett_d
        //        Serial.print("To:"); Serial.println((eedat_upr.spool_width-eedat_upr.target_diametr)*8*200);
        //}

        //if(work_model.w_mode==3){
        //    work_model.w_mode=0;
        //        //Стоп намотки
        //        Serial.println("Стоп намотки");
        //        main_mot.set_ob_sec(0);
        //        laying_mot.set_ob_sec(2);
        //        laying_mot.go_to(0);//targett_d
        //        Serial.print("To:"); Serial.println((eedat_upr.spool_width-eedat_upr.target_diametr)*8*200);
        //}

    }
 
    private:
    
    //Парковка
    void Parking(){
        //0 нейтраль
        //1 нижний концевик
        main_mot.set_ob_sec(0);
        bool llps= lay_pos_button.update();
        switch(parking_stage) {
            case 0://запуск мотора в нужную сторону по датчику
                Serial.println("WM:Парковка...");sys_info.write("WM:Парковка...");
                for(int i=0;i<15;i++){
                    llps= lay_pos_button.update();
                }
                laying_mot.dir(llps);
                laying_mot.set_ob_sec(2);
                ++parking_stage;
                break;
            case 1://если концевик то идём в верх!!!тут нужно хорошо проверитЬ!!!
                laying_mot.dir(llps);
                if(!llps){//!!!
                    ++parking_stage;
                    //Serial.println("WM:Идём в низ до концевика...");
                }
                break;
            case 2://идём в низ до концевика
                laying_mot.dir(llps);
                if(llps){//!!!
                    ++parking_stage;
                    //Serial.println("WM:Нижний концевик сработал...");
                    laying_mot.dir(true);
                    laying_mot.odometr_reset();//вроде не надо
                    laying_mot.go_inc( (eedat_upr.lay_offset+eedat_upr.spool_thickness+eedat_upr.target_diametr*0.0)*8*200 ) ;//разбить на 2 функциональных вызов
                    //laying_mot.set_ob_sec(0);//!!!
                }
                break;
            case 3://ждём парковку по отступам
                if(!(laying_mot.get_ob_sec()>0.00001)){
                    ++parking_stage;
                }
                break;
            case 4://припарковались
                Serial.print("WM:Скорость:");Serial.println(laying_mot.get_ob_sec());
                Serial.print("WM:Одометр:"); Serial.println(laying_mot.get_odometr());
                laying_mot.odometr_reset();
                Serial.print("WM:Одометр:"); Serial.println(laying_mot.get_odometr());
                Serial.println("WM:Парковка по отступу...завершена");
                sys_info.write("WM:Парковка по отступу...завершена");
                is_parking=true;
                break;
        }

    }

};
