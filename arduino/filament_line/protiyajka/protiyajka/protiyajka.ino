#include "GR_digital_micrometer.h"

int data_pin = 13; //шина данных
int clk_pin = 14; //шина clock


GR_digital_micrometer izm(data_pin,clk_pin);

void obrv(float data){
  Serial.println(data,3);
};

void setup(){ 
  Serial.begin(115200); 
  //izm.set_obr(obrv);
  attachInterrupt(clk_pin,[](){izm.get_bit();},RISING);

  delay(500);
}

void loop(){ 
  if(izm.doit()){
    obrv(izm.get_izm());
  }
} 


