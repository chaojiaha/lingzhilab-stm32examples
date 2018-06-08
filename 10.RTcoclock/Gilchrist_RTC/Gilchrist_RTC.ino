/*
 *	rtc时钟的设置和使用，包括它的中断使用
 */

#include "RTClock.h"

#define BOARD_LED_PIN LED_BUILTIN

int globAlmCnt = 0;
int globOvCnt = 0;
int globSecCnt = 0;
int specAlmCnt = 0;
int lastGlobAlmCnt = -1;
int lastSpecAlmCnt = -1;

void rtc_sec_intr() { if (rtc_is_second()) globSecCnt++; }
void rtc_ovf_intr() { if (rtc_is_overflow()) globOvCnt++; }
void rtc_glob_alm_intr() { if (rtc_is_alarm()) globAlmCnt++; }
void rtc_spec_alm_intr() { if (rtc_is_alarm()) specAlmCnt++; }

void setup() {

    pinMode(BOARD_LED_PIN, OUTPUT);
	delay(5000);
	Serial.begin(9600);
	Serial.println("begin RTC blink");
	delay(1000);	

	rtc_init(RTCSEL_LSI);
	rtc_set_prescaler_load(0x7fff);
	rtc_set_count(0);
	
	rtc_attach_interrupt(RTC_SECONDS_INTERRUPT, rtc_sec_intr);
	rtc_attach_interrupt(RTC_OVERFLOW_INTERRUPT, rtc_ovf_intr); // expected every 128000 seconds
	rtc_attach_interrupt(RTC_ALARM_GLOBAL_INTERRUPT, rtc_glob_alm_intr);
	rtc_attach_interrupt(RTC_ALARM_SPECIFIC_INTERRUPT, rtc_spec_alm_intr);
}

void loop() {
	int i,n;
	
	Serial.print("Time + interrupt counts: ");
	Serial.print(rtc_get_count());
	Serial.print(".");
	Serial.print(rtc_get_divider());
	Serial.print(" (");
	Serial.print(globSecCnt);
	Serial.print(", ");
	Serial.print(globOvCnt);
	Serial.print(", ");
	Serial.print(globAlmCnt);
	Serial.print(", ");
	Serial.print(specAlmCnt);
	Serial.println(")");

	delay(1000);

	digitalWrite(BOARD_LED_PIN, 1);
	if ((lastSpecAlmCnt != specAlmCnt) || (lastGlobAlmCnt != globAlmCnt)){
		lastGlobAlmCnt = globAlmCnt;
		lastSpecAlmCnt = specAlmCnt;

		Serial.println(" -- alarm -- ");
		for (i=0;i<3;i++) { digitalWrite(BOARD_LED_PIN, 0); delay(100); digitalWrite(BOARD_LED_PIN, 1); delay(100);}
		n = rtc_get_count() + 5;
		rtc_set_alarm(n);
	}
	
	delay(1000);
	digitalWrite(BOARD_LED_PIN, 0);
}


