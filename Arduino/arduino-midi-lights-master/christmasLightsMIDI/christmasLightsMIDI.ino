/* 
 *  Christmas New year light show with Arduino
 *  by Akshay James
 *  techmusician.wordpress.com
 * 
 * This project was inspired from a YouTube video by John Storms
 * from his channel ListenToOurLights (http://www.youtube.com/user/listentoourlights).
 * Thank you.

 * GND (pin 8) to ground,
 * Vcc (pin 16) to 5V
 * OE (pin 13) to ground
 * MR (pin 10) to 5V
 * 
 * DS (pin 14) to Ardunio DigitalPin 9 (blue wire)
 * SH_CP (pin 11) to to Ardunio DigitalPin 8 (yellow wire)
 * ST_CP (pin 12) to Ardunio DigitalPin 10 (green wire)
 */


/*
 * Which bit has to be turned ON or OFF is found
 * with the below function.
 * 
 * The range of music notes used for the control
 * of lights is from C3 to E6.
 * (sharp notes are excluded)     (total 24 lights)
 * 
 * So, this function will return the number of the bit
 * to be set.
 * For eg, C3(note 62) corresponds to the first light.
 * So this function will return '1'.
 * 
 * Similarly, '2' is returned for D3(note 64), etc.
 * 
 */

int getBit(int p) {
  switch(p) {
    case 60: return 0; //note C3 (middle C)
    case 62: return 1; //D3
    case 64: return 2; //E3
    case 65: return 3; //F3
    case 67: return 4; //G3
    case 69: return 5; //A3
    case 71: return 6; //B3
    case 72: return 7; //C4
    case 74: return 8; //D4
    case 76: return 9; //E4
    case 77: return 10; //F4
    case 79: return 11; //G4
    case 81: return 12; //A4
    case 83: return 13; //B4
    case 84: return 14; //C5
    case 86: return 15; //D5
    case 88: return 16; //E5
    case 89: return 17; //F5
    case 91: return 18; //G5
    case 93: return 19; //A5
    case 95: return 20; //B5
    case 96: return 21; //C6
    case 98: return 22; //D6
    case 100: return 23; //E6
  }
}


//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 9;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 8;
//Pin connected to Data in (DS) of 74HC595
const int dataPin = 10;

int pitch, cmd, velocity;
int light;
boolean state;

byte lightData1 = 0, lightData2 = 0, lightData3 = 0; //

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(38400);
  
}

void loop() {

  //read the midi signal
  if(Serial.available()>2) {
    cmd = Serial.read();
    pitch = Serial.read();
    velocity = Serial.read();
  
  //the lights are set according to the data on MIDI ch.1
  if(cmd==144) state=0;               //144 ch1 noteON ; 0=relayON
  else if(cmd==128) state=1;        //128 ch1 noteOFF  ; 1=relayOFF
    
  // so that lights don't change while the new data is being shifted
  digitalWrite(latchPin, LOW);

  light = getBit(pitch);
  // set the corresponding bit in lightData
  if(light<8)
    bitWrite(lightData1, light, state);
  else if(light<16){
    light-=8;
    bitWrite(lightData2, light, state);
  }
  else {
    light-=16;
    bitWrite(lightData3, light, state);
  }
    
  
  // shift out the data
  shiftOut(dataPin, clockPin, MSBFIRST, lightData3);
  shiftOut(dataPin, clockPin, MSBFIRST, lightData2);
  shiftOut(dataPin, clockPin, MSBFIRST, lightData1);

  // turn on the lights according to the new data
  digitalWrite(latchPin, HIGH);

  }
}
