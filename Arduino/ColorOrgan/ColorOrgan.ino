// Arduino LED Color Organ Kit
//https://www.youtube.com/user/greatscottlab/


int analogPin=0;      //connects to the Output of the MSGEQ7, Measures the voltage value for each frequency band (0V-5V) 
int strobePin=2;      //connects to the Strobe Pin of the MSGEQ7, controls the Multiplexer and thus switches between the frequency bands
int resetPin=3;       //connects to the Reset Pin of the MSGEQ7, controls the Multiplexer and let's it restart with the lowest frequency band
int ledred=9;         //connects to the Gate of the BUZ11 MOSFET of the RED LED (Bass) and creates a PWM signal with variable duty cycle which depends of the peak value of the low frequencies to control the brightness of the RED LED 
int ledgreen=10;      //connects to the Gate of the BUZ11 MOSFET of the GREEN LED (Middle) and creates a PWM signal with variable duty cycle which depends of the peak value of the middle frequencies to control the brightness of the GREEN LED
int ledblue=11;       //connects to the Gate of the BUZ11 MOSFET of the BLUE LED (High) and creates a PWM signal with variable duty cycle which depends of the peak value of the high frequencies to control the brightness of the BLUE LED
int spectrumValue[7]; //Integer variable to store the 10bit values of the frequency bands
int filter=80;        //There will always be some noises which the analogpin will receive. With this filter value we can ignore the very low peaks of the output of the MSGEQ7. Fell free to adjust this value to your liking

void setup(){  
  
  Serial.begin(9600);         //needed to output the values of the frequencies bands on the serial monitor 
  pinMode(analogPin, INPUT);  //defines analog pin A0 as an Input
  pinMode(strobePin, OUTPUT); //defines strobe pin 2 as Output
  pinMode(resetPin, OUTPUT);  //defines reset pin 3 as Output
  pinMode(ledred, OUTPUT);    //defines ledred pin 9 as Output
  pinMode(ledblue, OUTPUT);   //defines ledblue pin 10 as Output
  pinMode(ledgreen, OUTPUT);  //defines ledgreen pin 11 as Output
  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
}

void loop(){
  
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);              //change from high to low starts the output of the mutliplexer from the beginning 
  for (int i=0;i<7;i++){                    //for loop goes through this cycle 7 times to get the values for each frequency band
    digitalWrite(strobePin, LOW);           //puts strobe pin low to output the frequency band
    delayMicroseconds(30);                  //wait until output value of MSGEQ7 can be measured (see timing diagram in the datasheet)
    spectrumValue[i]=analogRead(analogPin); //put analog DC value in the spectrumValue variable
    if (spectrumValue[i]<filter){ 
      spectrumValue[i]=0;}                  //if the received value is below the filter value it will get set to 0
    spectrumValue[i]=map(spectrumValue[i], 0,1023,0,255); //transform the 10bit analog input value to a suitable 8bit PWM value
    Serial.print(spectrumValue[i]);         //outputs the PWM value on the serial monitor 
    Serial.print(" ");
    digitalWrite(strobePin, HIGH);          //puts the strobe pin high to get ready for the next cycle
  }
  Serial.println();
  analogWrite(ledred,spectrumValue[0]);   //outputs the 63Hz PWM Value for the RED LED
  analogWrite(ledred,spectrumValue[1]);   //outputs the 160Hz PWM Value for the RED LED
  analogWrite(ledgreen,spectrumValue[3]); //outputs the 1kHz PWM Value for the GREEN LED
  analogWrite(ledgreen,spectrumValue[4]); //outputs the 2.5kHz PWM Value for the GREEN LED
  analogWrite(ledblue,spectrumValue[5]);  //outputs the 6.25kHz PWM Value for the BLUE LED
  analogWrite(ledblue,spectrumValue[6]);  //outputs the 16kHz PWM Value for the BLUE LED
}


