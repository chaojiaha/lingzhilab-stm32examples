/*
使用for()循环来控制多个led灯
*/

int delayTime = 100;           //延时时间

void setup() {
    // 使用循环来设置2到7脚的模式
    for (int thisPin = 2; thisPin <= 7; thisPin++) {
        pinMode(thisPin, OUTPUT);
    }
}

void loop() {
    // 从引脚2-7
    for (int thisPin = 2; thisPin <= 7; thisPin++) {
      
        digitalWrite(thisPin, HIGH);
        delay(delayTime);
       
        digitalWrite(thisPin, LOW);
    }

    // 从引脚7-2
    for (int thisPin = 7; thisPin >= 2; thisPin--) {
        
        digitalWrite(thisPin, HIGH);
        delay(delayTime);
       
        digitalWrite(thisPin, LOW);
    }
}
