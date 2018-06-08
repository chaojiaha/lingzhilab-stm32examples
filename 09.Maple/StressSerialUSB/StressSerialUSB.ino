/*
串口测试程序
 
 */

#define LED_PIN 13
#define BUTTON_PIN 38

uint32 state = 0;
#define QUICKPRINT  0
#define BIGSTUFF    1
#define NUMBERS     2
#define SIMPLE      3
#define ONOFF       4

void setup()
{
	Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);

    //初始化按键
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // 设置另一个通道
    Serial2.begin(9600);
    Serial2.println("Hello world! 这是测试通道");
}

int toggle = 0;

void loop() {
    toggle ^= 1;
    digitalWrite(LED_PIN, toggle);
    delay(300);

    //如果有按键按下
    if(digitalRead(BUT_PIN)) {
        while(digitalRead(BUT_PIN)) {};
        state++;
    }
    
    switch(state) {

        case QUICKPRINT:
            for(int i = 0; i<40; i++) {
                Serial.print('.');
                Serial.print('|');
            }
            Serial2.println(Serial.pending(),DEC);
            Serial.println();
            break;

        // 发送大量的数据
        case BIGSTUFF:
            Serial.println("01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
            Serial.println((uint32)123456789,DEC);
            Serial.println(3.1415926535);
            Serial2.println(Serial.pending(),DEC);
            break;

        // 测试不同的了类型
        case NUMBERS:
            Serial.println("Numbers! -----------------------------");
            Serial2.println("Numbers! -----------------------------");
            Serial.println('1');
            Serial2.println('1');
            Serial.println(1,DEC);
            Serial2.println(1,DEC);
            Serial.println(-1,DEC);
            Serial2.println(-1,DEC);
            Serial.println(3.14159265);
            Serial2.println(3.14159265);
            Serial.println(3.14159265,9);
            Serial2.println(3.14159265,9);
            Serial.println(123456789,DEC);
            Serial2.println(123456789,DEC);
            Serial.println(-123456789,DEC);
            Serial2.println(-123456789,DEC);
            Serial.println(65535,HEX);
            Serial2.println(65535,HEX);
            Serial.println(65535,OCT);
            Serial2.println(65535,OCT);
            Serial.println(65535,BIN);
            Serial2.println(65535,BIN);
            break;

        // 基础的串口打印显示
        case SIMPLE:
            Serial2.println("Trying write('a')");
            Serial.write('a');
            Serial2.println("Trying write(\"b\")");
            Serial.write("b");
            Serial2.println("Trying print('c')");
            Serial.print('c');
            Serial2.println("Trying print(\"d\")");
            Serial.print("d");
            Serial2.println("Trying print(\"efg\")");
            Serial.print("efg");
            Serial2.println("Trying println(\"hij\\n\\r\")");
            Serial.print("hij\n\r");
            Serial.write(' ');
            Serial.println();
            Serial2.println("Trying println(123456789,DEC)");
            Serial.println(123456789,DEC);
            Serial2.println("Trying println(3.141592)");
            Serial.println(3.141592);
            Serial2.println("Trying println(\"DONE\")");
            Serial.println("DONE");
            break;

        case ONOFF:
            Serial2.println("Shutting down...");
            Serial.println("Shutting down...");
            Serial.end();
            Serial2.println("Waiting 4seconds...");
            delay(4000);
            Serial2.println("Starting up...");
            Serial.begin();
            Serial.println("Hello World!");
            Serial2.println("Waiting 4seconds...");
            delay(4000);
            state++;
            break;
        default:
            state = 0;
    }
} 

