//KY019 5V relay module
const int relay = 8; // relay turns trigger signal - active high;
const int water= A4;
void setup ()
{
  Serial.begin(9600);

  pinMode (relay, OUTPUT); // Define port attribute is output;
  pinMode (water,INPUT);
}
void loop ()
{
int waterread=analogRead(water);
  if(waterread>=1010){
  digitalWrite (relay, LOW); // relay off;
    Serial.print("water read: ");
       Serial.println(waterread);
  }
  else{
  digitalWrite (relay, HIGH); // relay  is turned on;
  Serial.print("water read: ");
     Serial.println(waterread);
  }
}
