
void wifi_do_all(){
  //Проверка статуса подключения
    if(wifi_state_tg.status!=WiFi.status()){
      wifi_state_tg.status=WiFi.status();
      if(wifi_state_tg.status == WL_CONNECTED){
        tcp_ip.begin(TCP_PORT);
        tcp_ip.setNoDelay(true);
		#ifdef DEBUG_ON
			debug_stream->println("WiFi: AP connected!");
			debug_stream->print("WiFi: IP address: ");
			debug_stream->println(WiFi.localIP());
		#endif
        if(MDNS.begin(WIFI_DNAME)){
			#ifdef DEBUG_ON
				debug_stream->println("WiFi: MDNS responder started");
			#endif
        }
      }else{
			#ifdef DEBUG_ON
				debug_stream->println("WiFi: AP DISconnected!");
			#endif
      }
    }
  //Проверка новых подключившихся
    if(wifi_state_tg.status == WL_CONNECTED){
      if (tcp_ip.hasClient()){
        for(i = 0; i < TCP_MAX_SRV_CLIENTS; i++){
          if (!tcp_ipClients[i] || !tcp_ipClients[i].connected()){
            if(tcp_ipClients[i]){
				tcp_ipClients[i].stop();
			}
            tcp_ipClients[i] = tcp_ip.available();
				#ifdef DEBUG_ON
					if (!tcp_ipClients[i]){
						debug_stream->println("WiFi: available broken");
					}
					debug_stream->print("WiFi: New client: ");
					debug_stream->print(i);
					debug_stream->print(' ');
					debug_stream->println(tcp_ipClients[i].remoteIP());
				#endif
				//!!!tcp_uart=&tcp_ipClients[i];
            break;
          }
        }
        if (i >= TCP_MAX_SRV_CLIENTS) {
			tcp_ip.available().stop();
			#ifdef DEBUG_ON
				debug_stream->println("WiFi:  NO available broken");
			#endif
        }
      }  
    }else {
		for(i = 0; i < TCP_MAX_SRV_CLIENTS; i++) {
			if (tcp_ipClients[i]){
				tcp_ipClients[i].stop();
			}
		}
    }
  //
}