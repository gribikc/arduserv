let nmea;// = new nmea_gr();
let datafall;// = new datafall_gr();
let sys_data;//=new xmlhttprq_stream_gr();
let message_db;

let test_paper;

//var xhr;// = new XMLHttpRequest();
//var xhr_read_point=0;
//var xhr_date = new Date;
//var xhr_fps=0;
//var xhr_bps=0;
//var xhr_temp;

var sys_data_param;
var test_cnt_stream_param;

var autoboat;
	var test=0;
			var gauge_speedometr=0;
			//////////
			/////////////////////////////////////
			var gauge_compass = 0;
			//////////
			//////////////////////////////////////
			var gauge_accuracy = 0;
			//////////
			//////////////////////////////////////
			var gauge_accelerometr = 0;



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////	
	function next_prev_main_wiev_div_in(rf){
		var i;
		var inner;
		var inner_count=document.getElementById("main_wiev_div").childElementCount;
		var vis_ch_tg=0;
		for(i=0;i<inner_count;i++){
			//document.getElementById("main_wiev_div").children[i].
			inner=document.getElementById("main_wiev_div").children[i];
			if(vis_ch_tg==1){
				inner.style.position="absolute";
				inner.style.visibility="hidden";
				inner.style.zIndex=-1;
			}else if(inner.style.visibility=="visible" || inner.style.position=="unset" ||
					 inner.style.zIndex=="unset"       || inner.style.visibility=="" ||
					 inner.style.position==""          || inner.style.zIndex==""){
				inner.style.position="absolute";
				inner.style.visibility="hidden";
				inner.style.zIndex=-1;
				
				//console.log(i);
				
				vis_ch_tg=1;
				if(rf=='f'){
					if( !(inner=document.getElementById("main_wiev_div").children[i+1]) ){
						inner=document.getElementById("main_wiev_div").children[0];
					}
					i++;
				}else{
					if( !(inner=document.getElementById("main_wiev_div").children[i-1]) ){
						inner=document.getElementById("main_wiev_div").children[inner_count-1];
						inner_count--;
					}
				}
				
				vis_ch_tg=1;
				inner.style.visibility="visible";
				inner.style.position="unset";
				inner.style.zIndex="unset";
			}
		}
	}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
	function test_send_data1(){
		xmlhttprq_test = new XMLHttpRequest();
		xmlhttprq_test.open('POST', 'http://192.168.0.101:3128/W/COM/28/57600/', true);//, true
		xmlhttprq_test.overrideMimeType('text/plain; charset=x-user-defined');
		xmlhttprq_test.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		var uint8 = new Uint8Array(2);
		uint8[0] = 1;
		uint8[1] = 2;
		xmlhttprq_test.send(uint8);
		//!!!xmlhttprq_test.abort();
		//xmlhttprq_test.send();
	}	
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//$(document).ready(function(){
function main_init(){

	//HUB

		//autoboat
		gps=new gps_gr();
	//_HUB
	//STREAM
		//arduino_uart
			gps_stream_param={//location.hostname
				url   : (document.location.protocol=="file:" ? "http://192.168.0.101:3128" : "" ) +"/dev/GPS/r/", //(document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/R/COM/28/57600/',//'http://localhost:3128/R/COM/28/57600/',//'http://192.168.0.122:3128/R/BT/HC-06/',//http://172.20.10.4:3128/R/BT/HC-06///http://192.168.0.122:3128/R/BT/HC-06/',//'/cgi-bin/stream_usart.sh',
				url_w : "http://192.168.0.44:3128/W/GPS/",//(document.location.protocol=="file:" ? "http://localhost:3128" : "" ) + '/W/COM/28/57600/',//'http://localhost:3128/W/COM/28/57600/',
				mime_type:'text/plain; charset=x-user-defined',
				status_div_name:"GPS:",
				//parser: new json_stream_parser_gr(gps),//new raw_parser_gr(message_hub),
				parser: new nt_json(gps),
				
				flush_en:true,
				auto_start:true,
				
				status_en:true,
				status_timer:1000,
				status_div:"xhr_status_div",
				status_div_status_css:"xmlhttprq_stream_gr_status",
				status_div_stat_css:"xmlhttprq_stream_gr_stat",
				
				reload_en:true,
				reload_time:1000
			};
			//new xmlhttprq_stream_gr(gps_stream_param);//'/cgi-bin/test_counter.sh',test_cnt_nmea,"xhr_status_div","TSTCNT:");//14*8*1=112
			gps_stream_param={
				url		:	"ws://192.168.0.101:3129/dev/gps/r",
				parser	:	new nt_json(gps)
			}
			new web_sock_stream_gr(gps_stream_param);
		//_arduino_uart
	///////////////////
			gauge_speedometr = new RadialGauge({
				renderTo: 'speedometr',
				width: 300,
				height: 300,
				units: "Km/h",
				minValue: 0,
				startAngle: 45,
				ticksAngle: 270,
				//valueBox: false,
				maxValue: 20,
				majorTicks: [
					"0",
					"1",
					"2",
					"3",
					"4",
					"5",
					"6",
					"7",
					"8",	
					"9",
					"10",
					"11",
					"12",
					"13",
					"14",
					"15",
					"16",
					"17",
					"18",	
					"19",
					"20"
				],
				minorTicks: 2,
				strokeTicks: true,
				highlights: [
					{
						"from": 10,
						"to": 20,
						"color": "rgba(200, 50, 50, .75)"
					}
				],
				colorPlate: "#fff",
				borderShadowWidth: 0,
				borders: false,
				needleType: "arrow",
				needleWidth: 2,
				needleCircleSize: 7,
				needleCircleOuter: true,
				needleCircleInner: false,
				animationDuration: 900,
				animationRule: "linear"
			}).draw();
			//////////
			/////////////////////////////////////
			gauge_compass = new RadialGauge({
				renderTo: 'compass',
				width: 300,
				height: 300,
				minValue: 0,
				maxValue: 360,
				majorTicks: [
					"N",
					"NE",
					"E",
					"SE",
					"S",
					"SW",
					"W",
					"NW",
					"N"
				],
				minorTicks: 22,
				ticksAngle: 360,
				startAngle: 180,
				strokeTicks: false,
				highlights: false,
				colorPlate: "#33a",
				colorMajorTicks: "#f5f5f5",
				colorMinorTicks: "#ddd",
				colorNumbers: "#ccc",
				colorNeedle: "rgba(240, 128, 128, 1)",
				colorNeedleEnd: "rgba(255, 160, 122, .9)",
				//valueBox: false,
				valueTextShadow: false,
				colorCircleInner: "#fff",
				colorNeedleCircleOuter: "#ccc",
				needleCircleSize: 15,
				needleCircleOuter: false,
				animationRule: "linear",
				needleType: "line",
				needleStart: 75,
				needleEnd: 99,
				needleWidth: 3,
				borders: true,
				borderInnerWidth: 0,
				borderMiddleWidth: 0,
				borderOuterWidth: 10,
				colorBorderOuter: "#ccc",
				colorBorderOuterEnd: "#ccc",
				colorNeedleShadowDown: "#222",
				borderShadowWidth: 0,
				animationTarget: "plate",
				units: "ᵍ",
				title: "DIRECTION",
				fontTitleSize: 19,
				colorTitle: "#f5f5f5",
				animationDuration: 900
			}).draw();
			//////////
			//////////////////////////////////////
			gauge_accuracy = new LinearGauge({
				renderTo: 'accuracy',
				width: 120,
				height: 300,
				units: "m",
				minValue: 0,
				maxValue: 20,
				majorTicks: [
					"0",
					"1",
					"2",
					"3",
					"4",
					"5",
					"6",
					"7",
					"8",	
					"9",
					"10",
					"11",
					"12",
					"13",
					"14",
					"15",
					"16",
					"17",
					"18",	
					"19",
					"20"
				],
				minorTicks: 2,
				strokeTicks: true,
				highlights: [
					{
						"from": 10,
						"to": 20,
						"color": "rgba(200, 50, 50, .75)"
					}
				],
				colorPlate: "#fff",
				borderShadowWidth: 0,
				borders: false,
				needleType: "arrow",
				needleWidth: 2,
				animationDuration: 900,
				animationRule: "linear",
				tickSide: "left",
				numberSide: "left",
				needleSide: "left",
				barStrokeWidth: 7,
				barBeginCircle: false,
				value: 3
			}).draw();
			//////////
			//////////////////////////////
			gauge_accelerometr = new RadialGauge({
				renderTo: 'accelerometr',
				width: 300,
				height: 300,
				units: "dm/s",
				title: "Ускорение",
				minValue: -10,
				maxValue: 10,
				majorTicks: [
					-10,
					-8,
					-6,
					-4,
					-2,
					0,
					2,
					4,
					6,
					8,
					10
				],
				minorTicks: 2,
				strokeTicks: true,
				highlights: [
					{
						"from": -50,
						"to": 0,
						"color": "rgba(0,0, 255, .3)"
					},
					{
						"from": 0,
						"to": 50,
						"color": "rgba(255, 0, 0, .3)"
					}
				],
				ticksAngle: 270,
				startAngle: 45,
				colorMajorTicks: "#ddd",
				colorMinorTicks: "#ddd",
				colorTitle: "#eee",
				colorUnits: "#ccc",
				colorNumbers: "#eee",
				colorPlate: "#222",
				borderShadowWidth: 0,
				borders: true,
				needleType: "arrow",
				needleWidth: 2,
				needleCircleSize: 7,
				needleCircleOuter: true,
				needleCircleInner: false,
				animationDuration: 900,
				animationRule: "linear",
				colorBorderOuter: "#333",
				colorBorderOuterEnd: "#111",
				colorBorderMiddle: "#222",
				colorBorderMiddleEnd: "#111",
				colorBorderInner: "#111",
				colorBorderInnerEnd: "#333",
				colorNeedleShadowDown: "#333",
				colorNeedleCircleOuter: "#333",
				colorNeedleCircleOuterEnd: "#111",
				colorNeedleCircleInner: "#111",
				colorNeedleCircleInnerEnd: "#222",
				valueBoxBorderRadius: 0,
				colorValueBoxRect: "#222",
				colorValueBoxRectEnd: "#333"
			}).draw();
			
			gauge_speedometr.value = 0;
			gauge_compass.value = 0;
			gauge_accuracy.value = 0;
			gauge_accelerometr.value=0;
}
