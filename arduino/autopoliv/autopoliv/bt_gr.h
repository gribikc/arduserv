void bt_do_all(){
	if(bt_state_tg.status!=SerialBT.hasClient()){
		bt_state_tg.status=SerialBT.hasClient();
		if(bt_state_tg.status==1){
			#ifdef DEBUG_ON
				debug_stream->println("BT: connected!");
			#endif
		}else{
			#ifdef DEBUG_ON
				debug_stream->println("BT: DISconnected!");
			#endif
		}
	}
}
