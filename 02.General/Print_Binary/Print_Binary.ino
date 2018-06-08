/* 
串口打印输出一个数的二进制形式
*/

#define BAUD 9600

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(BAUD); 
}

void loop()
{
  while(1)
  {
      print_binary(1024+256+63, 12);
      Serial.println();
      delay(1000);

  }
}

void print_binary(int v, int num_places)
{
    int mask=0, n;

    for (n=1; n<=num_places; n++)
    {
        mask = (mask << 1) | 0x0001;
    }
    v = v & mask;  // 按照数据位置对v进行截断

    while(num_places)
    {

        if (v & (0x0001 << num_places-1))
        {
             Serial.print("1");
        }
        else
        {
             Serial.print("0");
        }

        --num_places;
        if(((num_places%4) == 0) && (num_places != 0))
        {
            Serial.print("_");
        }
    }
}

