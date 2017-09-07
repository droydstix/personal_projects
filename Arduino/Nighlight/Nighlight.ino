int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 12;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  if(sensorValue>= 900){
  digitalWrite(ledPin, HIGH);
  }
  else
  digitalWrite(ledPin, LOW);
}
