/*
 * - Timer2 channel 1 输入捕获
 * - Timer2 channel 2 产生脉冲
 * - Timer 3 产生pwm信号
 */

const uint16_t pulseDelay = 200;
const uint16_t pulseWidth = 200;
//-----------------------------------------------------------------------------
void toggle_led()
{
	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
//-----------------------------------------------------------------------------
void setup()
{
	// 设置 PA1 (Timer2 channel 2) 输出pwm
	pinMode(PA1, PWM);
	// 设置 PA0 (Timer 2 channel 1) 为输入
	pinMode(PA0, INPUT);

	//在配置定时器之前停止它
	Timer2.pause();

	Timer2.setPrescaleFactor(72); 
	Timer2.setCompare(TIMER_CH2, pulseDelay);
	Timer2.setOverflow(pulseWidth + pulseDelay-1);

	// 计数器的数值
	TIMER2_BASE->CR1  = ( TIMER_CR1_OPM );
	Timer2.setSlaveFlags( TIMER_SMCR_TS_TI1FP1 | TIMER_SMCR_SMS_TRIGGER );

	// channel 1:在上升沿捕获输入
	Timer2.setMode(TIMER_CH1, TIMER_INPUT_CAPTURE);

	Timer2.setPolarity(TIMER_CH2, 1);

	// timer2 开启
	Timer2.refresh();
	Timer2.resume(); 

	//设置 PA6 (Timer3 channel 1) 产生 1ms 周期的pwm
	pinMode(PA6, PWM);
	Timer3.pause();
	Timer3.setPrescaleFactor(72); 
	Timer3.setCompare(TIMER_CH1, 100);
	Timer3.setOverflow(1000);
	Timer3.refresh();
	Timer3.resume(); 
}

uint32_t t;
//-----------------------------------------------------------------------------
void loop()
{
	if ( (millis()-t)>=1000 )
	{
		t = millis();
		toggle_led();
	}
}
