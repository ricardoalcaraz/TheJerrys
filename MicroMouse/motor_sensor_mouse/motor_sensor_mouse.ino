#include <Stepper.h> //Using built in library for stepper motors

//Letting program know where pins are located
const int trigger1 = 0;
const int echo1 = 1;
const int trigger2 = 2;
const int echo2 = 3;
const int trigger3 = 4;
const int echo3 = 5;
const int max_distance = 6000; //Goes out to about 80cm. Since this reduces the amount of time spent until a pulse is recorded, it can essentially limit the distance it records
double duration;
int distance;
int stepIncrementation = 100;
#define STEPS 200 //must be define, not int. Number based on how many increments per single revolution

//Pin assignment for first motor
//IC 1 (Left motor)
int LMotor1 = 15;
int LMotor2 = 21;
int LMotor3 = 14;
int LMotor4 = 10;

//Pin assignment for second motor
//IC 2 (Right motor)
int RMotor1 = 17;
int RMotor2 = 20;
int RMotor3 = 16;
int RMotor4 = 11;

//Creating instances of a motor
Stepper LMotor(STEPS, LMotor1, LMotor2, LMotor3, LMotor4); 
Stepper RMotor(STEPS, RMotor1, RMotor2, RMotor3, RMotor4); 

void setup() {
  pinMode(trigger1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trigger2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trigger3, OUTPUT);
  pinMode(echo3, INPUT);
  pinMode(in1PinMotor1, OUTPUT);
  pinMode(in2PinMotor1, OUTPUT);
  pinMode(in3PinMotor1, OUTPUT);
  pinMode(in4PinMotor1, OUTPUT);
  pinMode(in1PinMotor2, OUTPUT);
  pinMode(in2PinMotor2, OUTPUT);
  pinMode(in3PinMotor2, OUTPUT);
  pinMode(in4PinMotor2, OUTPUT);
  LMotor.setSpeed(20);
  RMotor.setSpeed(20);
  Serial.begin(9600);
}

void loop() {
  motorsOff(); //Has motor always turned off at start
  if (pulseRight() > 20){
    Serial.println("Can turn RIGHT and engage BOTH or ONE motor.");
    motorsOn();
    turnRight();
  }
  if (pulseLeft() > 20){
    Serial.println("Can turn LEFT and engage BOTH or ONE motor.");
    motorsOn();
    turnLeft();
  }
  if (pulseMiddle() > 20){
    Serial.println("Can move FORWARD and engage BOTH motors.");
    motorsOn();
    turnRight();
  }
  delay(100);
}


//Sensor functions
int pulseRight() {
  digitalWrite(trigger1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger1, LOW);

  //Read the echo pin
  duration = pulseIn(echo1, HIGH, max_distance);

  //Calculate distance
  distance = duration*0.034/2;

  Serial.print("Right distance: "); Serial.println(distance);
  return distance;
}

int pulseLeft() {
  digitalWrite(trigger2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger2, LOW);

  //Read the echo pin
  duration = pulseIn(echo2, HIGH, max_distance);

  //Calculate distance
  distance = duration*0.034/2;

  Serial.print("Left distance: "); Serial.println(distance);
  return distance;
}

int pulseMiddle() {
  digitalWrite(trigger3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger3, LOW);

  //Read the echo pin
  duration = pulseIn(echo3, HIGH, max_distance);

  //Calculate distance
  distance = duration*0.034/2;

  Serial.print("Middle distance: "); Serial.println(distance);
  return distance;
}

//Motor functions
void turnLeft(){
  LMotor.step(-stepIncrementation);
  RMotor.step(stepIncrementation);
}
void turnRight(){
  LMotor.step(stepIncrementation);
  RMotor.step(-stepIncrementation);
}
void forward(){
  LMotor.step(stepIncrementation);
  RMotor.step(stepIncrementation);
}

//Turning on an off motors to not expend current when not in use as we have no need to stabilize motors
//Both motors turn on and off at the same time as there is never a time when only one motor works. To turn, micromouse will spin on axis instead of pivoting
void motorsOn(){
    //Turning on motor 1 by setting all of its coiled pins to HIGH
    digitalWrite(LMotor1, HIGH);
    digitalWrite(LMotor2, HIGH);
    digitalWrite(LMotor3, HIGH);
    digitalWrite(LMotor4, HIGH); 
    //Turning on motor 2 by setting all of its coiled pins to HIGH
    digitalWrite(RMotor1, HIGH);
    digitalWrite(RMotor2, HIGH);
    digitalWrite(RMotor3, HIGH);
    digitalWrite(RMotor4, HIGH);
}

void motorsOff(){
    //Turning on motor 1 by setting all of its coiled pins to LOW
    digitalWrite(LMotor1, LOW);
    digitalWrite(LMotor2, LOW);
    digitalWrite(LMotor3, LOW);
    digitalWrite(LMotor4, LOW); 
    //Turning on motor 2 by setting all of its coiled pins to LOW
    digitalWrite(RMotor1, LOW);
    digitalWrite(RMotor2, LOW);
    digitalWrite(RMotor3, LOW);
    digitalWrite(RMotor4, LOW);
}

