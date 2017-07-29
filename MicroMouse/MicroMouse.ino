////////////////////////////////////////
///////// Jerry the Micromouse /////////
////////////////////////////////////////

// Calling libraries
#include "Jerry/Jerry.h"
#include <elapsedMillis.h>

// Constant Variables
#define STEPS 200 //Steps per revolution
const int max_distance = 6000; //Goes out to about 80cm. Since this reduces the amount of time spent until a pulse is recorded, it can essentially limit the distance it records
double duration;
int distance;
const int turn_angle = 50;
int wallDistance = 10; //Threshold to determine if there is a wall or openingS
String directions; //Stores directions
int goal_step_counter = 0; //Should be constantly at zero
char intersectionChoice;
bool isIntersectionBoolean;
// From left to right: Green black red blue 
// Stepper Pins
const int motorLeft_1 = 15;
const int motorLeft_2 = 21;
const int motorLeft_3 = 14;
const int motorLeft_4 = 10;
const int motorRight_1 = 17;
const int motorRight_2 = 20;
const int motorRight_3 = 16;
const int motorRight_4 = 11;

// Switch pins
int switchPins[4] = {6, 7, 8 , 9}; //Declaring pins for the switches

// UltraSonic Sensor Pins
const int trigger1 = 0;
const int echo1 = 1;
const int trigger2 = 2;
const int echo2 = 3;
const int trigger3 = 4;
const int echo3 = 5;

// Instantiating bot motors
Jerry jerryBot(STEPS, motorLeft_1, motorLeft_2, motorLeft_3, motorLeft_4, motorRight_1, motorRight_2, motorRight_3, motorRight_4);
  
int switch_value;  //Initializing switches 

// Timer Initialization and associated variables
IntervalTimer checkDistances;
volatile int volatile_left_distance;
volatile int volatile_right_distance;
volatile int volatile_middle_distance;
int left_distance;
int right_distance;
int middle_distance;
volatile int current_sensor;

void setup() {
    jerryBot.initializeSensors( 10000, echo1, trigger1, echo2, trigger2, echo3, trigger3);
    //3 sensors' pin assignment
    pinMode(trigger1, OUTPUT);
    pinMode(echo1, INPUT);
    pinMode(trigger2, OUTPUT);
    pinMode(echo2, INPUT);
    pinMode(trigger3, OUTPUT);
    pinMode(echo3, INPUT);
  	//Initialize switches
	jerryBot.initializeSwitches(6, 7, 8, 9);

    // Default speed
    jerryBot.setSpeed(100);
  	//start debug mode 
	jerryBot.setDebug(true);
}

void loop() {
    //Constantly reading switch values
    switch_value = jerryBot.readSwitches();
    //Constantly read and save distances
    noInterrupts();
    middle_distance = volatile_middle_distance;
    Serial.println(middle_distance);
    right_distance = volatile_right_distance;
    left_distance = volatile_left_distance;
    interrupts();
    //Switch case statements
    switch (switch_value) {
      case B0000: //Machine will not do anything
        Serial.println("Awaiting instruction");
        break;
      case B0001: //Machine will start solving maze
        if(middle_distance < 10){
          delay(1500);
          Serial.println("Solving maze");
          solveMaze();
        }
        break;
        
        
      case B0010: //Machine will solve maze with the optimized path
        delay(1000);
        Serial.println("Optimized solving maze");
        solveOptimized(directions);
        break;
      case B0100:
        Serial.println("Optimized solving maze at double speed");
        //    motorLeft.speed(300);
        //    motorRight.speed(300);
        //    solveOptimized(); //FIXME: Compilation error; was not declared in ths scope
        //    //return motors to normal speed.
        //    motorLeft.speed(150);
        //    motorRight.speed(150);
        break;
    }
}

//----------------------------------------------------------//
//------------------FUNCTIONS-------------------------------//
//----------------------------------------------------------//


//-------------Sensor Functions----------------------------

//
void pingDistances(void) {
  if( current_sensor == 0){
    volatile_right_distance = pulseRight();
    current_sensor++;
  }
  else if(current_sensor == 1){
    volatile_middle_distance = pulseMiddle();
    current_sensor++;
  }
  else if(current_sensor == 2){
    volatile_left_distance = pulseLeft();
    current_sensor = 0;
  }
}



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

  //Serial.print("Right distance: "); Serial.println(distance);
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
  
  ///Serial.print("Left distance: "); Serial.println(distance);
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

  //Serial.print("Middle distance: "); Serial.println(distance);
  return distance;
}



//------Debug functions---------------------//
void recall(String directions) {
  for (int i = 0; i <= (int) directions.length(); i++) {
    Serial.println(directions[i]);
  }
}

//-------Algorithm Functions----------------//
//INPUT: None
//OUTPUT: Returns boolean value if mouse is at the endpoint
//FIXME: NOTE: By request, random end goal peg can be removed. Therefore we can do the technique where if it detects a larger than normal opening for an extended period of time, return true. Also please check logic
bool isGoal() {
    int milli = elapsedMillis();
    //If there is a larger than normal distance, return true
    if ( ((left_distance > wallDistance) or (right_distance > wallDistance)) and milli > 3000 ){
      return true;
    }
  return false;
}

//Input: None
//Output: Returns a char based on sensors
//NOTE: DOES NOT append paths to array, just check and turn. We don't want it to append anything otherwise solveOptimized() would constantly add letters
char intersectionDecision() {
  if (left_distance > wallDistance) {
    return 'L';
  }
  else if (middle_distance > wallDistance) {
    return 'S';
  }
  else if (right_distance > wallDistance) {
    return 'R';
  }
  else  {
    return 'U';
  }
}

//INPUT: None
//Output: Boolean - Lets mouse know when there is an intersection
//Use: When solving maze with optimized path, mouse can just turn based on directions whenever there is an intersection
bool isIntersection(){
  Serial.println(left_distance);
  Serial.println(right_distance);
  Serial.println(middle_distance);
    if ( ( (middle_distance > wallDistance) and (left_distance > wallDistance) ) or ( (middle_distance > wallDistance) and (right_distance > wallDistance) ) ){
      return true;
    }

    if( left_distance < wallDistance and right_distance < wallDistance and middle_distance < wallDistance ){
      return true;
    }
    if( left_distance > wallDistance ) {
      return true;
    }
    if( right_distance > wallDistance ) {
      return true;
    }
    
    return false;
    
}


//INPUT: String directions - so that it can modify the directions as it goes
//OUTPUT: None
//Purpose: Function solves the maze using left hand rule
void solveMaze() {
  while (goal_step_counter < 150){ //Keep solving maze until we have found the goal
    //Update Distance Values
    noInterrupts();
    middle_distance = volatile_middle_distance;
    right_distance = volatile_right_distance;
    left_distance = volatile_left_distance;
    interrupts();
    isIntersectionBoolean = isIntersection();
    Serial.println(isIntersectionBoolean);
    if(isIntersectionBoolean){
      intersectionChoice = intersectionDecision();
      Serial.println(intersectionChoice);
      if (intersectionChoice == 'L') {
        jerryBot.moveForward(105);
        jerryBot.turnLeft();
        directions.concat('L');

      
      }
      //If sensors  can move forward, but cannot move left, continue going forward and add "S" to directions. It is important to add "S" here.
      else if (intersectionChoice == 'S') {
        jerryBot.moveForward(170);
        directions.concat('S');

      }
      //If motor can only turn right, then turn right and record it.
      else if (intersectionChoice == 'R') {
        jerryBot.turnRight();
        jerryBot.moveForward(105);
        directions.concat('R');

      }
      //If motor can only make a u-turn, do so and record it.
      else if (intersectionChoice == 'U') {
      jerryBot.turnAround();
      delay(200);
      directions.concat('U');

      }
      //Mouse should constantly be going forward unless sensors let mouse know it can turn. It is important to never add a direction unless at an intersection
      else{
        //jerryBot.moveForward(5); //Will step regardless if sensor is tripped or not
        Serial.println("ElSE continue straight");
        if ( (left_distance > wallDistance) or (right_distance > wallDistance) ){
          goal_step_counter++;
          Serial.println("Opening in left or right");
        } 
        else{
          goal_step_counter = 0;
          Serial.println("No right or left opening");
        }
      }
      optimizePath(directions); //Constantly optimize path after ever intersection
      }
      isIntersectionBoolean = false;
      jerryBot.moveForward(10);
      delay(200);
      
    }
    
}


//INPUT: array of characters
//OUTPUT: None
//Solves maze given the optimized code
void solveOptimized(String directions) {
  int directionsCounter = 0;
  char turn;
  if (isIntersection()){
    turn = directions[directionsCounter];
    //Note: don't need to make a function to go back
    if (turn == 'L'){
      jerryBot.turnLeft();
    }
    else if (turn == 'S'){
      jerryBot.moveForward(200);
    }
    else if (turn == 'R'){
      jerryBot.turnRight();
    }
    directionsCounter++;
  }
  else{
    jerryBot.moveForward(5); //Shouldn't it be 100 so it doesn't jump mpast a potential intersection?
  }
}

//INPUT: Accepts a string of directions
//OUTPUT: String directions
//Updates directions with shortcutstodo1
String optimizePath(String directions) {
    String longer[6] = {"LUR","LUS","LUL","RUL","SUL","SUS"};
    String shorter[6] = {"U","R","S","U","R","U"};
    for (int count = 0; count < 6; count++){
      if (directions.endsWith(longer[count])){
        directions.replace(longer[count], shorter[count]);
      }
    }
  Serial.println(directions);
  return directions;
}


