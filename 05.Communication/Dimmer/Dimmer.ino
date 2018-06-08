/*
通过串口输入数据来控制led亮度
*/

int ledPin = LED_BUILTIN;

void setup() {
	Serial.begin(9600); 
    pinMode(ledPin, OUTPUT);
}

void loop() {
    int brightness;

    // 检测串口是否有数据输入
    if (Serial.available()) {
        // 读取串口最近一次的一个byte数据，并转化范围到pwm的范围内
        brightness = map(Serial.read(), 0, 255, 0, 65535);

        Serial.print("brightness:");
        Serial.println(brightness);
        pwmWrite(ledPin, brightness);
    }
    delay(20);
}
