int analogPin=0;
int strobePin=2;
int resetPin=3;
int ledred=9;
int ledblue=10;
int ledgreen=11;
int spectrumValue[7];
int filter=190;

void setup(){
  
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  pinMode(strobePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  pinMode(ledred, OUTPUT);
  pinMode(ledblue, OUTPUT);
  pinMode(ledgreen, OUTPUT);
  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
}

void loop(){
  
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);
  for (int i=0;i<7;i++){
    digitalWrite(strobePin, LOW);
    delay(1);
    spectrumValue[i]=analogRead(analogPin);
    spectrumValue[i]=constrain(spectrumValue[i], filter, 1023);
    spectrumValue[i]=map(spectrumValue[i], filter,1023,0,255);
    Serial.print(spectrumValue[i]);
    Serial.print(" ");
    digitalWrite(strobePin, HIGH);
  }
  Serial.println();
  if(spectrumValue[0]>>spectrumValue[1]&&spectrumValue[0]>>spectrumValue[2]){
      analogWrite(ledred,spectrumValue[0]);
    }
   if(spectrumValue[1]>>spectrumValue[0]&&spectrumValue[1]>>spectrumValue[2]){
      analogWrite(ledred,spectrumValue[1]);
    }
    if(spectrumValue[2]>>spectrumValue[0]&&spectrumValue[2]>>spectrumValue[1]){
      analogWrite(ledred,spectrumValue[2]);
    }
    if(spectrumValue[2]>>spectrumValue[3]&&spectrumValue[2]>>spectrumValue[4]){
  analogWrite(ledgreen,spectrumValue[2]);
    }
    if(spectrumValue[3]>>spectrumValue[2]&&spectrumValue[3]>>spectrumValue[4]){
  analogWrite(ledgreen,spectrumValue[3]);
    }
    if(spectrumValue[4]>>spectrumValue[3]&&spectrumValue[4]>>spectrumValue[2]){
  analogWrite(ledgreen,spectrumValue[4]);
    }
    if(spectrumValue[4]>>spectrumValue[5]&&spectrumValue[4]>>spectrumValue[6]){
  analogWrite(ledblue,spectrumValue[4]);
    }
    if(spectrumValue[5]>>spectrumValue[4]&&spectrumValue[5]>>spectrumValue[6]){
  analogWrite(ledblue,spectrumValue[5]);
    }
    if(spectrumValue[6]>>spectrumValue[5]&&spectrumValue[6]>>spectrumValue[4]){
  analogWrite(ledblue,spectrumValue[6]);
    }
    else{
        analogWrite(ledred,0);
  analogWrite(ledgreen,0);
  analogWrite(ledblue,0);

      }
    /*
  analogWrite(ledred,spectrumValue[0]);
  analogWrite(ledred,spectrumValue[1]);
  analogWrite(ledred,spectrumValue[2]);
  analogWrite(ledgreen,spectrumValue[2]);
  analogWrite(ledgreen,spectrumValue[3]);
  analogWrite(ledgreen,spectrumValue[4]);
  analogWrite(ledblue,spectrumValue[4]);
  analogWrite(ledblue,spectrumValue[5]);
  analogWrite(ledblue,spectrumValue[6]);
  */
}
