/*
模拟输入、输出以及串口输出
*/

const int analogInPin = 15; // 模拟输入引脚

const int pwmOutPin = LED_BUILTIN;    //led连接到pwm输出引脚

int sensorValue = 0;        // 从引脚读到的值
int outputValue = 0;        //输出到pwm脚的值

void setup() {
    // 设置引脚为模拟输入模式
    pinMode(analogInPin, INPUT_ANALOG);
    // 设置led脚输出pwm模式
    pinMode(pwmOutPin, PWM);
	  Serial.begin(9600); 
}

void loop() {
    //读取模拟输入数值
    sensorValue = analogRead(analogInPin);
    // 使用map函数把输入的数值进行范围上扩大
    outputValue = map(sensorValue, 0, 1023, 0, 65535);
    // 改变模拟输出数值
    pwmWrite(pwmOutPin, outputValue);

    // 在串口打印显示输入输出的数值
    Serial.print("sensor = " );
    Serial.print(sensorValue);
    Serial.print("\t output = ");
    Serial.println(outputValue);
    delay(200);
}
