
#include <Servo.h>
//Define L298N Dual H-Bridge Motor Controller Pins   head.write(0);
#define dir1PinL  2    //Motor direction
#define dir2PinL  4    //Motor direction
#define speedPinL 6    // Needs to be a PWM pin to be able to control motor speed
#define dir1PinR  7    //Motor direction
#define dir2PinR  8   //Motor direction
#define SERVO_PIN 9  //servo connect to D9
#define speedPinR 5    // Needs to be a PWM pin to be able to control motor speed
#define Echo_PIN_L    11 // Ultrasonic Echo pin connect to D11
#define Trig_PIN_L    12  // Ultrasonic Trig pin connect to D12
#define SPEED  150     //both sides of the motor speed
#define LEFT_SPEED  100     //back speed
#define RIGHT_SPEED  120     //back speed
#define WALL 15              // threshold

unsigned long currentMillis;
unsigned long previouswatch = 0;
const long interval_watch = 200;
int i;// for loop
int count = 1; // # blocks

int map_1;

bool left = false; //175
bool leftd = false;// 135
bool center = false; //90
bool rightd = false;//45
bool right = false; //5

int mySensVals[5] = {175, 135, 90, 45, 5};

bool in_region;

int line_reg;
int line_sense = 3; //port
int block_sense = 13; //port


Servo head;

/*motor control*/
void go_Advance(void)  //Forward
{
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL, LOW);
  digitalWrite(dir1PinR, HIGH);
  digitalWrite(dir2PinR, LOW);
}
void go_Left(void)  //Turn left
{
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL, LOW);
  digitalWrite(dir1PinR, LOW);
  digitalWrite(dir2PinR, HIGH);
}
void go_Right(void)  //Turn right
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL, HIGH);
  digitalWrite(dir1PinR, HIGH);
  digitalWrite(dir2PinR, LOW);
}
void go_Back(void)  //Reverse
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL, HIGH);
  digitalWrite(dir1PinR, LOW);
  digitalWrite(dir2PinR, HIGH);
}
void stop_Stop()    //Stop
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL, LOW);
  digitalWrite(dir1PinR, LOW);
  digitalWrite(dir2PinR, LOW);
}
/*set motor speed */
void set_Motorspeed(int speed_L, int speed_R)
{
  analogWrite(speedPinL, speed_L);
  analogWrite(speedPinR, speed_R);
}
//Pins initialize
void init_GPIO()
{
  pinMode(dir1PinL, OUTPUT);
  pinMode(dir2PinL, OUTPUT);
  pinMode(speedPinL, OUTPUT);

  pinMode(dir1PinR, OUTPUT);
  pinMode(dir2PinR, OUTPUT);
  pinMode(speedPinR, OUTPUT);
  pinMode(Trig_PIN_L, OUTPUT);
  pinMode(Echo_PIN_L, INPUT);

  pinMode(line_sense, INPUT);
  pinMode(block_sense, INPUT);

  stop_Stop();
}

/*detection of ultrasonic distance*/
int watch(int head_val) {
  long echo_distance;
  digitalWrite(Trig_PIN_L, LOW);
  delay(5);
  digitalWrite(Trig_PIN_L, HIGH);
  delay(15);
  digitalWrite(Trig_PIN_L, LOW);
  echo_distance = pulseIn(Echo_PIN_L, HIGH);
  echo_distance = echo_distance * 0.01657; //how far away is the object in cm
  map_1 = echo_distance;

  if (head_val == 175 && map_1 < WALL) {
    left = true;
  }
  else if (head_val == 175 && map_1 > WALL) {
    left = false;
  }
  if (head_val == 135 && map_1 < WALL) {
    leftd = true;
  }
  else if (head_val == 135 && map_1 > WALL) {
    leftd = false;
  }
  if (head_val == 90 && map_1 < WALL) {
    center = true;
  }
  else if (head_val == 90 && map_1 > WALL) {
    center = false;
  }
  if (head_val == 45 && map_1 < WALL) {
    rightd = true;
  }
  else if (head_val == 45 && map_1 > WALL) {
    rightd = false;
  }
  if (head_val == 5 && map_1 < WALL) {
    right = true;
  }
  else if (head_val == 5 && map_1 > WALL) {
    right = false;
  }
  return round(echo_distance);
}



void watch_line() {
  line_reg = digitalRead(line_sense);
}

void watch_block () {

}

void setup()
{
  init_GPIO();
  stop_Stop();//Stop
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  head.attach(SERVO_PIN);
  head.write(175);
  //delay(4000);
}
void loop() {
  currentMillis = millis();
  watch_line();
  watch_block();

  if (count < 5) {
      
      
    if (line_reg == 0 && in_region == false) {
        for (i=0;i < 5; i++) {
        stop_Stop();
        delay(500);
        head.write(mySensVals[i]);
        watch(mySensVals[i]);
        Serial.println("watching");
      }
      if ((left == false || leftd == false  || rightd == false || right == false) && center == false) {
        Serial.println("Forward");
        set_Motorspeed(LEFT_SPEED, RIGHT_SPEED);
        go_Advance();
        delay(200);
      }

      else if ((left == true || leftd == true) &&  (rightd == false || right == false)) {
       Serial.println("right");
        set_Motorspeed(LEFT_SPEED, 0);
        go_Advance();
delay(200);
      }

      else if ((rightd == true || right == true) && (left == false || leftd == false)) {
        Serial.println("left");
        set_Motorspeed(0, RIGHT_SPEED);
        go_Advance();
delay(200);
      }
      else if (center == true) {
        set_Motorspeed(LEFT_SPEED, RIGHT_SPEED);
        go_Back();
        Serial.println("wall front");
        delay(200);
      }

    }


    else if (line_reg == 1 && in_region == false) {
      //watch front
      in_region = true;
      Serial.println("region");
    }

    else if (line_reg == 1 && in_region == true && map_1 > WALL) {

      Serial.println("in region, turning right");
    }

    else if (line_reg == 0 && in_region == true && map_1 > WALL) {

      Serial.println("in region, turning left");
    }

    else if (line_reg == 1 && in_region == true && map_1 < WALL) {

      Serial.println("WALL front line");
      in_region = false;

    }
    else if (line_reg == 0 && in_region == true && map_1 < WALL) {

      Serial.println("WALL front no line");
      in_region = false;

    }
  }

  else if (count >= 5 && in_region == false ) {


    Serial.println("going home");



    if (left == false && leftd == false && center == false && rightd == false && right == false) {
      go_Advance();
    }

    else if ((left == true || leftd == true) && center == false && rightd == false && right == false) {
      go_Right();
    }

    else if (left == false && leftd == false && center == false && (rightd == true || right == true)) {
      go_Left();
    }
  }
}
