/*
LED的显示，本示例包含了10个led，这些led的引脚顺序是可以更改的
*/

const int analogPin = 0;    // 电位器连接的引脚
const int ledCount = 10;    // led的数量

int ledPins[] = {
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }; // 该数组保存led引脚号

void setup() {
    //设置模拟输入
    pinMode(analogPin, INPUT_ANALOG);
    // 设置数组中所有的led引脚模式
    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
        pinMode(ledPins[thisLed], OUTPUT);
    }
}

void loop() {
    // 读取电位
    int sensorReading = analogRead(analogPin);
    // 使用map进行范围映射
    int ledLevel = map(sensorReading, 0, 4095, 0, ledCount);

    for (int thisLed = 0; thisLed < ledCount; thisLed++) {

        if (thisLed < ledLevel) {
            digitalWrite(ledPins[thisLed], HIGH);
        }
        else {
            digitalWrite(ledPins[thisLed], LOW);
        }
    }
}
