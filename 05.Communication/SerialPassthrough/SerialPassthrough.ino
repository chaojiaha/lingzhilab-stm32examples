/*
多个串口之间交互
*/

int inByte;                     //从串口1获取的数据

void setup() {
    //初始化串口
	   Serial.begin(9600); 
     Serial1.begin(9600);
}

void loop() {
    // 获取串口Serial1的数据，然后发送到串口Serial
    if (Serial1.available()) {
        inByte = Serial1.read();
        Serial.write(inByte);
    }
}
