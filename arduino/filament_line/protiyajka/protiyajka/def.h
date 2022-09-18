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

	//IZM
	#define PIN_data0 13 //шина данных
	#define PIN_clk0 14 //шина clock

	//MOT
	#define MOT_EN 27
	#define MOT_STEP 25
	#define MOT_DIR 26

//BT
	#define BT_DEV_NAME ""
	#define BT_DEV_KEY  ""

//WIFI
	#define TCP_PORT 483
	#define TCP_MAX_SRV_CLIENTS 3
	#define WIFI_DNAME "prot"
	
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
	
