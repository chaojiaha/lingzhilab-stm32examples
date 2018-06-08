/*
  8x8的led矩阵横向和竖向扫描示例。
*/


// 横向的led引脚号
const int row[8] = {
    2, 7, 19, 5, 13, 18, 12, 16 };

// 竖向led引脚号
const int col[8] = {
    6, 11, 10, 3, 17, 4, 8, 9 };

// 模拟输入引脚
const int analogPin1 = 0;
const int analogPin2 = 1;

// 像素值
int pixels[8][8];

// 光标的位置
int x = 5;
int y = 5;

void setup() {
    // 设置为模拟输入
    pinMode(analogPin1, INPUT_ANALOG);
    pinMode(analogPin2, INPUT_ANALOG);

    //初始化led连接的引脚
    for (int thisPin = 0; thisPin < 8; thisPin++) {
        pinMode(col[thisPin], OUTPUT);
        pinMode(row[thisPin], OUTPUT);
        // 初始状态时，在垂直方向上led连接的引脚输出高电平
        digitalWrite(col[thisPin], HIGH);
    }

    // 初始化像素矩阵
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            pixels[x][y] = HIGH;
        }
    }
}

void loop() {
    //读取输入
    readSensors();

    //通过led矩阵输出
    refreshScreen();
}

void readSensors() {
    // 最后一个位置关闭
    pixels[x][y] = HIGH;
    // 把读取的值映射为x，y坐标
    x = 7 - map(analogRead(analogPin1), 0, 4095, 0, 7);
    y = map(analogRead(analogPin2), 0, 4095, 0, 7);
    // 设置新的坐标位置的led状态
    pixels[x][y] = LOW;
}

void refreshScreen() {
    for (int thisRow = 0; thisRow < 8; thisRow++) {
        // 设置横向当前位置的led状态
        digitalWrite(row[thisRow], HIGH);

        for (int thisCol = 0; thisCol < 8; thisCol++) {
            //获取当前像素的状态
            int thisPixel = pixels[thisRow][thisCol];

            digitalWrite(col[thisCol], thisPixel);

            if (thisPixel == LOW) {
                digitalWrite(col[thisCol], HIGH);
            }
        }
        //所有横向上的led状态设置为low
        digitalWrite(row[thisRow], LOW);
    }
}
