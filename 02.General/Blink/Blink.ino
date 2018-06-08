/*
 让板载LED灯每秒闪烁一次
*/

void setup() {
    // 设置开发板上led对应的引脚为输出模式
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));// 先读出led脚的电平，如果为高就输出低，如果是低就输出高
    delay(1000);          // 延时1000ms，即1s
}
