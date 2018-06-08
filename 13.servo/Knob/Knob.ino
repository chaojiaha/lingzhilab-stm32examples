/*
电位器控制伺服模块
*/

#include <Servo.h>

Servo myservo;  // 建立servo模块的实例

int potpin = 0;  // 连接电位器的脚
int val;    

void setup() {
  myservo.attach(9);  //伺服模块连接到9号脚
}

void loop() {
  val = analogRead(potpin);            // 读取模拟输入
  val = map(val, 0, 1023, 0, 180);     // 范围映射
  myservo.write(val);                  // 把调整后的值设置到伺服模块
  delay(15);                           //等待伺服模块运行到指定的位置
}

