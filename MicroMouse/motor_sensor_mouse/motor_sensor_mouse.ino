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

//Pin assignment for first motor
int motor1_1 = 17;
int motor1_2 = 20;
int motor1_3 = 16;
int motor1_4 = 11;
//Pin assignment for second motor
int motor2_1 = 15;
int motor2_2 = 21;
int motor2_3 = 14;
int motor2_4 = 10;
//Pin for switches
int switches[] = {6,7,8,9};

#define STEPS 200 //must be define, not int. Number based on how many increments per single revolution
 
Stepper stepperLeft= Stepper(200, motor1_1, motor1_2, motor1_3, motor1_4);
Stepper stepperRight= Stepper(200, motor2_1, motor2_2, motor2_3, motor2_4);

void setup() {
  // put your setup code here, to run once:
  pinMode(trigger1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trigger2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trigger3, OUTPUT);
  pinMode(echo3, INPUT);
  for(int i = 10; i < 22; i++){
    pinMode(i, OUTPUT);
  }
  for(int i = 6; i < 10; i++){
    pinMode(i, INPUT);
  }
  stepperRight.setSpeed(150);
  stepperLeft.setSpeed(150);
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:

    
    
    moveForward(200);
    for(int i = 6; i < 10; i++){
      Serial.print("Pin ");Serial.print(i);Serial.print(" : ");Serial.println(digitalRead(i));
    }
    delay(1000);
    
}

void rightMotorOff(){
    digitalWrite(motor2_1, LOW);
    digitalWrite(motor2_2, HIGH);
    digitalWrite(motor2_3, LOW);
    digitalWrite(motor2_4, HIGH);
}

void leftMotorOff(){
    digitalWrite(motor1_1, LOW);
    digitalWrite(motor1_2, HIGH);
    digitalWrite(motor1_3, LOW);
    digitalWrite(motor1_4, HIGH);
}

void moveForward(int steps){
  for(int i = 0; i < steps; i++){
    stepperRight.step(1);
    stepperLeft.step(1);
  }
  leftMotorOff();
  rightMotorOff();
}

void moveRight(){
  
}


