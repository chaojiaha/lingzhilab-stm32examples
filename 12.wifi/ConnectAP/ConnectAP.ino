// ConnectAP.ino

#include "esp8266.h"
#include <HardwareSerial.h>

#define	ssid		"test"			// you need to change the ssid and password to your wifi's name and password
#define	password	"12345678"

Esp8266 wifi;
bool flag=false;

#define serialDebug		Serial
#define serialEsp		Serial1

void setup() {

	delay(2000);				// it will be better to delay 2s to wait esp8266 module OK
	pinMode(13, OUTPUT);

	serialEsp.begin(115200);
	serialDebug.begin(115200);					
	wifi.begin(&serialEsp, &serialDebug);  //Serial is used to communicate with esp8266 module, mySerial is used to print debug message

	// if you use arduino leonardo ,you can use Serial to debut rather than software serial. like this
	// Serial.begin(115200);
	// while (!Serial) {
	// ; // wait for serial port to connect. Needed for Leonardo only
	// }
	// wifi.begin(&Serial1, &Serial);
	 

	if (wifi.connectAP(ssid, password)) {	  // it will return TRUE if it connect successfully 
		flag = true;
		wifi.debugPrintln("connected to AP"); // if you don't use a serial to debug, DON NOT use this function 
	} else { 
		wifi.debugPrintln("connect Fail");								
	}

 // 	if you don't want to use debug, you can write like below
	// Serial1.begin(115200);
	// wifi.begin(&Serial1);
	// if (wifi.connectAP(ssid, password)) {
	// 	flag = true;
	// }
	
}

void loop() {
	if (flag) {
	  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
	  delay(500);              // wait for 500ms
	  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
	  delay(500);              // wait for 500ms	
	}
}

