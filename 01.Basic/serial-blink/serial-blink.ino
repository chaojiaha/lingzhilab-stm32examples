/*
*	简单点灯，串口输出
*/

void setup() { 
  Serial.begin(9600);
	
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
	
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
	
  Serial.println("hello, 世界!");
}