/*
*	测试rtc时钟
*/

#include <RTClock.h>

RTClock rt (RTCSEL_LSE); //初始化
uint32 tt; 

#define LED_PIN LED_BUILTIN

void blink () 
{
 digitalWrite(LED_PIN,!digitalRead(LED_PIN));
}

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  
  rt.attachSecondsInterrupt(blink);// Call blink
}



void loop() 
{
  
  if (rt.getTime()!=tt)
  {
    tt = rt.getTime();
    
    Serial.print("time is: ");
    Serial.println(tt);
  }
}