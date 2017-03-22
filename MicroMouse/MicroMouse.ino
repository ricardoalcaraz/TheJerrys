#include <Stepper.h>

// Variables
const int stepsPerRevolution = 200;
//Green black red blue from left to right
//Stepper Pins
const int stepperRight = 11;
const int stepperRightDir = 12;
const int stepperLeft = 21;
const int stepperLeftDir = 20;

//Initializing Stepper Motors
//Stepper stepperRight(stepsPerRevolution, 11, 12);
//Stepper stepperLeft(stepsPerRevolution, 20, 21);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;
  pinMode(stepperRight, OUTPUT);
  pinMode(stepperLeft, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // stepperRight.step(1);
  // stepperLeft.step(2);

  moveForward();
  delay(1);
}

void moveForward(){
  //digitalWrite(stepperRightDir, HIGH);
  digitalWrite(stepperLeftDir, HIGH);
  for(int i = 0; i < stepsPerRevolution; i++){
      digitalWrite(stepperRight, HIGH);
      digitalWrite(stepperLeft, HIGH);
      digitalWrite(stepperRight, LOW);
      digitalWrite(stepperLeft, LOW);
  }
  
}
