
#include "TimerOne.h"
#define redled 9
int red=0;
void setup()
{
  Serial.begin(9600);
  pinMode(redled, OUTPUT);
  Timer1.initialize(500000);         // initialize timer1, and set a 1/2 second period
  Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt  
}
void callback()        // timer compare interrupt service routine
{
  for(red=0;red<=255;red+=1){
    analogWrite(redled,red);
    }
    for(red=255;red>=0;red-=1){
    analogWrite(redled,red);
    }

}

void loop()
{
  Serial.println(red);

  // your program here...
}
