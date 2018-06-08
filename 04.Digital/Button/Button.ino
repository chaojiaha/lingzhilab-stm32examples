/*
按钮的检测
*/

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
 
  pinMode(BOARD_BUTTON_PIN, INPUT);
}

#define BUTTON_DEBOUNCE_DELAY 1
uint8 isButtonPressed(uint8 pin=BOARD_BUTTON_PIN,
                      uint32 pressedLevel=BOARD_BUTTON_PRESSED_LEVEL) {
    if (digitalRead(pin) == pressedLevel) {
        delay(BUTTON_DEBOUNCE_DELAY);
        while (digitalRead(pin) == pressedLevel)
            ;
        return true;
    }
    return false;
}

void loop() {
    //检测是否按键按下
    if (isButtonPressed()) {
        // 翻转led的电平
        digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
    }
}
