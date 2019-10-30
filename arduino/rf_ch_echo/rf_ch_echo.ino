#include "TimerOne.h"

#define rf_in_pin 8

#define sred_cnt 10

int val=0;


int bit_cnt=0;
int major=0;

void setup() {
  Serial.begin(115200);
  pinMode(rf_in_pin, INPUT);

  Timer1.initialize(25);         // инициализировать timer1, и установить период 1/2 сек.
  Timer1.attachInterrupt(callback);  // прикрепить callback(), как обработчик прерывания по переполнению таймера
}

void loop() {
  
}

void callback(){
  val = digitalRead(rf_in_pin);
  bit_cnt++;
  major+=val;
  
  if(bit_cnt>=sred_cnt){
    if(major>=sred_cnt/2){
      Serial.println( "1" );
    }else{
      Serial.println( "0" );
    }
    bit_cnt=0;
    major=0;
  }
}
