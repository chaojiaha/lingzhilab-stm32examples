/*
 进制转换
*/

//对符号 "<<" 进行重载，使串口输出更方便
template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

  char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
  char * pEnd;
  long int li1, li2, li3, li4;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  delay(5000);

  li1 = strtol (szNumbers,&pEnd,10);  // 十进制
  li2 = strtol (pEnd,&pEnd,16);       // 十六进制
  li3 = strtol (pEnd,&pEnd,2);        // 二进制
  li4 = strtol (pEnd,NULL,0);         // 带有十进制或十六进制格式前缀的整数
  //下面两句是等价的，
  // Serial.print ("相应十进制数值: %ld, %ld, %ld and %ld.\n", li1, li2, li3, li4);
  Serial << "相应的十进制数: " << li1 << " " << li2 << " " << li3 << " " << li4 << "\r\n\r\n";
}



void loop() {
  // put your main code here, to run repeatedly: 
  
}
