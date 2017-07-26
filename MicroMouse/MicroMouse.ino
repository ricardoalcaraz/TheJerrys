//#include <NewPing.h>
#include <Stepper.h>

// Constant Variables
#define STEPS 200 //Steps per revolution
#define SONAR_NUM 3 //Number of sensors
#define MAX_DISTANCE 200 //Max Distance we want to measure
#define PING_INTERVAL 33//Milliseconds between pings


//Green black red blue from left to right
//Stepper Pins
#define stepperRight 11
#define stepperRightDir 12
#define stepperLeft 21
#define stepperLeftDir 20

//UltraSonic Sensor Pins
#define ECHO_1 5
#define TRIGGER_1 6
#define ECHO_2 17
#define TRIGGER_2 16
#define ECHO_3 2
#define TRIGGER_3 3




void setup() {

  
}

void loop() {
  
  
}



//-------------Sensor Functions----------------------------

//pulseRight
//Pulse right wall
//Inputs: None
//Outputs: Integer - wall distance
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
//Outputs: Integer - wall distance
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
//Outputs: Integer - wall distance
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
    stepperRight.step(1);
    stepperLeft.step(1);
  }
  leftMotorOff();
  rightMotorOff();
}


