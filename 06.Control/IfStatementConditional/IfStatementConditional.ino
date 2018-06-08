/*
if()结构的使用
*/

// These constants won't change:

const int analogPin = 15;     // 传感器连接的引脚号

const int threshold = 400;    //一个随机的模拟输入范围的临界值

void setup() {
	Serial.begin(9600); 
    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(analogPin, INPUT_ANALOG);
}

void loop() {
    //读取模拟输入的值
    int analogValue = analogRead(analogPin);

    //如果值达到临界值，就给led脚输出高电平
    if (analogValue > threshold) {
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else {
        digitalWrite(LED_BUILTIN, LOW);
    }

    // 串口显示模拟输入获取的数值
    Serial.println(analogValue, DEC);
}
