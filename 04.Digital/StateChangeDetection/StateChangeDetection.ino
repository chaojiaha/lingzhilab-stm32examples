/*
检测按键状态改变
*/

int buttonPushCounter = 0;   // 按键按下的次数
int buttonState = 0;         // 按键当前的状态
int lastButtonState = 0;     // 前一次按键的状态

void setup() {
	Serial.begin(9600); 
    pinMode(BOARD_BUTTON_PIN, INPUT);

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    buttonState = digitalRead(BOARD_BUTTON_PIN);

    if (buttonState != lastButtonState) {

        if (buttonState == HIGH) {
            // 在串口中显示
            buttonPushCounter++;
            Serial.println("on");
            Serial.print("number of button pushes:  ");
            Serial.println(buttonPushCounter, DEC);
        }
        else {
            Serial.println("off");
        }

        //保存这次的状态
        lastButtonState = buttonState;
    }

    //没四次按键按下就把led电平翻转
    if (buttonPushCounter % 4 == 0) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }
}
