int tempsen= A0;
int coolerout=13;

void setup() {
  Serial.begin(9600);
pinMode(tempsen,INPUT);
pinMode(coolerout,OUTPUT);
}

void loop() {
 int temp=analogRead(tempsen);
if(temp<=500){
  digitalWrite(coolerout,HIGH);
  }
  else{
      digitalWrite(coolerout,LOW);
    }
    Serial.println(temp);
}
