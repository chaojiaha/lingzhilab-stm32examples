/* 
伺服控制 sweep 示例程序
*/

#include <Servo.h>

Servo myservo;  // 创建伺服模块的实例

int pos = 0;    // 存放伺服位置的变量

void setup() {
  myservo.attach(9);  // 伺服模块连接到9号脚
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { //从0到180度
    // in steps of 1 degree
    myservo.write(pos);              //pos设置到伺服模块
    delay(15);                       //等待完成
  }
  for (pos = 180; pos >= 0; pos -= 1) { //从180到0度
    myservo.write(pos);              
    delay(15);                       
  }
}

