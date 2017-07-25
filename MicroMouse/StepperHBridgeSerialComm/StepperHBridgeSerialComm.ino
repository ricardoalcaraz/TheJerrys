//Controlled via inputting steps into serial
#include <Stepper.h> //gets library
//declaring pints
int in1Pin = 21;
int in2Pin = 14;
int in3Pin = 15;
int in4Pin = 10;

#define STEPS 200 //must be define, not int. Number based on how many increments per single revolution
 
Stepper motor(STEPS, in1Pin, in2Pin, in3Pin, in4Pin); 
 
void setup()
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
 
  while (!Serial);   
  Serial.begin(9600);
  motor.setSpeed(20);
}
 
void loop()
{
  motorOff();
  if (Serial.available())
  {
    int steps = Serial.parseInt();
    if (steps == 1){
      motorOn();
      turnLeft();
    }
    else if (steps == 3){
      motorOn();
      turnRight();
    }
    else{
    }
  }
}


void turnLeft(){
  motor.step(-100);
}
void turnRight(){
  motor.step(100);
}

void motorOn(){
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, HIGH);
    digitalWrite(in3Pin, HIGH);
    digitalWrite(in4Pin, HIGH);  
}

void motorOff(){
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    digitalWrite(in3Pin, LOW);
    digitalWrite(in4Pin, LOW);    
}

