/*
模拟输入
*/

int sensorPin = 0;   // 模拟输入的引脚
int sensorValue = 0; //从传感器读取的数值存储到这个变量中

void setup() {
    // 配置引脚为模拟输入
    pinMode(sensorPin, INPUT_ANALOG);

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    // 从传感器读取
    sensorValue = analogRead(sensorPin);

    digitalWrite(LED_BUILTIN, HIGH);
    //读取的数值作为led开启和关闭的延时时间
    delay(sensorValue);
    digitalWrite(LED_BUILTIN, LOW);
    delay(sensorValue);
}
