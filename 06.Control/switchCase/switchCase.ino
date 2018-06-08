/*
switch结构的使用，它的功能相当于具有多个分支的if结构
*/

// 常量
const int sensorMin = 0;      //最小值
const int sensorMax = 600;    // 最大值

void setup() {
	Serial.begin(9600); 
    pinMode(0, INPUT_ANALOG);
}

void loop() {
    // 读取模拟输入
    int sensorReading = analogRead(0);
    //数值范围进行映射
    int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

    //根据不同的range，执行不同的语句
    switch (range) {
    case 0:  
        Serial.println("dark");
        break;
    case 1:    
        Serial.println("dim");
        break;
    case 2:   
        Serial.println("medium");
        break;
    case 3:   
        Serial.println("bright");
        break;
    }
}
