/*
通过led来模拟莫尔斯电码
 
*/
#define LED_PIN LED_BUILTIN 
#define TIMECONSTANT 100

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    sendMorse("-- .- .--. .-.. .   ");
}

void sendMorse(char *dotsAndDashes)
{
  while(*dotsAndDashes!=0)
  {
    switch(*dotsAndDashes)
    {
      case '-':
        digitalWrite(LED_PIN,HIGH);
        delay(TIMECONSTANT*3);
        digitalWrite(LED_PIN,LOW);
        delay(TIMECONSTANT);
        break;
      case '.':
        digitalWrite(LED_PIN,HIGH);
        delay(TIMECONSTANT);
        digitalWrite(LED_PIN,LOW);
        delay(TIMECONSTANT);
        break;   
      case ' ':   
      default:
        digitalWrite(LED_PIN,LOW);
        delay(TIMECONSTANT*3);
        break;   
    }
    dotsAndDashes++;
  }
}
