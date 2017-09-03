long red;
long green;
long blue;



#define led1 12
#define led2 11
#define led3 10


void setup()
{
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

}

void loop()
{
red=random(256);
green=random(256);
blue=random(256);
analogWrite(led1,red);
analogWrite(led2,green);
analogWrite(led3,blue);
delay(10000);


}

