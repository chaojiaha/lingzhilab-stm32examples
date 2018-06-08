/*
从串口输入整数测试
*/

#define BAUD 9600
#define timeoutPeriod 3000 

int a;
int b;

void setup()
{
  // 初始化引脚为输出模式
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(BAUD);  //设置串口波特率
  Serial.setTimeout(timeoutPeriod); // 设置串口超时时间
}

void loop()
{
    Serial.println("输入第一个整数: ");
    a = Serial.parseInt();
    Serial.print("a = ");
    Serial.println(a);


    Serial.println("输入第二个整数: ");
    b = Serial.parseInt();
    Serial.print("b = ");
    Serial.println(b);

    Serial.print("两数相加后结果： a + b =");
    Serial.println( a + b);
    Serial.print("两数相加后结果： a - b =");
    Serial.println(a - b);
}

