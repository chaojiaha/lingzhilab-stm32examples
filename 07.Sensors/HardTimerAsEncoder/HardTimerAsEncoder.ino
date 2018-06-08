/*
 * 把的硬件定制器作为编码器接口，stm32的硬件定时器完全可以作为一种编码器的接口，可以是正交编码或者脉冲编码
 *
 * 
*/

#include "HardwareTimer.h"

unsigned char mode = 0; 
unsigned char dir = 'F'; //编码移动方向

unsigned int freq = 100; //更新的频率
unsigned long time = 0;   
unsigned char states[4];      

//编码器每一圈的脉冲数量，即编码的分辨率
#define PPR   1024

HardwareTimer timer(2);

unsigned long ints = 0;

void func(){
if (timer.getDirection()){
  ints--;
} else{
  ints++;
}
}


void setup() {
  //定义timer的通道为输入模式
  pinMode(D2, INPUT_PULLUP);  //channel A
  pinMode(D3, INPUT_PULLUP);  //channel B

//配置timer
  timer.setMode(0, TIMER_ENCODER); 
  timer.pause();// 停止
  timer.setPrescaleFactor(1); //为了使编码器有最小的预分频或没有
  timer.setOverflow(PPR);    //分辨率
  timer.setCount(0);          //重设计数器
  timer.setEdgeCounting(TIMER_SMCR_SMS_ENCODER3); //可选：TIMER_SMCR_SMS_ENCODER1、TIMER_SMCR_SMS_ENCODER2等编码的模式
  timer.attachInterrupt(0, func); 
  timer.resume();                 //开始
  
//设置编码器模拟
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

  digitalWrite(5, HIGH); 
  digitalWrite(4, LOW);
  states[0] = 0; //00
  states[1] = 1; //01
  states[2] = 3; //11
  states[3] = 2; //10


}

unsigned long interval=0; 
char received = 0;

void loop() {
  //编码
  if (millis() - interval >= 1000) { 
     Serial.print(timer.getCount()); 
     Serial.println(" counts");
     Serial.print("direction ");
     Serial.println(timer.getDirection());
     Serial.print("Full Revs: ");
     Serial.println(ints);
     interval = millis(); 
  }
  
  
  
/*
EENCODER SIMULATION PART. 
*/  
/*
 * 
 * Protocol... 
 * 
 * if received F - Move forward. 
 * if received B - Move BackWard
 * if received 1 - Mode 1 (Channel B counts)
 * if received 2 - Mode 2 (Channel A counts)
 * if received 3 - Mode 3 (Counts on both channels)
 * if received 4 - Change prescaler to 4
 * if received 0 - change prescaler to 1
 * if received - - Increase Speed
 * if received + - Decrease Speed
*/

//注意串口获取的值
  if (Serial.available() > 0) {
    received = Serial.read();
    if (received == 'F' || received == 'R') dir = received; //前进或反转
    if (received == '1') timer.setEdgeCounting(TIMER_SMCR_SMS_ENCODER1); //仅计算1的输入脉冲
    if (received == '2') timer.setEdgeCounting(TIMER_SMCR_SMS_ENCODER2); //仅计算2的脉冲输入
    if (received == '3') timer.setEdgeCounting(TIMER_SMCR_SMS_ENCODER3); //两个都进行计算（默认）
    if (received == '4') timer.setPrescaleFactor(4); //仅在溢出时候更新
    if (received == '0') timer.setPrescaleFactor(1); //仅在溢出时候更新
    if (received == '-') freq+=50; //加速
    if (received == '+') {
      freq-=50;
      if (freq <= 0) freq = 100; //最小为 10 ms
    }
  }
  
//模拟脉冲 
  if ( millis() - time >= freq) { 
    time = millis(); 
    
    if (dir == 'F')  mode++;
    if (dir == 'R')  mode --;
    
    digitalWrite(4, (states[mode%4] & 0x01));
    digitalWrite(5, (states[mode%4] >> 1));
  }

}
