/*
使用流的方式进行字符串操作，以及串口输出流操作
*/

#include "Streaming.h"  //使用这个库后使得串口操作更加方便

char sInput[] = {"ZD2b102c080c090e05ba0549\0"} ;  // 来自串口输入
String sMM ;          // 0xHH\0  5 个字符

void setup(void)
{
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  delay(5000);


  Serial << "示例程序开始运行...\r\n" ;
  Serial << "原始的字符串： " << sInput << "\r\n\r\n" ;

  //使用流的方式进行字符串的操作，这里的 "+" 进行了重载
  sMM += "0x" ; sMM += sInput[6]; sMM += sInput[7]; sMM += '\0' ;  

  Serial << "Substrings: " << sMM << "\r\n\r\n" ;  //使用流的方式进行串口输出显示  

  Serial.end();
}

void loop( void ) {}

