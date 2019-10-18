int i,j,k;
char a,b,c;
unsigned long long_timer_cnt=0;
unsigned long bme280_tcnt=0;

char rx_buf[32];


Sd2Card card;
SdVolume volume;
SdFile root;


gribikc_serial usb_serial;
gribikc_nrf24l01p nrf24l01p;

Adafruit_BME280 bme;

Stream* user_stream=&Serial;
Stream* dev_stream=&Serial;
