/*
数组的使用，这里把led的脚存放到数组中，从而可以同时控制多个led，并且不同于循环，这里存放到数组中的led引脚是随机的，
因此控制的led引脚号不需要按一定的顺序
*/

int delayTime = 100;      // 延时的时间
int ledPins[] = { 2, 7, 4, 6, 5, 3 };     // 与led连接的引脚号
int pinCount = 6;         //引脚的数量，即数组的大小

void setup() {
    int thisPin;
    // 设置所有在数组中的引脚的模式为输出
    for (int thisPin = 0; thisPin < pinCount; thisPin++)  {
        pinMode(ledPins[thisPin], OUTPUT);
    }
}

void loop() {
  //从数组中的第一个到最后一个
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {

    digitalWrite(ledPins[thisPin], HIGH);
    delay(delayTime);

    digitalWrite(ledPins[thisPin], LOW);
  }

  // 从数组中的最后一个到第一个
  for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) {
    
    digitalWrite(ledPins[thisPin], HIGH);
    delay(delayTime);

    digitalWrite(ledPins[thisPin], LOW);
  }
}
