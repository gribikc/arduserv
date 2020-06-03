#define FILESYSTEM SPIFFS
#define FORMAT_FILESYSTEM false
#define DBG_OUTPUT_PORT Serial
#include <WebServer.h>
#include <SPIFFS.h>

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
		//WebServer server(80);
		WebServer *server;
		
		String getContentType(String filename);
		bool exists(String path);
		bool handleFileRead(String path);
		void handleFileList();
		void write_db();
		String formatBytes(size_t bytes);
		
		Web_server_gr();
		void init();
		void do_web();
		
		
	private:	
	protected:
};
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
            output += ',';
          }
          output += "{\"type\":\"";
          output += (file.isDirectory()) ? "dir" : "file";
          output += "\",\"name\":\"";
          output += String(file.name()).substring(1);
          output += "\"}";
          file = root.openNextFile();
      }
  }
  output += "]";
  server->send(200, "text/json", output);
}
//////////////////////////////////////
void Web_server_gr::write_db() {
	String data=server->arg((server->args()-1));
	DBG_OUTPUT_PORT.println(data);
	for(int k=0;k<server->args();k++){
		DBG_OUTPUT_PORT.println(server->arg(i));
	}
	
	String filename=server->arg("base_name");
	if (!filename.startsWith("/")) {
      filename = "/" + filename;
    }
	File file = FILESYSTEM.open(filename, "w");
	uint8_t a;
	for(int i=0;i<data.length();i++){
		a=data.charAt(i);
		file.write(&a,1);
	}
    file.close();
	
	String output = "OK";
	server->send(200, "text/json", output);
}
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
///////////////////////////////
Web_server_gr::Web_server_gr(){
	server=new WebServer(80);
}
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
		if (!handleFileRead(server->uri())) {
			server->send(404, "text/plain", "FileNotFound");
		}
	});
	server->on("/test", HTTP_GET, [this]() {
		String json = "TEST:OK;";
		server->send(200, "text/json", json);

	});
	server->on("/list", HTTP_GET, [this]() {
		handleFileList();
	});
	server->on("/db/w",HTTP_POST,[this]() {
		write_db();
	});
	server->on("/help", HTTP_GET, [this]() {
		String 	json  = "Hello world!!!;\n";
				json += "/list?dir=/: File List\n";
				json += "/neme.exp: Get File\n";
				json +="Temperature: ";
				json += ((temprature_sens_read() - 32) / 1.8);
		server->send(200, "text/plain", json);
	});

        //server->pathArg()

	server->begin();
	DBG_OUTPUT_PORT.println("HTTP server started");
}
/////////////////////////////
void Web_server_gr::do_web(){
	server->handleClient();
}
