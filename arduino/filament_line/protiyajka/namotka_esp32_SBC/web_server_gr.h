#include <string>
#define FILESYSTEM SPIFFS
#define FORMAT_FILESYSTEM false
#define DBG_OUTPUT_PORT Serial
#include <WebServer.h>
#include <unordered_map>
#include <SPIFFS.h>
#include <Update.h>

 #ifdef __cplusplus
  extern "C" {
 #endif
 
  uint8_t temprature_sens_read();
 
#ifdef __cplusplus
}
#endif
 
uint8_t temprature_sens_read();

class Web_server_gr{
	#define FILESYSTEM SPIFFS
	#define FORMAT_FILESYSTEM false
	#define DBG_OUTPUT_PORT Serial
	typedef std::function<void(void)> THandlerFunction;
	public:
		Web_server_gr(){
			server=new WebServer(80);
		}

   void TaskDo(void *pvParameters){
    for(;;){
      do_web();
      //vTaskDelay(10);
    } 
   }

		void do_web(){
			server->handleClient();
		}

		//WebServer server(80);
		WebServer *server;
    
		String getContentType(String filename);
		bool exists(String path);
		bool handleFileRead(String path);
		void handleFileList();
		void write_db();
		String formatBytes(size_t bytes);

		int params();
		String param(int k);

		void init();


    std::unordered_map<std::string, std::string> get_map_param(){
      std::unordered_map<std::string, std::string> arguments_map;
      for (uint8_t i = 0; i < server->args(); ++i) {
        arguments_map[server->argName(i).c_str()]=server->arg(i).c_str(); //web_server.server->arg(i).c_str()
      }
      return arguments_map;
    }
		
		
	private:	
	protected:
};
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
	int Web_server_gr::params(){
		String url=server->uri();
		int url_len=url.length();
		int k=0;
		for(int i=0;i<url_len;i++){
			if(url[i]=='/'){
			  k++;
			}
		}
		return k;
	}
	String Web_server_gr::param(int k){
		String url=server->uri();
		int url_len=url.length();
		String str="";
		int cnt=0;
		for(int i=1;i<url_len;i++){
			if(url[i]=='/'){
				if(cnt==k){
					return str;
				}
				str="";
				cnt++;
			}else{
				str+=url[i];
			}
		}
		return str;
	}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
String Web_server_gr::formatBytes(size_t bytes) {
  if (bytes < 1024) {
    return String(bytes) + "B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + "KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  } else {
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
  }
}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
String Web_server_gr::getContentType(String filename) {
  if (server->hasArg("download")) {
    return "application/octet-stream";
  } else if (filename.endsWith(".htm")) {
    return "text/html";
  } else if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } else if (filename.endsWith(".png")) {
    return "image/png";
  } else if (filename.endsWith(".gif")) {
    return "image/gif";
  } else if (filename.endsWith(".jpg")) {
    return "image/jpeg";
  } else if (filename.endsWith(".ico")) {
    return "image/x-icon";
  } else if (filename.endsWith(".xml")) {
    return "text/xml";
  } else if (filename.endsWith(".pdf")) {
    return "application/x-pdf";
  } else if (filename.endsWith(".zip")) {
    return "application/x-zip";
  } else if (filename.endsWith("js.gz")) {
    return "gzip_types/application/javascript";
  } else if (filename.endsWith(".gz")) {
    return "application/x-gzip";
  }
  return "text/plain";
}
////////////////////////////////////////
bool Web_server_gr::exists(String path){
  bool yes = false;
  File file = FILESYSTEM.open(path, "r");
  if(!file.isDirectory()){
    yes = true;
  }
  file.close();
  return yes;
}
/////////////////////////////////////////////////
bool Web_server_gr::handleFileRead(String path) {
  DBG_OUTPUT_PORT.println("handleFileRead: " + path);
  if (path.endsWith("/")) {
    path += "index.htm";
  }
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (exists(pathWithGz) || exists(path)) {
    if (exists(pathWithGz)) {
      path += ".gz";
    }
    File file = FILESYSTEM.open(path, "r");
    server->streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}
//////////////////////////////////////
void Web_server_gr::handleFileList() {
  if (!server->hasArg("dir")) {
    server->send(500, "text/plain", "BAD ARGS");
    return;
  }

  String path = server->arg("dir");
  DBG_OUTPUT_PORT.println("handleFileList: " + path);


  File root = FILESYSTEM.open(path);
  path = String();

  String output = "[";
  if(root.isDirectory()){
      File file = root.openNextFile();
      while(file){
          if (output != "[") {
            output += ", \n ";
          }else{
            output += "\n ";            
          }
          output += "{\"type\":\"";
          output += (file.isDirectory()) ? "dir" : "file";
          output += "\",\"name\":\"";
          output += String(file.name());//.substring(1);//!!! тут вроде не надо обрезать символ
          output += "\"}";
          file = root.openNextFile();
      }
  }
  output += "\n]";
  //server->send(204);
  server->send(200, "text/json", output);
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////
  void Web_server_gr::write_db() {
    DBG_OUTPUT_PORT.println("================================================");
    DBG_OUTPUT_PORT.println("Write DB.");
    //if(server->hasArg("plain") && server->hasArg("file")){
	if(server->hasArg("plain") && params()>=4 && (server->method() == HTTP_POST)){
      //String file_name="/"+server->arg("file");
      String file_name="/db/"+param(2)+"/"+param(3);
      String data=server->arg("plain");
	  
      DBG_OUTPUT_PORT.println("File:"+file_name);
      //DBG_OUTPUT_PORT.println(data);
      if (exists(file_name)) {
        DBG_OUTPUT_PORT.println("File exists");
      }
      
	  File file = FILESYSTEM.open(file_name, "w");
      if (file) {
      	uint8_t a;
      	for(int i=0;i<data.length();i++){
      		a=data.charAt(i);
      		file.write(&a,1);
      	}
        file.close();
        server->send(200, "text/json", "Ok");
      }else{
        DBG_OUTPUT_PORT.println("File error");
        server->send(200, "text/json", "File error");
      }
    }else{
        server->send(200, "text/json", "Wrong Format");
    }
  }
/////////////////////////////////////////////////
void Web_server_gr::init(){
	FILESYSTEM.begin();
	{
		File root = FILESYSTEM.open("/");
		File file = root.openNextFile();
		while(file){
			String fileName = file.name();
			size_t fileSize = file.size();
			DBG_OUTPUT_PORT.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
			file = root.openNextFile();
		}
		DBG_OUTPUT_PORT.printf("\n");
	}
	server->enableCORS(1);


  
	server->onNotFound([this]() {
    DBG_OUTPUT_PORT.println("onNotFound start");
		if (handleFileRead(server->uri())) {//if file exist, send him!!!
			return;
		}
		
		String url=server->uri();
		if(url.startsWith("/db/w")){
			write_db();
			return;
		}

		server->send(404, "text/plain", "FileNotFound");
		//dbg
		DBG_OUTPUT_PORT.println("------------------------------------------------------");
		DBG_OUTPUT_PORT.print("Params:");
		DBG_OUTPUT_PORT.println(params());
		for(int k=0;k<params();k++){
			DBG_OUTPUT_PORT.println(param(k));
		}
		DBG_OUTPUT_PORT.println("---0");

		DBG_OUTPUT_PORT.println("---1");
  		String message = "";
  		message += "URI: ";
  		message += server->uri();
  		message += "\nMethod: ";
  		message += (server->method() == HTTP_GET) ? "GET" : "POST";
  		message += "\nArguments: ";
  		message += server->args();
  		message += "\n";
  		DBG_OUTPUT_PORT.println(message);
		DBG_OUTPUT_PORT.println("---2");
      message="";
  		for (uint8_t i = 0; i < server->args(); i++) {
  			message += "" + server->argName(i) + ":::::::::::::" + server->arg(i) + "\n---------------------------------------------------------\n";
  		}
      DBG_OUTPUT_PORT.println(message);
		DBG_OUTPUT_PORT.println("---3");
  		for (uint8_t i = 0; i < server->headers(); i++) {
  			DBG_OUTPUT_PORT.println(server->header(i)+"\n");
  		}
		DBG_OUTPUT_PORT.println("---4");
      String data=server->arg("plain");
		  uint8_t a;
      DBG_OUTPUT_PORT.print(data.length());
      DBG_OUTPUT_PORT.print(":");
      for(int i=0;i<data.length();i++){
        a=data.charAt(i);
        DBG_OUTPUT_PORT.write(&a,1);
      }
	});
 
	server->on("/test", HTTP_GET, [this]() {
		String str = "TEST:OK;";
		server->send(200, "text/json", str);
	});
  
  server->on("/_RESET_CPU_", HTTP_GET, [this]() {
		String str = "RESET CPU!!!";
		server->send(200, "text/json", str);
    ESP.restart();
	});
 
	server->on("/list", HTTP_GET, [this]() {
		handleFileList();
	});
  
	server->on("/help", HTTP_GET, [this]() {
		String 	html  = "<html><head></head><body>Hello world!!!;<br>\n";
				html += "<a href=\"/list?dir=/\">/list?dir=/: File List</a><br>\n";
        html += "<a href=\"/update\">UPDATE</a><br>\n";
				html += "/neme.exp: Get File<br>\n";
        html += "RSSI:";
        html += WiFi.RSSI();
				html +="<br>\nTemperature: ";
				html += ((temprature_sens_read() - 32) / 1.8);
        html += "<br>\nBild:";
        html += String(__DATE__) + " " + String(__TIME__) + " Ver:0.1";
        html += "<br>\n";
        html += "<a href=\"/\">Main page</a><br>\n";
        html += "<br>\n</body></html>";
		server->send(200, "text/html", html);
	});

  //UPDATE FIRMVARE
      server->on("/update", HTTP_GET, [this]() {
        server->sendHeader("Connection", "close");
        const char *serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";
        server->send(200, "text/html", serverIndex);
      });

      server->on(
        "/update", HTTP_POST,
        [this]() {
          server->sendHeader("Connection", "close");
          server->send(200, "text/plain", (Update.hasError()) ? "FAIL <a href=\"/\">Main page</a>" : "OK <a href=\"/\">Main page</a>");
          ESP.restart();
        },
        [this]() {
          HTTPUpload &upload = server->upload();
          if (upload.status == UPLOAD_FILE_START) {
            Serial.setDebugOutput(true);
            Serial.printf("Update: %s\n", upload.filename.c_str());
            if (!Update.begin()) {  //start with max available size
              Update.printError(Serial);
            }
          } else if (upload.status == UPLOAD_FILE_WRITE) {
            if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
              Update.printError(Serial);
            }
          } else if (upload.status == UPLOAD_FILE_END) {
            if (Update.end(true)) {  //true to set the size to the current progress
              Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
            } else {
              Update.printError(Serial);
            }
            Serial.setDebugOutput(false);
          } else {
            Serial.printf("Update Failed Unexpectedly (likely broken connection): status=%d\n", upload.status);
          }
        }
      );




	server->begin();
	DBG_OUTPUT_PORT.println("HTTP server started");

    //xTaskCreatePinnedToCore(      this->TaskDo    ,  "TaskBlink"      ,  1024*8      ,  NULL    ,  2      ,  NULL     ,  0);

 
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
