/*
	查找质数示例2
*/

#define BAUD 9600
const int SHOW_EVERY = 500;  // 串口打印显示频率
int candidate;
int found = 5; // 找到的个数
int count = found - 1;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(BAUD); 
  
  delay(5000);
}

void loop() {
    Serial.println("从 1 到 99999999 之间的质数:");
    Serial.println("2 \t");
    for (int i=3; i<99999999;i+=2) {
        // 当前循环停止的条件为：1、当 j*j>i； 2、i能被 j 整除.
        // 第一个条件说明是质数，第二个条件说明不是质数
        int j=3;
        for(;j*j<=i && i%j!=0; j+=2); //循环体为空语句

        if (j*j>i) 
          Serial.print(i);
          
        Serial.print( "\r\n");

    delay(50);
    }
    Serial.println("\r\n");
}
