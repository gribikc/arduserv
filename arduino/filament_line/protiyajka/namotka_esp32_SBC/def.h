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

    	/*//IZM
    	#define PIN_data0 13 //шина данных
    	#define PIN_clk0 14 //шина clock
    
    	//MOT
    	#define MOT_EN 27
    	#define MOT_STEP 25
    	#define MOT_DIR 26*/

//УБ
  //MOT
    #define MOT_EN_P 17
    #define MOT_STEP_P 16
    #define MOT_DIR_P 4
	//MOT
    #define MOT_EN_S 19
    #define MOT_STEP_S 18
    #define MOT_DIR_S 5
	//T izm
		#define RT_0 	34
		#define RT_1 	35
		#define RT_2 	32
	//Heater
		#define Heat_0 23
		#define Heat_1 22
		#define Heat_2 21
	//D
		#define D33 	33
		#define D25 	25
	//IZM
    #define IZM_data 27 //шина данных
    #define IZM_clk 26 //шина clock
	//IO	
		#define lsS 14
		#define MOff 12
		#define lsP 13

		#define Servo0 15
		#define LedS	2

	//
		#define RXD0 3
		#define TXD0 1

		//#define PIN_LED		2
		#define LAY_S D25


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
	//#define DEBUG_ON 1
	#define targett_d 10*10*200
	#define Lay_Ki 0.5 //0.5 чуть быстрее
	

	
