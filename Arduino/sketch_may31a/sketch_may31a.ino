#define ledPin 4
int ledb = 7;           // the PWM pin the LED is attached to
int cntf=0;;
int cntb=0;


void setup()
{
 pinMode(ledPin, OUTPUT);
     pinMode(ledb, OUTPUT);


 // initialize timer1 
 noInterrupts();    // disable all interrupts
 TCCR1A = 0;
 TCCR1B = 0;

 TCNT1 = cntf;            // preload timer;    // preload timer 65536-16MHz/256/1Hz
 TCCR1B |= (1 << CS12);    // 256 prescaler 
 TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
 interrupts();    // enable all interrupts
  
 Serial.begin(9600);
}



ISR(TIMER1_OVF_vect)
{
      TCNT1 = cntf;            // preload timer
   digitalWrite(ledPin, digitalRead(ledPin)^1);
                Serial.println(" "); 

     Serial.println("Front ");
     Serial.print(cntf);  
  cntf++;
if(cntf>31250){
  cntf=0;
  }
}



void loop()
{
digitalWrite(ledb, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(cntb);                       // wait for a second
  digitalWrite(ledb, LOW);    // turn the LED off by making the voltage LOW
  delay(cntb);
  cntb++; 
  if(cntb>31250){
    cntb=0;
    }
             Serial.println(" "); 
         Serial.println("Back "); 
         Serial.println(cntb); 

}

