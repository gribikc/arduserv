#include "def.h"
#include "Encoder.h"
#include "GR_step_driver.h"
#include "EEPROM.h"


GR_step_driver sm_prot(X_STP,X_DIR,MOT_EN,true);//true/false направление вращение двигателя
Encoder enc(X_Lim, Y_Lim, Z_Lim);
uint8_t event=0;
char mode=0;//0-stop//1-run

  ///Work Mode & EEPROM
    struct eedat_upr_def{
      float last_speed=0.5;
    }eedat_upr;

//Timer
  #define To 65496    //65336-10кГц //65436-20кГц //65469-30кГц  //65486-40кГц  //65496-50кГц
// #define To 65436  // 20 кГц  
// #define To 65469  // 30 кГц
// #define To 65486  // 40 кГц
  bool tmr_flg=false;
  ISR(TIMER1_OVF_vect){
    TCNT1 = To; // Timer Preloading
    tmr_flg=true;
  }

void setup() {
  pinMode(Led, OUTPUT);
  digitalWrite(Led,true);
  Serial.begin(115200);
  Serial.println("Begin...");
  delay(500);
  digitalWrite(Led,false);

  //Timer
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= B00000010;
    TCNT1 = To;
    TIMSK1 |= B00000001;

  sm_prot.set_ob_sec(0.0);//0.00003-примерно 0.5 обсек!!!
  mode=0;


  EEPROM.begin();
  if(EEPROM.read(0)==28){
      EEPROM.get(1, eedat_upr);
      Serial.println("EEPROM read");
  }else{
    Serial.println("EEPROM not valid!");
    EEPROM.put(1, eedat_upr);
    EEPROM.write(0, 28 );
    //EEPROM.commit();
    Serial.println("EEPROM reset");
  }
  Serial.print("defSpeed:");
  Serial.println(eedat_upr.last_speed);
}

void loop(){
  if(tmr_flg){
    tmr_flg=false;
    sm_prot.doit();
    event = enc.doWork();
  }

  //uint8_t event = enc.doWork();
    
    switch (event) {
        case 0:
            // Нет события
            break;
        case 2:
            //Serial.print("Rotation | Absolute: ");
            //Serial.print(enc.getAbsolute());
            //Serial.print(" | Relative: ");
            if(mode&1){
              sm_prot.inc_ob_sec(-enc.getRelative()*0.01);
            }else{
              Serial.println("run turn...");
              sm_prot.go_inc(enc.getRelative()*8288);//(8288==1;100000~12)
              sm_prot.set_ob_sec(eedat_upr.last_speed);
            }
            break;
        case 3:
            Serial.println("Button pressed");
            break;
        case 4:
            Serial.println("Button released");
            if(mode&2){
              mode^=2;
              Serial.println("Button hold runs");
              break;
            }

            if(~mode&1){
              sm_prot.set_ob_sec(eedat_upr.last_speed);
              Serial.print("Start...");
              Serial.println(eedat_upr.last_speed);
              mode|=1;
            }else if(mode&1){
              eedat_upr.last_speed=sm_prot.get_ob_sec();
              Serial.print("Stop...");
              Serial.println(eedat_upr.last_speed);
              sm_prot.set_ob_sec(0.0);
              mode^=1;
            }
            break;
        case 5:
            Serial.println("Button hold > 0.5s");
            break;
        case 6:
            Serial.println("Button hold > 1s");
            break;
        case 7:
            Serial.println("Button hold > 5s");
            Serial.println("EEPROM save...");
            EEPROM.put(1, eedat_upr);
            mode|=2;
            break;
    }

}
