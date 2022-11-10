//CyberKot (он же... я же! Shadow)
//Скетч Arduino, выводящий данные с циркуля в COM-порт
//Версия для хабра
int dataIn = 13; //шина данных, можно менять
int clockIn = 14; //шина clock, не трогать, так надо (читайте про attachInterrupt)

int isin = 0; //д=1 мм=0 
int isfs = 0; //минус 
int index_1 = 0; //счётчик битов

unsigned long xData, oData; //новые показания и старые (потом будет понятно зачем)

int ledPin = 13; //мигалка на 13й вход (встроенная, чтоб понятно было, что ничего не повисло)
int ledState = LOW; //статус мигалки
long previousMillis = 0; //когда последний раз мигали
long interval = 500; // интервал мигания

long previousGetMillis = 0;
long Timeout = 8; //таймаут чтения битов в мс

float stringOne; //временные переменные для вывода
char charBuf[5];
char charBuf2[8];

void setup(){ 
  digitalWrite (dataIn, 1); 
  digitalWrite (clockIn, 1); 
  pinMode (dataIn, INPUT); //привязываем шину данных на dataIn
  pinMode (clockIn, INPUT); //и clock на 2й вход
  attachInterrupt(clockIn,getBit,RISING); //и аттачим clock также на 2й вход
  
  Serial.begin(115200); 
  delay(500);
  
  index_1 = 0; 
  xData = 0; 
  oData = 999; 
}

void loop(){ 
if ((index_1 !=0) && (millis() - previousGetMillis > Timeout) ) { //обнуление по превышению таймаута
  index_1 = 0; 
  xData = 0; 
}; 

if (index_1 >23) { //если слово считано полностью
  if (oData !=xData) { 
    /* Этот вариант более изящен, по моему мнению, но съедает лишний килобайт
    if (isin==1){ //дюймы 
      Serial.print("inch: ");
      stringOne =xData*5/10000.00000;
      stringOne *=pow(-1,isfs);
      Serial.println(floatToString(charBuf2,stringOne,5,5)); 
    }else { //мм
      Serial.print("mm: ");
      stringOne =xData/100.00;
      stringOne *=pow(-1,isfs);
      Serial.println(floatToString(charBuf,stringOne,2,5));
    }; */
    if (isin==1){ //дюймы 
      if (isfs==1){ //минус
        Serial.print("inch: -");
      }else {
        Serial.print("inch: ");  
      }
      stringOne =xData*5/10000.00000; 
      Serial.println(floatToString(charBuf2,stringOne,5,5)); 
    }else { //мм
      if (isfs==1){ //минус
        Serial.print("mm: -");
      }else {
        Serial.print("mm: ");  
      }
      stringOne =xData/100.00;
      Serial.println(floatToString(charBuf,stringOne,2,5));
    }; 
  };
  oData =xData; 
  index_1=0; 
  xData=0; 
}; 

if (millis() - previousMillis > interval) { //мигалка
  previousMillis = millis(); 
  if (ledState == LOW) 
    ledState = HIGH; 
  else 
    ledState = LOW; 
  digitalWrite(ledPin, ledState); 
  } 
} 

void getBit(){ //чтение битов и флаги
previousGetMillis=millis(); 
if(index_1 < 20){ 
  if(digitalRead(dataIn)==1){ 
    xData|= 1<<index_1;
  } 
} else { 
  if (index_1==20) //минус
  isfs=digitalRead(dataIn); 
  
  if (index_1==23) //дюймы
  isin=digitalRead(dataIn); 
}; 

index_1++; 
} 

//функция для безгеморойного конверта переменной типа float в строку
char * floatToString(char * outstr, double val, byte precision, byte widthp){ //буфер под результат, число, точность (после запятой), минимальная длина
  char temp[16];
  byte i;

  //обсчёт округления 
  double roundingFactor = 0.5;
  unsigned long mult = 1;
  for (i = 0; i < precision; i++)
  {
    roundingFactor /= 10.0;
    mult *= 10;
  }
  
  temp[0]='\0';
  outstr[0]='\0';

  if(val < 0.0){
    strcpy(outstr,"-\0");
    val = -val;
  }

  val += roundingFactor;

  strcat(outstr, itoa(int(val),temp,10));  // целая часть
  if( precision > 0) {
    strcat(outstr, ".\0"); // дробная
    unsigned long frac;
    unsigned long mult = 1;
    byte padding = precision -1;
    while(precision--)
      mult *=10;

    if(val >= 0)
      frac = (val - int(val)) * mult;
    else
      frac = (int(val)- val ) * mult;
    unsigned long frac1 = frac;

    while(frac1 /= 10)
      padding--;

    while(padding--)
      strcat(outstr,"0\0");

    strcat(outstr,itoa(frac,temp,10));
  }

  // пробелы (для форматирования)
  if ((widthp != 0)&&(widthp >= strlen(outstr))){
    byte J=0;
    J = widthp - strlen(outstr);
    
    for (i=0; i< J; i++) {
      temp[i] = ' ';
    }

    temp[i++] = '\0';
    strcat(temp,outstr);
    strcpy(outstr,temp);
  }
  
  return outstr;
} 
