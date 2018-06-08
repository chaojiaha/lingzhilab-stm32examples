/*
 * - Timer2 channel 1 捕获输入
 * - Timer3 产生pwm
 */

#include <Streaming.h>

const uint8_t pwmPulse = 20; // ms
const uint8_t pwmPeriod = 50; // ms
//-----------------------------------------------------------------------------
void toggle_led()
{
	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
//-----------------------------------------------------------------------------
void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);

	//设置 PA0 (Timer 2 channel 1) 输入捕获
	pinMode(PA0, INPUT);

	while (!Serial); delay(1000);

	// 配置定时器之前停止它
	Timer2.pause();
	Timer3.pause();

	Timer2.setPrescaleFactor(72); 

	// 配置 timer 2 channel 1 在上升沿捕获
	Timer2.setInputCaptureMode(TIMER_CH1, TIMER_IC_INPUT_DEFAULT); 
	// 配置 timer 2 channel 2 在下降沿捕获
	Timer2.setInputCaptureMode(TIMER_CH2, TIMER_IC_INPUT_SWITCH); 
	Timer2.setPolarity(TIMER_CH2, 1); // 在下降沿反转

	Timer2.setSlaveFlags( TIMER_SMCR_TS_TI1FP1 | TIMER_SMCR_SMS_RESET );

	Timer2.refresh();
	Timer2.getCompare(TIMER_CH1); // 清除标志
	Timer2.getCompare(TIMER_CH2);
	Timer2.resume(); //开启timer 2

	// 配置 PA6 (Timer3 channel 1) 产生周期为1ms的pwm
	pinMode(PA6, PWM);
	Timer3.setPrescaleFactor(72); 
	Timer3.setCompare(TIMER_CH1, pwmPulse*1000);
	Timer3.setOverflow(pwmPeriod*1000);
	Timer3.refresh();

	Timer3.resume(); //开启timer3

	while ( !Timer2.getInputCaptureFlag(TIMER_CH1) );
	Timer2.getCompare(TIMER_CH1); 
}
//-----------------------------------------------------------------------------
void loop()
{
	if ( Timer2.getInputCaptureFlag(TIMER_CH2) ) 
	{
		Serial << "pwm 脉宽: " << Timer2.getCompare(TIMER_CH2);
	}
	if ( Timer2.getInputCaptureFlag(TIMER_CH1) ) 
	{
		Serial << ", 周期: " << Timer2.getCompare(TIMER_CH1) << endl;
		toggle_led();
	}
}
