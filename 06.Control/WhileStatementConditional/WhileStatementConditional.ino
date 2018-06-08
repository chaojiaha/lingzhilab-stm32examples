/*
while循环的使用
*/

const int sensorPin = 2;     // 传感器连接的引脚
const int ledPin = 9;        // led连接的引脚

int sensorMin = 4095;  //最小值
int sensorMax = 0;     // 最大值
int sensorValue = 0;   // 保存当前获取的数值

void setup() {
    pinMode(ledPin, OUTPUT);          // 连接9引脚的led
    pinMode(LED_BUILTIN, OUTPUT);   // 板载led
    pinMode(BOARD_BUTTON_PIN, INPUT); // 板载按键
}

void loop() {
    //循环中检测按键状态，如果高执行校准
    while (digitalRead(BOARD_BUTTON_PIN) == HIGH) {
        calibrate();
    }
    //校准阶段结束
    digitalWrite(LED_BUILTIN, LOW);

    //获取模拟输入的数值
    sensorValue = analogRead(sensorPin);

    //映射最大到最小值得范围
    sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 65535);

    // 在校准过程中如果超出范围了
    sensorValue = constrain(sensorValue, 0, 65535);

    // 通过获取的数值设置为led引脚的输出值
    pwmWrite(ledPin, sensorValue);
}

void calibrate() {
    // 标识校准发生
    digitalWrite(LED_BUILTIN, HIGH);
    // 获取模拟输入值
    sensorValue = analogRead(sensorPin);

    // 记录最大值
    if (sensorValue > sensorMax) {
        sensorMax = sensorValue;
    }

    //记录最小值
    if (sensorValue < sensorMin) {
        sensorMin = sensorValue;
    }
}
