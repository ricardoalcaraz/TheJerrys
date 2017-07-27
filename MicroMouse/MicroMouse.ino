#include <Stepper.h>

// Constant Variables
#define STEPS 200 //Steps per revolution
const int max_distance = 6000; //Goes out to about 80cm. Since this reduces the amount of time spent until a pulse is recorded, it can essentially limit the distance it records
double duration;
int distance;
int steps = 50; //number of steps per incrementation
int stepCount = 0; //Record number of steps taken to determine if goal is reached
int wallDistance = 5; //Threshold to determine if there is a wall or opening
String directions; //Store directions

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

//Switch pins
int switchPins[4] = {6, 7, 8 , 9}; //Declaring pins for the switches

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

//Instantiating motors and switches
Stepper motorLeft(STEPS, motorLeft_1, motorLeft_2, motorLeft_3, motorLeft_4);
Stepper motorRight(STEPS, motorRight_1, motorRight_2, motorRight_3, motorRight_4);
int switches;  //Initializing switches 

void setup() {
	//Assigning inputs and outputs
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
    readSwitches(); //Must constantly read switches to know what it must do
  
}

//----------------------------------------------------------//
//------------------FUNCTIONS-------------------------------//
//----------------------------------------------------------//


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

<<<<<<< HEAD
//Pivot robot right
=======
//---------------------Movement Functions-------------------------------------------------
//Care has to be taken with the speed
//Motors use approximately 1A each at 100 rpm and .5A at 200 rpm
//150rpm is a good balance of speed and torque




//Move the robot right and goes forward
>>>>>>> 2ecad0e8a469cd68e0c2d67039137b5cb7c1ce3d
//Inputs: int - Number of steps
//Outputs: None
void turnRight(int steps){
  for(int i = 0; i < steps; i++){
    motorLeft.step(1);
  }
}

//------------Switch function--------------//
//Constantly reading value of switches and resetting to zero.
//INPUT: Four Switch pins
//OUTPUT: Returns the value of switches from 0-15
void readSwitches() {
  switches = 0; //Must constantly reset switch count, otherwise it reaches rediculously large numbers
  for (int i = 0; i < 4; i++) {
    pinMode(switchPins[i], INPUT);
    switches += (int) digitalRead(switchPins[i]) * (int) pow(2, i) ;
  }
  switch (switches) {
    case B0000: //Machine will not do anything
      Serial.println("Awaiting instruction");
      break;
    case B0001: //Machine will start solving maze
      delay(1000); //Add delay to have mouse wait a second after we flipl switch
      Serial.println("Solving maze");
      solveMaze();
      break;
    case B0010: //Machine will solve maze with the optimized path
      delay(1000);
      Serial.println("Optimized solving maze");
      solveOptimized();
      break;
    case B0100:
      Serial.println("Optimized solving maze at double speed");
      //	  motor1.speed(300);
      //	  motor2.speed(300);
      //	  solveOptimized();
      //	  //return motors to normal speed.
      //	  motor1.speed(150);
      //	  motor2.speed(150);
      break;
  }
  delay(10); //Stability pause
  
//-------Algorithm Functions----------------//

//INPUT: None
//OUTPUT: None
//Purpose: Function solves the maze using left hand rule
void solveMaze() {
  while foundGoal() = False{ //Keep trying to solve the maze until we have found the goal
    //If sensors say it can turn left, turn left and add "L" to the directions
    if (checkIntersection() = "L") {
      turnLeft();
      directions += "L";
    }
    //If sensors  can move forward, but cannot move left, continue going forward and add "S" to directions. It is important to add "S" here.
    else if (checkIntersection() = "S") {
      forward();
      directions += "S";
    }
    //If motor can only turn right, then turn right and record it.
    else if (checkIntersection() = "R") {
      turnRight();
      directions += "R";
    }
    //If motor can only make a u-turn, do so and record it.
    else if (checkIntersection() = "B") {
      backward();
      directions += "B";
    }
    //Mouse should constantly be going forward unless sensors let mouse know it can turn. It is important to never add a direction unless at an intersection
    else{
      forward();
    }
    optimizePath() //Constantly optimize path after ever intersection
  }
}

void solveOptimized(directions) {
  //FIXME: Write code,
  //Keep going forward, if at an intersection, do the upcoming element turn.
  //	checkIntersection
}

void optimizePath(directions) {
  String shortcuts[10] = {"LBR", "LBS", "RBL", "SBL", "SBS", "LBL"}; //Notice how all the optimizations have "B" in the middle
  for (shortcuts[i]; shortcuts[i] <= 11; i++) {
    if (i in directions) {
      //FIXME: replace these shrotcuts
      //LBR = B
      //LBS = R
      //RBL = B
      //SBL = R
      //SBS = B
      //LBL = S
    }
  }
}


bool foundGoal() {}
stepCount = 0; //Constantly resetting the stepper counter
//FIXME: if either sensor reading on left or right is greater than normal AND stepCount reaches something like 500 steps, then turn off motors to kill engine
//FIXME: Add steps to stepCount in forward();
//motor1.turnOff();
//motor2.turnOff();
//return true
}

//Input: None
//Output: Returns a letter given sensors
//DOES NOT append paths to array, just check and turn. We don't want it to append anything otherwise solveOptimized() would constantly add letters
String checkIntersection() {
  if (pulseLeft() > wallDistance) {
    return "L";
  }
  else if (pulseMiddle() > wallDistance) {
    return "S";
  }
  else if (pulseRight() > wallDistance) {
    return "R";
  }
  else if (pulseLeft() > wallDistance) and (pulseMiddle() > wallDistance) and (pulseRight() > wallDistance) {
    return "B";
  }
}