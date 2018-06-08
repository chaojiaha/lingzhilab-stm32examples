/*
  ASCII码输出显示
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); 

  delay(5000);
  Serial.println("输入一个字符，开始打印：");
}

// 第一个可见的ASCII码字符: '!' ，相应的十进制为 33:
int thisByte = 33; //这里也可以直接使用 int thisByte = '!';
int junk     =  0;
bool Virgin  = true;

void loop() {

  Restart:
    // 等待用户输入一个字符
    if (!Virgin) 
      goto NextPhase;
    while (!Serial.available())
        continue;

    while (Serial.available()) {
        junk = Serial.read();
    }

    NextPhase:
    Virgin = false ;
    //串口直接输出对应的ASCII码
    Serial.write(thisByte);

    Serial.print(", dec: ");

    // 十进制形式, 是print的默认形式
    Serial.print(thisByte);

    Serial.print(", hex: ");
    //十六进制
    Serial.print(thisByte, HEX);

    Serial.print(", oct: ");
    // 八进制
    Serial.print(thisByte, OCT);

    Serial.print(", bin: ");
    // 二进制
    Serial.println(thisByte, BIN);
    Serial.print("\r\n\r\n");
    delay(100);

    // 最后一个可见字符： '~' 十进制为 126，结束打印
    if (thisByte == 126) {     // 可以直接写成这样： if (thisByte == '~') {
        thisByte = 33;
        Virgin = true;
        Serial.println("==============================");
        Serial.println("输入字符重新开始打印");
        goto Restart ;
    }
    //下一个字符
    thisByte++;
}
