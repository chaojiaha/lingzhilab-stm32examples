/*
使用平均值法对读取的数值进行滤波处理
*/

const int numReadings = 10;

int readings[numReadings];      // 从模拟引脚读取的数值存放到这个数组中
int index1 = 0;                  // 当前读取时候的下标
int total = 0;                  // 总的数值
int average = 0;                // 平均值

int inputPin = 15;              // 模拟输入的引脚

void setup() {

    pinMode(inputPin, INPUT_ANALOG);
	  Serial.begin(9600); 
	
    // 清空数组，初始化为0
    for (int thisReading = 0; thisReading < numReadings; thisReading++) {
        readings[thisReading] = 0;
    }
}

void loop() {
    // 减去最后一次读取的值
    total = total - readings[index1];
    //模拟读入
    readings[index1] = analogRead(inputPin);
    //把读取的数值相加
    total = total + readings[index1];
    // 数组的下标在读取一次后增加1
    index1 = index1 + 1;

    //如果是数组的最后一个元素
    if (index1 >= numReadings) {
        // 准备下一轮的读取，数组下标置0
        index1 = 0;
    }

    // 计算平均值
    average = total / numReadings;
    //串口打印显示该数值
    Serial.println(average, DEC);
}
