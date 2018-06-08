/*
使用vga接口进行显示一个图片。

接口的连线：
    D5 通过 200欧姆 连接 VGA Red     (1)
    D6 通过 200欧姆 连接 VGA Green   (2)
    D7 通过 200欧姆 连接 VGA Blue    (3)
    D11 连接 VGA VSync               (14)  
    D12 连接 VGA HSync               (13)  
    GND 连接 VGA Ground              (5)
    GND 连接 VGA Sync Ground         (10)
 
 */

#define LED_PIN 13

// Pinouts
#define VGA_R 5     // STM32: B6
#define VGA_G 6     // STM32: A8
#define VGA_B 7     // STM32: A9
#define VGA_V 11    // STM32: A6
#define VGA_H 12    // STM32: A7

// 使用底层寄存器来加速写操作
#define VGA_R_HIGH (GPIOB_BASE)->BSRR = BIT(6)
#define VGA_R_LOW  (GPIOB_BASE)->BRR  = BIT(6)
#define VGA_G_HIGH (GPIOA_BASE)->BSRR = BIT(8)
#define VGA_G_LOW  (GPIOA_BASE)->BRR  = BIT(8)
#define VGA_B_HIGH (GPIOA_BASE)->BSRR = BIT(9)
#define VGA_B_LOW  (GPIOA_BASE)->BRR  = BIT(9)
#define VGA_V_HIGH (GPIOA_BASE)->BSRR = BIT(6)
#define VGA_V_LOW  (GPIOA_BASE)->BRR  = BIT(6)
#define VGA_H_HIGH (GPIOA_BASE)->BSRR = BIT(7)
#define VGA_H_LOW  (GPIOA_BASE)->BRR  = BIT(7)

void isr_porch(void);
void isr_start(void);
void isr_stop(void);
void isr_update(void);

uint8 toggle;
uint16 x = 0;       // X 轴
uint16 y = 0;       // Y 轴
uint8 v_active = 1; 

// 1-bit!
uint8 logo[18][16] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,},
    {0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,},
    {0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,},
    {0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,},
    {0,0,1,0,0,1,0,1,0,1,0,0,1,0,0,0,},
    {0,1,0,0,0,0,1,1,1,0,0,0,0,1,0,0,},
    {0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,},
    {1,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,},
    {1,0,0,0,0,1,0,1,0,1,0,0,0,0,1,0,},
    {1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,},
    {0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,},
    {0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,},
    {0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,},
    {0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, };

void setup() {
	Serial.begin(9600); 
 
    pinMode(LED_PIN, OUTPUT);
    pinMode(VGA_R, OUTPUT);
    pinMode(VGA_G, OUTPUT);
    pinMode(VGA_B, OUTPUT);
    pinMode(VGA_V, OUTPUT);
    pinMode(VGA_H, OUTPUT);
    digitalWrite(VGA_R, LOW);
    digitalWrite(VGA_G, LOW);
    digitalWrite(VGA_B, LOW);
    digitalWrite(VGA_H, HIGH);
    digitalWrite(VGA_V, HIGH);

    Serial.end();
    

    // 定时器配置
    Timer4.pause();
    Timer4.setPrescaleFactor(1);  
    Timer4.setChannel1Mode(TIMER_OUTPUTCOMPARE);
    Timer4.setChannel2Mode(TIMER_OUTPUTCOMPARE);
    Timer4.setChannel3Mode(TIMER_OUTPUTCOMPARE);
    Timer4.setChannel4Mode(TIMER_OUTPUTCOMPARE);
    Timer4.setOverflow(2287);  

    Timer4.setCompare1(200);
    Timer4.attachCompare1Interrupt(isr_porch);
    Timer4.setCompare2(300);
    Timer4.attachCompare2Interrupt(isr_start);
    Timer4.setCompare3(2170);
    Timer4.attachCompare3Interrupt(isr_stop);
    Timer4.setCompare4(1);  
    Timer4.attachCompare4Interrupt(isr_update);
    
    Timer4.setCount(0);         
    Timer4.resume();          
}

void loop() {
    toggle ^= 1;
    digitalWrite(LED_PIN, toggle);
    delay(100);

    //时间在中断中处理
}

//水平同步结束，设置垂直同步
void isr_porch(void) {
    VGA_H_HIGH;
    y++;
    // 回到顶部
    if(y>=523) {
        y=1;
        v_active = 1;
        return;
    }
    // 其他vsync情况下
    if(y>=492) {
        VGA_V_HIGH;
        return;
    }
    if(y>=490) {
        VGA_V_LOW;
        return;
    }
    if(y>=479) { 
        v_active = 0;
        return;
    }
}

//水平方向清除的中断
void isr_start(void) {  
    // 如果没有在图像范围内
    if(!v_active) { return; }

    // 红色
    VGA_R_LOW;
    VGA_R_HIGH;

    // 对于每一个像素时显示对应的红色和白色
    for(x=0; x<32; x++) {
        if(logo[y/28][x/2]) {
            VGA_G_HIGH;
            VGA_B_HIGH;
        } else {
            VGA_G_LOW;
            VGA_B_LOW;
        }
    }
}

// 水平方向结束
void isr_stop(void) {
    if(!v_active) { return; }
    VGA_R_LOW;
    VGA_G_LOW;
    VGA_B_LOW;
}

//水平同步设置
void isr_update(void) {
    VGA_H_LOW;
}

