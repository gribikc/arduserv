'use strict';
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//gps
	class simple_test_gr{
		constructor(hub){
			this.parser_data_array=new Array();
			this.hub_handler=hub;
			
			this.speed=0;
		}
		//////////
		//xdstartjson:{
		//}:xdstopjson
		parser_data(type,stream){
			key_array_to_inner(stream,"simple_test");
			//console.log(stream);
			

			/*for(var i=0;i<stream.length;i++){
				if(stream[i][0]=="$BME280"){
					key_array_to_inner(stream[i],"simple_test");
				}
				if(stream[i][0]=="$GNVLW"){
					key_array_to_inner(stream[i],"GNVLW");
				}
				
				if(stream[i][0]=="$GNGGA"){
					key_array_to_inner(stream[i],"GNGGA");
				}
			}*/
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
