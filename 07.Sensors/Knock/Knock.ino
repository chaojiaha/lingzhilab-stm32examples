/*
 通过压电模块检测敲击的声音，如果在模拟输入脚读到了一个超过某个设定阈值的信号，就在串口打印“敲击”信息，并反转led

  电路连接
  * + piezo引脚连接到模拟引脚0
  * - piezo引脚连接到地
  * 在模拟引脚0和地之间连接一个1兆的电阻
*/

const int knockSensor = 0;  // 连接piezo
const int threshold = 100;  //检测是否是敲击的声音的一个临界值

int sensorReading = 0;     

void setup() {
	Serial.begin(9600);
    pinMode(knockSensor, INPUT_ANALOG);
   
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    // 获取模拟输入数据
    sensorReading = analogRead(knockSensor);

    // 如果获取的数值比设定的阈值大，说明有敲击发生
    if (sensorReading >= threshold) {
        // 反转led
        digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
        // 打印显示“敲击”信息
        Serial.println("敲击!");
    }
    delay(100); 
}
