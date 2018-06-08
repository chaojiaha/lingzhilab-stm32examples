/* 
*	使用ESP8266建立TCP服务器示例
*
*/
#include "esp8266.h"

#include <HardwareSerial.h>

#define	ssid		"ESP8266-TCP服务器"
#define	password	"12345678"
#define	serverPort	8081		// 开启的端口号

Esp8266 wifi;

#define serialDebug		Serial
#define serialEsp		Serial1

void setup() {

	delay(8000);				//等待一段时间，以便查看串口的调试信息

	
	serialDebug.begin(115200);
	serialEsp.begin(115200);

	
	wifi.begin(&serialEsp, &serialDebug);  
	

	if (wifi.enableAP(ssid, password)) {
		wifi.debugPrintln("AP成功开启！");
	}
	if (wifi.setMultiConnect()) {
		wifi.debugPrintln("开启多连接模式成功！");
	}	
	if (wifi.openTCPServer(serverPort, 180)) {   
		wifi.debugPrintln("开启TCP服务器成功！");
	}
	wifi.debugPrintln("服务器IP:" + wifi.getIP() + " 端口:" + String(serverPort));
	
}

void loop() {


	int state = wifi.getState();
	switch (state) {
	    case WIFI_NEW_MESSAGE: //从客户端接收到了新的信息，打印
	      wifi.debugPrintln(String(wifi.getWorkingID()) + ":" + wifi.getMessage()); // debug
	      wifi.sendMessage(wifi.getWorkingID(), wifi.getMessage());	// 把接收到的信息发送回给客户端
	      wifi.setState(WIFI_IDLE);
	      break;
	    case WIFI_CLOSED : 	// 如果客户机端口连接
	      wifi.debugPrintln(String(wifi.getFailConnectID()) + ":连接关闭！");
	      wifi.setState(WIFI_IDLE);
	      break;
	    case WIFI_IDLE :
	    {
	    	int state = wifi.checkMessage(); 
	    	wifi.setState(state);
	    	break;
	    }
	    case WIFI_CLIENT_ON ://客户端连接成功	
	    	wifi.sendMessage(wifi.getWorkingID(), "from ESP8266: Hello, www.lingzhilab.com");
	    	wifi.setState(WIFI_IDLE);
	    	break;
	}

}

