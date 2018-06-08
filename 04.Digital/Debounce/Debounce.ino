/*
按键状态检测，去除抖动
*/

// Variables:
int ledState = HIGH;         //输出的当前电平状态
int buttonState;             // 输入的当前状态
int lastButtonState = LOW;   // 输入的前一次状态
int lastDebounceTime = 0;   // 前一次输出的状态
int debounceDelay = 50;     // 去抖动的延时时间

void setup() {
    pinMode(BOARD_BUTTON_PIN, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    //读取输入的状态
    int reading = digitalRead(BOARD_BUTTON_PIN);

    // 去除抖动
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        // 此次为真实的按键改变的状态
        buttonState = reading;
    }

    // 通过led指示按键状态的改变
    digitalWrite(LED_BUILTIN, buttonState);

    //存放上一次的按键状态
    lastButtonState = reading;
}
