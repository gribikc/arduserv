#include "def.h"
#include "Encoder.h"
#include "GR_step_driver.h"


GR_step_driver sm_prot(X_STP,X_DIR,MOT_EN,true);//true/false направление вращение двигателя
Encoder enc(X_Lim, Y_Lim, Z_Lim);

#define To 65496    //65336-10кгц//65496-50кгц
bool tmr_flg=false;
ISR(TIMER1_OVF_vect){
  TCNT1 = To; // Timer Preloading
  tmr_flg=true;
}

void setup() {
  pinMode(Led, OUTPUT);
  Serial.begin(115200);
  Serial.println("Begin...");

  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= B00000010;
  TCNT1 = To;
  TIMSK1 |= B00000001;

  sm_prot.set_ob_sec(0.25);//0.00003-примерно 0.5 обсек!!!
  Serial.println(sm_prot.get_inc());
  Serial.println(sm_prot.get_freq(),6);
  Serial.println(sm_prot.get_ob_sec(),6);

  Serial.println("===");
  //sm_prot.set_freq(200.0);
  Serial.println(sm_prot.get_freq());
  Serial.println(sm_prot.get_inc());
  Serial.println(sm_prot.get_ob_sec());
}


void loop(){
  if(tmr_flg){
    tmr_flg=false;
    sm_prot.doit();
  }

  uint8_t event = enc.doWork();
    
    switch (event) {
        case 0:
            // Нет события
            break;
        case 2:
            Serial.print("Rotation | Absolute: ");
            Serial.print(enc.getAbsolute());
            Serial.print(" | Relative: ");
            sm_prot.inc_ob_sec(-enc.getRelative()*0.01);
            Serial.println(sm_prot.get_ob_sec(),6);
            //sm_prot.set_ob_sec(0.25);
            break;
        case 3:
            Serial.println("Button pressed");
            if(sm_prot.get_ob_sec()<0.01){
              sm_prot.set_ob_sec(0.25);
            }else{
              sm_prot.set_ob_sec(0.0);
            }
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

}
