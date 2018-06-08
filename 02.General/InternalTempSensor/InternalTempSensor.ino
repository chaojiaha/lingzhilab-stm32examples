/*
内部温度测量
*/

//#include <stdio.h>
#include <libmaple/adc.h>

#define LED_PIN LED_BUILTIN
#define A_RANDOM_ANALOG_PIN 15

void setup_temperature_sensor() {
  adc_reg_map *regs = ADC1->regs;


//从power down 模式唤醒
  regs->CR2 |= ADC_CR2_TSVREFE;

// 设置采集通道 16
  regs->SMPR1 = (0b111 << (3*6));   
}

void setup(void)
{
  pinMode(LED_PIN, OUTPUT);
  
// 设置为模拟输入模式
  pinMode(A_RANDOM_ANALOG_PIN, INPUT_ANALOG);
  
// 初始化内部温度传感器
  setup_temperature_sensor();
	
  Serial.begin(9600);
  
}

//每秒采集一次数据并从串口打印显示
//
void loop(void)
{
  uint16 vsense, alogpin;
  uint32 t1, t2, t3;
  char buf[64];
  
  t1 = micros();
  alogpin = analogRead(A_RANDOM_ANALOG_PIN);
  t2 = micros();
  vsense = adc_read(ADC1, 16);
  t3 = micros();
	
  Serial.print("ADC值(hex)："); Serial.println(vsense, 16);
  Serial.print("时间(us)："); Serial.println(t3-t2, 16);
  Serial.print("模拟输入值(hex)："); Serial.println(alogpin, 16);
  Serial.print("时间(us)："); Serial.println(t2-t1, 16);

  digitalWrite(LED_PIN,!digitalRead(LED_PIN));// 翻转led电平
  delay(1000);
}


