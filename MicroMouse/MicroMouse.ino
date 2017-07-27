//FIXME GLOBAL: Should we loop pulse functions and set to a variable and just pass them into a function? Otherwise program might have a hard time as sensors might not be able to keep up. Unsure.
//Biggest reason: maintain consistency in times, also, might send script to a function that keeps it in a loop

#include <Stepper.h>

// Constant Variables
#define STEPS 200 //Steps per revolution
const int max_distance = 6000; //Goes out to about 80cm. Since this reduces the amount of time spent until a pulse is recorded, it can essentially limit the distance it records
double duration;
int distance;
const int turn_angle = 50;
int stepCount = 0; //Record number of steps taken to determine if goal is reached
int wallDistance = 5; //Threshold to determine if there is a wall or opening
char directions[200]; //Store directions

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

//Instantiating motors and switches
Stepper motorLeft(STEPS, motorLeft_1, motorLeft_2, motorLeft_3, motorLeft_4);
Stepper motorRight(STEPS, motorRight_1, motorRight_2, motorRight_3, motorRight_4);
int switch_value;  //Initializing switches 

//Assigning inputs and outputs
void setup() {
  	//3 sensors' pin assignment
	pinMode(trigger1, OUTPUT);
	pinMode(echo1, INPUT);
	pinMode(trigger2, OUTPUT);
	pinMode(echo2, INPUT);
	pinMode(trigger3, OUTPUT);
	pinMode(echo3, INPUT);
  	//2 motors' pin assignment
	pinMode(motorLeft_1, OUTPUT);
	pinMode(motorLeft_2, OUTPUT);
	pinMode(motorLeft_3, OUTPUT);
	pinMode(motorLeft_4, OUTPUT);
	pinMode(motorRight_1, OUTPUT);
	pinMode(motorRight_1, OUTPUT);
	pinMode(motorRight_1, OUTPUT);
	pinMode(motorRight_1, OUTPUT);
  	//Four switches' pin assignment
    for(int i = 6; i < 10; i++){
      pinMode(i, INPUT);
    }
  	//Begin serial communication
	Serial.begin(9600);
}

void loop() {
  	//Constantly reading switch values
    switch_value = readSwitches();
  	//Switch case statements
    switch (switch_value) {
      case B0000: //Machine will not do anything
      	leftMotorOff();
      	rightMotorOff();
        Serial.println("Awaiting instruction");
        break;
      case B0001: //Machine will start solving maze
        delay(1000); //Add delay to have mouse wait a second after we flip switch
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
        //	  motorLeft.speed(300);
        //	  motorRight.speed(300);
        //	  solveOptimized(); //FIXME: Compilation error; was not declared in ths scope
        //	  //return motors to normal speed.
        //	  motorLeft.speed(150);
        //	  motorRight.speed(150);
        break;
    }
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

//---------------------Movement Functions-------------------------------------------------
//Care has to be taken with the speed
//Motors use approximately 1A each at 100 rpm and .5A at 200 rpm
//150rpm is a good balance of speed and torque

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
void turnLeft(int turn_angle){
  for(int i = 0; i < turn_angle; i++){
    motorRight.step(1);
  }
}

//Move the robot right and goes forward
//Inputs: int - Number of steps
//Outputs: None
void turnRight(int steps){
  for(int i = 0; i < steps; i++){
    motorLeft.step(1);
  }
}

//------------Switch function--------------//
//Constantly reading value of switches
//INPUTS: NONE
//OUTPUT: Returns the value of switches from 0-15
int readSwitches() {
  switches = 0; //Must constantly reset switch count, otherwise it reaches rediculously large numbers //FIXME: Compilation error: 'switches' was not declared in this scope
  for (int i = 0; i < 4; i++) {
    pinMode(switchPins[i], INPUT);
    switches += (int) digitalRead(switchPins[i]) * (int) pow(2, i) ;
  }
  return switches;
  }
  
//-------Algorithm Functions----------------//

//INPUT: None
//OUTPUT: None
//Purpose: Function solves the maze using left hand rule
void solveMaze() {
  int counter = 0;
  char next_direction = checkIntersection();
  while ( !foundGoal() ){ //Keep trying to solve the maze until we have found the goal
    
    //If sensors say it can turn left, turn left and add "L" to the directions
    if (next_direction = 'L') {
      counter++;
      turnLeft();
      directions[counter] = 'L';
    }
    //If sensors  can move forward, but cannot move left, continue going forward and add "S" to directions. It is important to add "S" here.
    else if (next_direction = 'S') {
      counter++;
      moveforward();
      directions[counter] = 'S';
    }
    //If motor can only turn right, then turn right and record it.
    else if (next_direction = 'R') {
      counter++;
      turnRight();
      directions[counter] = 'R';
    }
    //If motor can only make a u-turn, do so and record it.
    else if (next_direction = 'B') {
      counter++;
      backward();
      directions[counter] =  'B';
    }
    //Mouse should constantly be going forward unless sensors let mouse know it can turn. It is important to never add a direction unless at an intersection
    else{
      moveForward();
    }
    moveForward();  //FIXME: Why should it be moving forward 
    optimizePath() //Constantly optimize path after ever intersection
  }
}

//FIXME: Ricardo please add explanation amd move under sensor functions if necessary
void checkDistance(){
  int middle_distance = pingMiddle();
  int move = middle_distance/.108;
}
//INPUT: array of characters
//OUTPUT: None
//Solves maze given the optimized code
void solveOptimized(directions) {
  	//If mouse can move left, turn left
    if (checkIntersection() = 'L') {
      turnLeft();
    }
    //If sensors  can move forward, but cannot move left, continue going forward and add "S" to directions. It is important to add "S" here.
    else if (checkIntersection() = 'S') {
      forward();
    }
    //If motor can only turn right, then turn right and record it.
    else if (checkIntersection() = 'R') {
      turnRight();
    }
    //If motor can only make a u-turn, do so and record it.
    else if (checkIntersection() = 'B') {
      backward();
    }
    //Mouse should constantly be going forward unless sensors let mouse know it can turn. It is important to never add a direction unless at an intersection
    else{
      forward();
}

void optimizePath(directions) {
  char opt_directions[100];
  int initializer = 0;
  String shortcuts[10] = {"LBR", "LBS", "RBL", "SBL", "SBS", "LBL"}; //Notice how all the optimizations have "B" in the middle
  for (shortcuts[i]; shortcuts[i] <= 11; i++) {
    if (i in directions) {
      //FIXME: replace these shortcuts
      //LBR = B
      //LBS = R
      //LBL = S
      //RBL = B
      //SBL = R
      //SBS = B
    }
  }
  int count = 0;
  for(int j = 0; j < directions.size(); j += 3){
    for(int k = j; k < (j+2); k++){
    	if(directions[k] == shortcuts
    }
  }
  for(int j = 0; j < directions.size(); j += 3){
    if(!((j + 2) > directions.size())){
      if(directions[j] == 'L'){
        if(directions[j +2] == 'R'){
        	opt_directions[initializer] = 'B';
        }
        else if(directions[j +2] == 'S'){
        	opt_directions[initializer] = 'R';
        }
        else if(directions[j +2] == 'L'){
        	opt_directions[initializer] = 'S';
        }
    	}
      else if(directions[j] == 'R'){
        if(directions[j+2] == 'L'){
        	opt_directionsp[initializer] = 'B'
        }
      }
    }
  }
}

//INPUT: None
//OUTPUT: Returns boolean value if mouse is at the endpoint
//FIXME: NOTE: By request, random end goal peg can be removed. Therefore we can do the technique where if it detects a larger than normal opening for an extended period of time, return true. Also please check logic
bool foundGoal() {}
	int timeCounter = 0; //FIXME: should this be global?
    //If there is a larger than normal distance, increase time counter
    if (pulseLeft() > wallDistance) or (pulseRight() > wallDistance){
  		timeCounter++;
    }
    //If there is no longer a larger than normal distance, reset counter to 0
    else{
    	timeCounter = 0;
    }  	
    //if L, L, L, or {R, R, R in directions, AND within a certain timeframe //FIXME: For now, keeping this option in case of rejection, would have to create 9+ case statements
    //If timeCounter reaches a certain threshold, then return true as it found the goal
  	if (timeCounter >100){ //FIXME: Subject to change
    	return true;
    }

}

//Input: None
//Output: Returns a char based on sensors
//NOTE: DOES NOT append paths to array, just check and turn. We don't want it to append anything otherwise solveOptimized() would constantly add letters
char checkIntersection() {
  if (pulseLeft() > wallDistance) {
    return 'L';
  }
  else if (pulseMiddle() > wallDistance) {
    return 'S';
  }
  else if (pulseRight() > wallDistance) {
    return 'R';
  }
  else if (pulseLeft() > wallDistance) and (pulseMiddle() > wallDistance) and (pulseRight() > wallDistance) {
    return 'B';
  }
}