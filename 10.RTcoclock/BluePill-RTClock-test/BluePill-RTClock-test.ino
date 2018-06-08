/*  
*      这是一个STM32F10x系列的RTC应用的例子，希望对你的编码有所帮助
*  这个程序基于https://github.com/rogerclarkmelbourne/Arduino_STM32 ， 感谢所有贡献者的付出。
*  程序测试了 F10x系列RTC 的 几种中断， 并通过LED和串口进行表达。
*  RTClock 使用 UTC 作为时间标准， 你可以从https://www.epochconverter.com/ 获得 Unix epoch time数值
*  并通过串口进行设置， 当然你也可以略微修改一下串口接收处理方法，直接从串口接收日期形式。如 2017-9-13-10:30:00, 
*  另外一个方法是通过ESP8266获取NTP网络时间，并定期发送给F10x进行更新。
*/


#include <RTClock.h>

RTClock rtclock (RTCSEL_LSE); // initialise
int timezone = 8;      // change to your timezone
time_t tt;
time_t tt1;
tm_t mtt = { 47, 9, 13, 3, 11, 22, 30, 30 };    // init time 47+1970 = 2017  Unix epoch Time counted from 00:00:00 1 Jan 1970  
char weekday1[][7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};  // 0,1,2,3,4,5,6
uint8_t dateread[11];
int globAlmCount = 0;
int lastGlobAlmCount;
int SPECAlmCount = 0;
int lastSPECAlmCount;
int i = 0;
int alarmcount = 3;
uint8_t AlarmExchange = 0;
bool dispflag = true;

#define LED_PIN LED_BUILTIN

// This function is called in the attachSecondsInterrpt
void SecondCount ()
{
  tt++;
}
// This function is called in the attachAlarmInterrpt
void blink ()
{
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  globAlmCount++;
  //tt++;
}

void OnOffSerial ()
{
  dispflag = !dispflag;
  SPECAlmCount++;
}

void setup()
{
  lastGlobAlmCount = ~globAlmCount;
  lastSPECAlmCount = ~SPECAlmCount;
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  tt = rtclock.makeTime(mtt); 
  rtclock.setTime(tt);  
  tt1 = tt;
  rtclock.attachAlarmInterrupt(blink);// Call blink
  rtclock.attachSecondsInterrupt(SecondCount);// Call SecondCount
}

void loop()
{
  while (Serial.available())
  { 
    dateread[i] = Serial.read();
    if (i < 11) {
      i++;
    }
    else {
      i = 0;
      tt = (dateread[0] - '0') * 1000000000 + (dateread[1] - '0') * 100000000 + (dateread[2] - '0') * 10000000 + (dateread[3] - '0') * 1000000 + (dateread[4] - '0') * 100000;
      tt += (dateread[5] - '0') * 10000 + (dateread[6] - '0') * 1000 + (dateread[7] - '0') * 100 + (dateread[8] - '0') * 10 + (dateread[9] - '0');
      rtclock.TimeZone(tt, timezone);    //adjust to your local date
      rtclock.setTime(rtclock.TimeZone(tt, timezone));
    }
  }
  if (lastGlobAlmCount != globAlmCount | lastSPECAlmCount != SPECAlmCount ) {
    if (globAlmCount == 10) {        // to detachAlarmInterrupt and start creatAlarm after 10 times about 110s
      rtclock.detachAlarmInterrupt();
      globAlmCount = 0;
      rtclock.createAlarm(OnOffSerial, (rtclock.getTime() + 20));   // call OnOffSerial stop output date from Serial after 2 mins
      alarmcount = 20;   //change to creatAlarm  21S close Serial output and 41s open Serial output.
    }
    else {
      lastGlobAlmCount = globAlmCount;
      lastSPECAlmCount = SPECAlmCount;
      Serial.println(" Say hello to every guys ");
      if(dispflag == false)
      Serial.println(" SPECAlarm turn Display Off ");
      switch (AlarmExchange)  {
        case 0:
          rtclock.setAlarmTime(rtclock.getTime() + alarmcount);  // reset alarm = current time + 4s for attachAlarmInterrupt,  21s for creatAlarm
          AlarmExchange = 1;
          break;
        case 1:
          rtclock.breakTime(rtclock.getTime() + alarmcount * 2, mtt); //// reset alarm = current time + 7s for attachAlarmInterrupt,  41s for creatAlarm
          rtclock.setAlarmTime(mtt);
          AlarmExchange = 0;
          break;
      }
    }
  }
  if (tt1 != tt & dispflag == true )
  {
    tt1 = tt;
    //rtclock.breakTime(tt, mtt);
    Serial.print("Date:  ");
    Serial.print(rtclock.day());
    Serial.print("- ");
    Serial.print(rtclock.month());
    Serial.print("  ");
    Serial.print(rtclock.year() + 1970);
    Serial.print("  ");
    Serial.print(weekday1[rtclock.weekday()]);
    Serial.print("  Time: ");
    Serial.print(rtclock.hour());
    Serial.print(" : ");
    Serial.print(rtclock.minute());
    Serial.print(" : ");
    Serial.println(rtclock.second());
  }
}
