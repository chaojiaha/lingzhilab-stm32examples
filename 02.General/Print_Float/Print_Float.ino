/*
 打印输出浮点数
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
      //正数的情形
      print_float(0.6, 2);  
      Serial.println();
      print_float(1.2, 1);
      Serial.println();
      print_float(10.27, 2);
      Serial.println();
      print_float(10.345, 3);
      Serial.println();
      print_float(107.345, 3);
      Serial.println();
      delay(1000);

      //负数的情形
      print_float(-0.6, 2);
      Serial.println();
      print_float(-1.2, 1);
      Serial.println();
      print_float(-10.27, 2);
      Serial.println();
      print_float(-10.345, 3);
      Serial.println();
      print_float(-107.345, 3);
      Serial.println();
      delay(1000);
  }
}

void print_float(float f, int num_digits)
{
    int f_int;
    int pows_of_ten[4] = {1, 10, 100, 1000};
    int multiplier, whole, fract, d, n;

    multiplier = pows_of_ten[num_digits];
    if (f < 0.0)
    {
        f = -f;
        Serial.print("-");
    }
    whole = (int) f;
    fract = (int) (multiplier * (f - (float)whole));

    Serial.print(whole);
    Serial.print(".");

    for (n=num_digits-1; n>=0; n--) 
    {
         d = fract / pows_of_ten[n];
         Serial.print(d);
         fract = fract % pows_of_ten[n];
    }
}


