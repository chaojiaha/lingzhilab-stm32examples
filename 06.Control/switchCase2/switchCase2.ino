/*
switch选择结构的使用示例，这个示例中当串口接受到不同的值时，led将会有不同的变化
*/

void setup() {
	Serial.begin(9600); 
    // 初始化连接led的2-6脚为输出模式
    for (int thisPin = 2; thisPin <= 6; thisPin++) {
        pinMode(thisPin, OUTPUT);
    }
}

void loop() {
    //获取串口数据
    if (Serial.available() > 0) {
        int inByte = Serial.read();
        //根据从串口获取的不同字符，对不同的led引脚输出高电平
        switch (inByte) {
        case 'a':
            digitalWrite(2, HIGH);
            break;
        case 'b':
            digitalWrite(3, HIGH);
            break;
        case 'c':
            digitalWrite(4, HIGH);
            break;
        case 'd':
            digitalWrite(5, HIGH);
            break;
        case 'e':
            digitalWrite(6, HIGH);
            break;
        default:
            // 除了上面的字符外，其他字符的情况下把所有的led引脚拉低
            for (int thisPin = 2; thisPin < 7; thisPin++) {
                digitalWrite(thisPin, LOW);
            }
        }
    }
}
