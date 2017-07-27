#include <Stepper.h>

// Constant Variables
#define STEPS 200 //Steps per revolution
const int max_distance = 6000; //Goes out to about 80cm. Since this reduces the amount of time spent until a pulse is recorded, it can essentially limit the distance it records
double duration;
int distance;
int steps = 50; //number of steps per incrementation

//From left to right: Green black red blue 
//Stepper Pins
int motorLeft_1 = 15;
int motorLeft_2 = 21;
int motorLeft_3 = 14;
int motorLeft_4 = 10;
int motorRight_1 = 17;
int motorRight_2 = 20;
int motorRight_3 = 16;
int motorRight_4 = 11;

//UltraSonic Sensor Pins
const int trigger1 = 0;
const int echo1 = 1;
const int trigger2 = 2;
const int echo2 = 3;
const int trigger3 = 4;
const int echo3 = 5;
const int max_distance = 6000; //Goes out to about 80cm. Since this reduces the amount of time spent until a pulse is recorded, it can essentially limit the distance it records
double duration;
int distance;

//Instantiating motors
Stepper motorLeft(STEPS, motorLeft_1, motorLeft_2, motorLeft_3, motorLeft_4);
Stepper motorRight(STEPS, motorRight_1, motorRight_2, motorRight_3, motorRight_4);

void setup() {
	pinMode(trigger1, OUTPUT);
	pinMode(echo1, INPUT);
	pinMode(trigger2, OUTPUT);
	pinMode(echo2, INPUT);
	pinMode(trigger3, OUTPUT);
	pinMode(echo3, INPUT);
	pinMode(motorLeft_1, OUTPUT);
	pinMode(motorLeft_2, OUTPUT);
	pinMode(motorLeft_3, OUTPUT);
	pinMode(motorLeft_4, OUTPUT);
	pinMode(motorRight_1, OUTPUT);
	pinMode(motorRight_1, OUTPUT);
	pinMode(motorRight_1, OUTPUT);
	pinMode(motorRight_1, OUTPUT);	
	Serial.begin(9600);
}

void loop() {
  
  
}



//-------------Sensor Functions----------------------------

//pulseRight
//Pulse right wall
//Inputs: None
//Outputs: Integer - wall distance in cm
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


//pulseLeft
//Pulse left wall
//Inputs: None
//Outputs: Integer - wall distance in cm
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

//pulseMiddle
//Pulse middle wall
//Inputs: None
//Outputs: Integer - wall distance in cm
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

//---------------------Motor Functions----------------------------
//Turn right Motor On
//Inputs: None
//Outputs: None
void rightMotorOn(){
    digitalWrite(motorRight_1, HIGH);
    digitalWrite(motorRight_2, LOW);
    digitalWrite(motorRight_3, HIGH);
    digitalWrite(motorRight_4, LOW);
}

//Turn left Motor On
//Inputs: None
//Outputs: None
void leftMotorOn(){
    digitalWrite(motorLeft_1, HIGH);
    digitalWrite(motorLeft_1, LOW);
    digitalWrite(motorLeft_1, HIGH);
    digitalWrite(motorLeft_1, LOW);
}

//Turn right Motor Off
//Inputs: None
//Outputs: None
void rightMotorOff(){
    digitalWrite(motorRight_1, LOW);
    digitalWrite(motorRight_2, HIGH);
    digitalWrite(motorRight_3, LOW);
    digitalWrite(motorRight_4, HIGH);
}

//Turn left Motor Off
//Inputs: None
//Outputs: None
void leftMotorOff(){
    digitalWrite(motorLeft_1, LOW);
    digitalWrite(motorLeft_2, HIGH);
    digitalWrite(motorLeft_3, LOW);
    digitalWrite(motorLeft_4, HIGH);
}

//Move the robot forward
//Inputs: int - Number of steps
//Outputs: None
void moveForward(int steps){
  for(int i = 0; i < steps; i++){
    motorLeft.step(1);
    motorRight.step(1);
  }
  leftMotorOff();
  rightMotorOff();
}

//Pivot robot left
//Inputs: int - Number of steps
//Outputs: None
void turnLeft(int steps){
  for(int i = 0; i < steps; i++){
    motorRight.step(1);
  }
}

//Pivot robot right
//Inputs: int - Number of steps
//Outputs: None
void turnRight(int steps){
  for(int i = 0; i < steps; i++){
    motorLeft.step(1);
  }
}

