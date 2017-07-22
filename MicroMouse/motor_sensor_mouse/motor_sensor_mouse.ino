#include <Stepper.h>

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

////Protoboard pin assignment
////Pin assignment for first motor\
////IC 1 (Left motor)
//int in1PinMotor1 = 9;
//int in2PinMotor1 = 10;
//int in3PinMotor1 = 11;
//int in4PinMotor1 = 12;
////Pin assignment for second motor
////IC 2 (Right motor)
//int in1PinMotor2 = 13;
//int in2PinMotor2 = 14;
//int in3PinMotor2 = 15;
//int in4PinMotor2 = 16;

//Protoboard pin assignment
//Pin assignment for first motor\
//IC 1 (Left motor)
int in1PinMotor1 = 15;
int in2PinMotor1 = 21;
int in3PinMotor1 = 14;
int in4PinMotor1 = 10;
//Pin assignment for second motor
//IC 2 (Right motor)
int in1PinMotor2 = 17;
int in2PinMotor2 = 20;
int in3PinMotor2 = 16;
int in4PinMotor2 = 11;

#define STEPS 200 //must be define, not int. Number based on how many increments per single revolution
 
Stepper motor1(STEPS, in1PinMotor1, in2PinMotor1, in3PinMotor1, in4PinMotor1); 
Stepper motor2(STEPS, in1PinMotor2, in2PinMotor2, in3PinMotor2, in4PinMotor2); 

void setup() {
  // put your setup code here, to run once:
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
  motor1.setSpeed(20);
  motor2.setSpeed(20);
Serial.begin(9600);
}

void loop() {
  //AWAITING algorithm. Turning functions subject to change depending on which method to solve
  motorsOff();
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
  motor1.step(-stepIncrementation);
  motor2.step(stepIncrementation);
}
void turnRight(){
  motor1.step(stepIncrementation);
  motor2.step(-stepIncrementation);
}
void forward(){
  motor1.step(stepIncrementation);
  motor2.step(stepIncrementation);
}

//Turning on an off motors to not expend current when not in use as we have no need to stabilize motors
//Both motors turn on and off at the same time as there is never a time when only one motor works. To turn, micromouse will spin on axis instead of pivoting
void motorsOn(){
    //Turning on motor 1 by setting all of its coiled pins to HIGH
    digitalWrite(in1PinMotor1, HIGH);
    digitalWrite(in2PinMotor1, HIGH);
    digitalWrite(in3PinMotor1, HIGH);
    digitalWrite(in4PinMotor1, HIGH); 
    //Turning on motor 2 by setting all of its coiled pins to HIGH
    digitalWrite(in1PinMotor2, HIGH);
    digitalWrite(in2PinMotor2, HIGH);
    digitalWrite(in3PinMotor2, HIGH);
    digitalWrite(in4PinMotor2, HIGH);
}

void motorsOff(){
    //Turning on motor 1 by setting all of its coiled pins to HIGH
    digitalWrite(in1PinMotor1, LOW);
    digitalWrite(in2PinMotor1, LOW);
    digitalWrite(in3PinMotor1, LOW);
    digitalWrite(in4PinMotor1, LOW);  
    //Turning on motor 2 by setting all of its coiled pins to HIGH
    digitalWrite(in1PinMotor2, LOW);
    digitalWrite(in2PinMotor2, LOW);
    digitalWrite(in3PinMotor2, LOW);
    digitalWrite(in4PinMotor2, LOW);
}

