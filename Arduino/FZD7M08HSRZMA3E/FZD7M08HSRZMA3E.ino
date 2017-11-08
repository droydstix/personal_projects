
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
    delay(2);
    spectrumValue[i]=analogRead(analogPin);
    spectrumValue[i]=constrain(spectrumValue[i], filter, 1023);
    spectrumValue[i]=map(spectrumValue[i], filter,1023,0,255);
    Serial.print(spectrumValue[i]);
    Serial.print(" ");
    digitalWrite(strobePin, HIGH);
  }
  Serial.println();
  analogWrite(ledred,spectrumValue[0]);
  analogWrite(ledred,spectrumValue[1]);
  analogWrite(ledblue,spectrumValue[5]);
  analogWrite(ledblue,spectrumValue[6]);
  analogWrite(ledgreen,spectrumValue[3]);
  analogWrite(ledgreen,spectrumValue[4]);
}

