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
	



String print_reset_reason(int reason) {
  switch (reason) {
    case 1:  return "POWERON_RESET"; break;          /**<1,  Vbat power on reset*/
    case 3:  return "SW_RESET"; break;               /**<3,  Software reset digital core*/
    case 4:  return "OWDT_RESET"; break;             /**<4,  Legacy watch dog reset digital core*/
    case 5:  return "DEEPSLEEP_RESET"; break;        /**<5,  Deep Sleep reset digital core*/
    case 6:  return "SDIO_RESET"; break;             /**<6,  Reset by SLC module, reset digital core*/
    case 7:  return "TG0WDT_SYS_RESET"; break;       /**<7,  Timer Group0 Watch dog reset digital core*/
    case 8:  return "TG1WDT_SYS_RESET"; break;       /**<8,  Timer Group1 Watch dog reset digital core*/
    case 9:  return "RTCWDT_SYS_RESET"; break;       /**<9,  RTC Watch dog Reset digital core*/
    case 10: return "INTRUSION_RESET"; break;        /**<10, Instrusion tested to reset CPU*/
    case 11: return "TGWDT_CPU_RESET"; break;        /**<11, Time Group reset CPU*/
    case 12: return "SW_CPU_RESET"; break;           /**<12, Software reset CPU*/
    case 13: return "RTCWDT_CPU_RESET"; break;       /**<13, RTC Watch dog Reset CPU*/
    case 14: return "EXT_CPU_RESET"; break;          /**<14, for APP CPU, reset by PRO CPU*/
    case 15: return "RTCWDT_BROWN_OUT_RESET"; break; /**<15, Reset when the vdd voltage is not stable*/
    case 16: return "RTCWDT_RTC_RESET"; break;       /**<16, RTC Watch dog reset digital core and rtc module*/
    default: return "NO_MEAN";
  }
  return "!!!";
}

String verbose_print_reset_reason(int reason) {
  switch (reason) {
    case 1:  return "Vbat power on reset"; break;
    case 3:  return "Software reset digital core"; break;
    case 4:  return "Legacy watch dog reset digital core"; break;
    case 5:  return "Deep Sleep reset digital core"; break;
    case 6:  return "Reset by SLC module, reset digital core"; break;
    case 7:  return "Timer Group0 Watch dog reset digital core"; break;
    case 8:  return "Timer Group1 Watch dog reset digital core"; break;
    case 9:  return "RTC Watch dog Reset digital core"; break;
    case 10: return "Instrusion tested to reset CPU"; break;
    case 11: return "Time Group reset CPU"; break;
    case 12: return "Software reset CPU"; break;
    case 13: return "RTC Watch dog Reset CPU"; break;
    case 14: return "for APP CPU, reset by PRO CPU"; break;
    case 15: return "Reset when the vdd voltage is not stable"; break;
    case 16: return "RTC Watch dog reset digital core and rtc module"; break;
    default: return "NO_MEAN";
  }
  return "!!!";
}
	
