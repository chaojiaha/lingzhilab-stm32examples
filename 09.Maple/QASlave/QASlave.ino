/*
   QA测试程序，所有的未使用的pin脚连接到运行qa测试程序的板子的相应的脚
*/

#define INTER_TOGGLE_DELAY_NORMAL 5
#define INTER_TOGGLE_DELAY_SLOW   80

void interToggleDelay(void);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(BOARD_BUTTON_PIN, INPUT);

    // 所有的未使用的pin脚设置
    for (int i = 0; i < BOARD_NR_GPIO_PINS; i++) {
        if (boardUsesPin(i))
            continue;
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
}

void loop() {
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
    delay(100);
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));

    for (int i = 0; i < BOARD_NR_GPIO_PINS; i++) {
        if (boardUsesPin(i))
            continue;

        digitalWrite(i, HIGH);

        interToggleDelay();

        digitalWrite(i, LOW);

        interToggleDelay();
    }
}

void interToggleDelay(void) {
    if (digitalRead(BOARD_BUTTON_PIN)) { 
        delay(INTER_TOGGLE_DELAY_SLOW);
    } else {
        delay(INTER_TOGGLE_DELAY_NORMAL);
    }
}
