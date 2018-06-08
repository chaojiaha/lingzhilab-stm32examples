/*
打印输出十六进制形式
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
      print_hex(1024+256+63, 13);
      Serial.println();
      delay(1000);

  }
}

void print_hex(int v, int num_places)
{
    int mask=0, n, num_nibbles, digit;

    for (n=1; n<=num_places; n++)
    {
        mask = (mask << 1) | 0x0001;
    }
    v = v & mask; //按位数截断

    num_nibbles = num_places / 4;
    if ((num_places % 4) != 0)
    {
        ++num_nibbles;
    }

    do
    {
        digit = ((v >> (num_nibbles-1) * 4)) & 0x0f;
        Serial.print(digit, HEX);
    } while(--num_nibbles);

}

