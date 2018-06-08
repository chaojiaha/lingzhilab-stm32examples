/*
连接led到一个可以输出PWM的引脚上，实现呼吸灯的效果
*/

int ledPin = LED_BUILTIN;
void setup() {
    pinMode(ledPin, PWM);  // 设置引脚为输出pwm模式
}

void loop()  {
    // 以每次增加1280点，从最小到最大的占空比输出pwm
    for (int fadeValue = 0; fadeValue <= 65535; fadeValue += 1280) {

        pwmWrite(ledPin, fadeValue);
        // 延时30ms
        delay(30);
    }

    // 从最大到最小的占空比输出pwm，每次减少1280
    for (int fadeValue = 65535 ; fadeValue >= 0; fadeValue -= 1280) {
        pwmWrite(ledPin, fadeValue);
        //延时30ms
        delay(30);
    }
}
