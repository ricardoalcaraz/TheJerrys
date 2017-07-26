#include <Stepper.h>

// Constant Variables
#define STEPS 200 //Steps per revolution
const int max_distance = 6000; //Goes out to about 80cm. Since this reduces the amount of time spent until a pulse is recorded, it can essentially limit the distance it records
double duration;
int distance;

//From left to right: Green black red blue 
//Stepper Pins
int motor1_1 = 15;
int motor1_2 = 21;
int motor1_3 = 14;
int motor1_4 = 10;
int motor2_1 = 17;
int motor2_2 = 20;
int motor2_3 = 16;
int motor2_4 = 11;

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
Stepper motor1(STEPS, motor1_1, motor1_2, motor1_3, motor1_4);
Stepper motor2(STEPS, motor2_1, motor2_2, motor2_3, motor2_4);

void setup() {
	pinMode(trigger1, OUTPUT);
	pinMode(echo1, INPUT);
	pinMode(trigger2, OUTPUT);
	pinMode(echo2, INPUT);
	pinMode(trigger3, OUTPUT);
	pinMode(echo3, INPUT);
	pinMode(motor1_1, OUTPUT);
	pinMode(motor1_2, OUTPUT);
	pinMode(motor1_3, OUTPUT);
	pinMode(motor1_4, OUTPUT);
	pinMode(motor2_1, OUTPUT);
	pinMode(motor2_2, OUTPUT);
	pinMode(motor2_3, OUTPUT);
	pinMode(motor2_4, OUTPUT);	
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
    digitalWrite(motor2_1, HIGH);
    digitalWrite(motor2_2, LOW);
    digitalWrite(motor2_3, HIGH);
    digitalWrite(motor2_4, LOW);
}

//Turn left Motor On
//Inputs: None
//Outputs: None
void leftMotorOn(){
    digitalWrite(motor1_1, HIGH);
    digitalWrite(motor1_2, LOW);
    digitalWrite(motor1_3, HIGH);
    digitalWrite(motor1_4, LOW);
}

//Turn right Motor Off
//Inputs: None
//Outputs: None
void rightMotorOff(){
    digitalWrite(motor2_1, LOW);
    digitalWrite(motor2_2, HIGH);
    digitalWrite(motor2_3, LOW);
    digitalWrite(motor2_4, HIGH);
}

//Turn left Motor Off
//Inputs: None
//Outputs: None
void leftMotorOff(){
    digitalWrite(motor1_1, LOW);
    digitalWrite(motor1_2, HIGH);
    digitalWrite(motor1_3, LOW);
    digitalWrite(motor1_4, HIGH);
}

//Move the robot forward
//Inputs: int - Number of steps
//Outputs: None
void moveForward(int steps){
  for(int i = 0; i < steps; i++){
    motor1.step(1);
    motor2.step(1);
  }
  leftMotorOff();
  rightMotorOff();
}

//Move the robot left and goes forward
//Inputs: int - Number of steps
//Outputs: None
void moveLeft(int steps){
  for(int i = 0; i < steps; i++){
    motor1.step(1);
    motor2.step(1);
  }
	moveForward(steps);
}

//---------------------Movement Functions-------------------------------------------------
//Care has to be taken with the speed
//Motors use approximately 1A each at 100 rpm and .5A at 200 rpm
//150rpm is a good balance of speed and torque




//Move the robot right and goes forward
//Inputs: int - Number of steps
//Outputs: None
void moveRight(int steps){
  for(int i = 0; i < steps; i++){
    motor1.step(1);
    motor2.step(1);
  }
  moveForward(steps);
}

