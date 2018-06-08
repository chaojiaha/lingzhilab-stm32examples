
/*
  串口读取数据示例
*/

#define BAUD 9600

char serialdata[80] = "TEST\r\n";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(BAUD);  
}

void loop() {
  
  int lf = 10;
 
  Serial.readBytesUntil(lf, serialdata, 80);

  Serial.println(serialdata);

}


