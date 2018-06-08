/*
模拟输入读取校准操作
*/

const int sensorPin = 15;    //连接传感器的引脚

// 定义相关的变量
int sensorMin = 1023;   
int sensorMax = 0;      
int sensorValue = 0;    

void setup() {
    pinMode(sensorPin, INPUT_ANALOG);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    //在第一个5s内，进行校准操作
    while (millis() < 5000) {
        sensorValue = analogRead(sensorPin);

        // 记录最大值
        if (sensorValue > sensorMax) {
            sensorMax = sensorValue;
        }

        // 记录最小值
        if (sensorValue < sensorMin) {
            sensorMin = sensorValue;
        }
    }

    // 表示校准阶段结束
    digitalWrite(LED_BUILTIN, LOW);
}

void loop() {

    sensorValue = analogRead(sensorPin);

    //扩大范围
    sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 65535);

    //如果超出了范围
    sensorValue = constrain(sensorValue, 0, 65535);

    // 通过led亮度可以指示数值的大小
    pwmWrite(LED_BUILTIN, sensorValue);
}
