
int sensorValue = 0;
int RelayControl =4;
void setup()
{
  pinMode(RelayControl, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop()
{
  // read the input on analog pin 0:
  sensorValue = analogRead(A0);
  // print out the value you read:
  //Serial.println(sensorValue);
  if(sensorValue<100){
  digitalWrite(RelayControl, LOW);
  }
  else if(sensorValue>228){
  digitalWrite(RelayControl, HIGH);
  }
}
