/*
  使led灯按照1s的频率进行闪烁，并对循环的次数进行串口打印显示
 */
int n = 0;


void setup() {
  // 设置led引脚为输出
  pinMode(LED_BUILTIN, OUTPUT);
  // 设置串口波特率为 9600
  Serial.begin(9600);  
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // 设置led引脚为高电平
  delay(500);              //等待500ms
  digitalWrite(LED_BUILTIN, LOW);    //设置led引脚低电平
  Serial.print("循环次数: ");       //串口打印显示循环的次数
  n++;
  Serial.println(n);

  delay(500);              // 再次等待500ms
}
