/*
*	检测按键输入，来控制LED灯的亮和灭
*/

#define KEY  	BOARD_BUTTON_PIN  //板载按键

void setup() { 
  Serial.begin(9600);
  pinMode(KEY, INPUT);
	
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
	
  digitalWrite(LED_BUILTIN, HIGH);
	
  if(digitalRead(KEY) == LOW) {
	  //消除抖动的影响
	delay(10);
	if(digitalRead(KEY) == LOW) {
		Serial.println("按键按下了");
		digitalWrite(LED_BUILTIN, LOW);
		
		//等待按键释放
		while(digitalRead(KEY) == LOW) {
			delay(10);
		}
	}
  }
}