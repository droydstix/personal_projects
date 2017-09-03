
int sol1 = 13;
int sol2=12;
int swt1=7;
int val1=0;
void setup() {
  Serial.begin(9600);
  pinMode(sol1, OUTPUT);
  pinMode(sol2, OUTPUT);
  pinMode(swt1, INPUT);
}

void loop() {
  val1=digitalRead(swt1);
      digitalWrite(sol1, HIGH); 
      digitalWrite(sol2, LOW);
        Serial.println(val1);  

 delay(1000);
      digitalWrite(sol1, LOW); 
      digitalWrite(sol2, HIGH);
      delay(1000);

  Serial.println(val1);  
}
