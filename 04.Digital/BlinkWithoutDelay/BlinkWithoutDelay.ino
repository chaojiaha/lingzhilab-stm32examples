/*
 led灯的闪烁效果，但是不使用delay来实现
*/

// Variables:
int previousMillis = 0;        // 存取led上一次状态改变的时间
int interval = 1000;            //在闪烁时的内部计数时间ms

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

    if (millis() - previousMillis > interval) {
        // 前一次led状态改变的时间
        previousMillis = millis();

        // 如果led已经打开，则关闭，否则反之
        digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
    }
}
