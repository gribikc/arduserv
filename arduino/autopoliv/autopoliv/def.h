//#PINMAP
//	#0-BOOT_MODE	#HIatBOOT???
//	#1-TX_BOOT		#HIatBOOT
//	#3-RX_BOOT		#HIatBOOT
//	#5-boot???		#HIatBOOT
//	#6-#11 flash	#HIatBOOT
//	#12-boot???
//	#14-boot???		#HIatBOOT
//	#15-boot???		#HIatBOOT
//	#34-only INPUT
//	#35-only INPUT
//	#36-only INPUT
//	#39-only INPUT

//BT
	#define BT_DEV_NAME "BAP"
	#define BT_DEV_KEY  "12345"

//WIFI
	#define TCP_PORT 483
	#define TCP_MAX_SRV_CLIENTS 3
	#define WIFI_DNAME "BAP"
	
	//#define WIFI_SSID	"***"
	//#define WIFI_KEY	"***"
	
	#define FILESYSTEM SPIFFS
	#define FORMAT_FILESYSTEM false
	#define DBG_OUTPUT_PORT Serial

//OTHER
	#define DEBUG_ON 1
	
//MY_DEF
	#define RXD0 	3
	#define TXD0 	1
	
	#define RXD1 	33//33//14
	#define TXD1 	32//32//2
	
	//#define RXD2 	27
	//#define TXD2 	28
	
	//#define PIN_LED		2

  #define PIN_SOLAR_VOLT  34
  #define PIN_BATT_VOLT  35
  #define PIN_RELE  4

	
//UART_STREAM_CONTROL
	#define CMT_BYTE 0
    #define CMT_FLOAT 1
    #define CMT_EXOT 2
    #define CMT_INT 3
    #define CMT_DOUBLE 4

    #define CMI_STD 0
    #define CMI_HEAD_S 4
    #define CMI_FOOT_S 4
    #define CMI_DATA_S 7
    #define CMI_MASK 31
    #define CMI_SIZE 4
