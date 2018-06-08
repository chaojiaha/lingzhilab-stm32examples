/*
*	在模拟A7脚测量电压值，使用pwm输出控制LED灯达到呼吸灯的效果
*/

#define SENSOR_PIN	A7		//模拟引脚
#define LED_2		PWM6	//pwm引脚

void setup() { 
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT_ANALOG);
  pinMode(LED_2, PWM);
}

void loop() {

  int i = 0;
  for(i=1; i<256; i++) {
	pwmWrite(LED_2, i*i);
	delay(10);
  }
  for(i=255; i>0; i--) {
	pwmWrite(LED_2, i*i);
	delay(10);
  }
  
  int value = analogRead(SENSOR_PIN);
  Serial.print("value=");
  Serial.print(value);
  Serial.println();
}