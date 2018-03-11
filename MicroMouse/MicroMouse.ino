////////////////////////////////////////
///////// Jerry the Micromouse /////////
////////////////////////////////////////

// Calling libraries
#include "Jerry.h"

// Constant Variables
#define STEPS 200 //Steps per revolution
const int max_distance = 6000; //Goes out to about 80cm. Since this reduces the amount of time spent until a pulse is recorded, it can essentially limit the distance it records
const int turn_angle = 50;  //Holds number or steps to swivel
int wallDistance = 10; //Threshold to determine if there is a wall or openings
int middleWallDistance = wallDistance + 2; //Threshold for middle sensor as it eats the wall, preventing a clean turn by allowing for extra clearance
String directions; //Stores directions
int stepCounter; //Tracks for the final goal
int goal_step_counter = 0; //Should be constantly at zero
char intersectionChoice; //Can either be (L)eft, (R)ight, (S)traight, or (U)turn
bool isIntersectionBoolean; //True if there is an intersection. If mouse can only turn left, right, or go back this counts as an intersection

//----------------------------------------------------------//
//------------------PIN INITIALIZATION----------------------//
//----------------------------------------------------------//

// Stepper Pins
// From left to right: Green black red blue 
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
int switch_value;  //Initializing switches 

// UltraSonic Sensor Pins
const int trigger1 = 0;
const int echo1 = 1;
const int trigger2 = 2;
const int echo2 = 3;
const int trigger3 = 18;
const int echo3 = 19;

// Instantiating bot motors
Jerry jerryBot(STEPS, motorLeft_1, motorLeft_2, motorLeft_3, motorLeft_4, motorRight_1, motorRight_2, motorRight_3, motorRight_4);
  

// Timer Initialization and associated variables
int left_distance;
int right_distance;
int middle_distance;

void setup(){
    jerryBot.initializeSensors( 10000, echo1, trigger1, echo2, trigger2, echo3, trigger3);
    //Initialize switches
    jerryBot.initializeSwitches(6, 7, 8, 9);
    // Default speed
    jerryBot.setSpeed(100);
    //start debug mode 
    jerryBot.setDebug(true);
}

//----------------------------------------------------------//
//------------------MAIN------------------------------------//
//----------------------------------------------------------//
void loop() {
    //Constantly reading switch values
    switch_value = jerryBot.readSwitches();
    //Constantly read and save distances
    middle_distance = jerryBot.getMiddleDistance();
    Serial.println(middle_distance);
    //Switch case statements
    switch (switch_value) {
      case B0000: //Machine will not do anything
        Serial.println("Awaiting instruction");
        break;
      case B0001: //Machine will start solving maze
        if(middle_distance < 10){ //Begins to solve by waving hand in front
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

//INPUT: Turn
//OUTPUT: None
//
void makeTurn(String turn){
  Serial.println("Turned: " + turn);
  directions.concat(turn);
  optimize(directions);
  
  stepCounter+=50;
  if ( ! directions.endsWith("R")){
    stepCounter = 0;
  }
  
  Serial.println("Optimized Directions: " + directions);
  Serial.println(stepCounter);
//  isGoal(directions,stepCounter); //FIXME: Should probably go outside of scope
  Serial.println();
}

//------Debug functions---------------------//
void recall(String &directions) {
  for (int i = 0; i <= directions.length(); i++) {
    Serial.print(directions[i]);
  }
}


//-------Algorithm Functions----------------//
//INPUT: Directions and stepper count by reference
//OUTPUT: Returns boolean value if mouse is at the endpoint
//Notes: Tracks by steps instead of time for consistency regardless of speed. This also prevents 
//       the program from being "taken over"
bool isGoal(String &directions, int &stepCount){
  if ( directions.endsWith("RRR") & (stepCount <= 150) ){
    Serial.println("Found Goal");
    return true;
  }
  return false;
}


//INPUT: None
//Output: Boolean - Lets mouse know when there is an intersection
//Use: When solving maze with optimized path, mouse can just turn based on directions whenever there is an intersection
bool isIntersection(){
  //Printing distances for debugging purposes
  Serial.println(left_distance);
  Serial.println(right_distance);
  Serial.println(middle_distance);
    if ( ( (middle_distance > middleWallDistance) and (left_distance > wallDistance) ) or ( (middle_distance > middleWallDistance) and (right_distance > wallDistance) ) ){ //If opening left and forward or right and forward
      //FIXME: IS this one even necessary since it will turn left regardless of if there is an opening in front? I forgot, it seemed like a good idea at the time. Probably best to keep it just because
      return true;
    }

    if( left_distance < wallDistance and right_distance < wallDistance and middle_distance < middleWallDistance ){ //If at a dead end
      return true;
    }
    if( left_distance > wallDistance ) { //Opening to the left
      return true;
    }
    if( right_distance > wallDistance ) { //Opening to the right
      return true;
    }
    
    return false; //Automatically assumes there is no intersection and will travel in a straight line
    
}

//Input: None
//Output: Returns a char based on sensors
//NOTE: DOES NOT append paths to array, just check and turn. We don't want it to append anything otherwise solveOptimized() would constantly add letters
char intersectionDecision() {
  //Using waterfall princniple of control flow statements. Priority: Left, straight, right, turn around
  if (left_distance > wallDistance) {
    return 'L';
  }
  else if (middle_distance > middleWallDistance) {
    return 'S';
  }
  else if (right_distance > wallDistance) {
    return 'R';
  }
  else if  ((left_distance < wallDistance) and (middle_distance < middleWallDistance) and (right_distance < wallDistance)) {
    return 'U';
  }
}



//INPUT: String directions - so that it can modify the directions as it goes
//OUTPUT: None
//Purpose: Function solves the maze using left hand rule
void solveMaze() {
  while (goal_step_counter < 150){ //Keep solving maze until we have found the goal
    //Update Distance Values
    middle_distance = jerryBot.getMiddleDistance();
    right_distance = jerryBot.getRightDistance();
    left_distance = jerryBot.getLeftDistance();
    isIntersectionBoolean = isIntersection();
    Serial.println("At intersection: ");
    Serial.println(isIntersectionBoolean);
    if(isIntersectionBoolean){ //If we are at an intersection
      intersectionChoice = intersectionDecision(); //Get decision to turn
      Serial.println(intersectionChoice);
      if (intersectionChoice == 'L') {
        jerryBot.moveForward(100); //Was 105
        jerryBot.turnLeft();
        directions.concat('L');
        delay(1000);
      }
      //If sensors  can move forward, but cannot move left, continue going forward and add "S" to directions. It is important to add "S" here.
      else if (intersectionChoice == 'S') {
        jerryBot.moveForward(200);
        directions.concat('S');
        delay(1000);
      }
      //If motor can only turn right, then turn right and record it.
      else if (intersectionChoice == 'R') {
        jerryBot.turnRight();
        jerryBot.moveForward(105);
        directions.concat('R');
        delay(1000);

      }
      //If motor can only make a u-turn, do so and record it.
      else if (intersectionChoice == 'U') {
      jerryBot.turnAround();
      directions.concat('U');
      delay(1000);
      }
      
//      //Mouse should constantly be going forward unless sensors let mouse know it can turn. It is important to never add a direction unless at an intersection
//      else{
//        jerryBot.moveForward(5); //Will step regardless if sensor is tripped or not
//        Serial.println("CONTINUE");
//        if ( (left_distance > wallDistance) or (right_distance > wallDistance) ){
//          goal_step_counter++;
//          Serial.println("Opening in left or right");
//        } 
//        else{
//          goal_step_counter = 0;
//          Serial.println("No right or left opening");
//        }
//      }
      optimizePath(directions); //Constantly optimize path after ever intersection
      }
      isIntersectionBoolean = false;
      jerryBot.moveForward(50);
      
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
    //Note: don't need to make a function to go back as u-turns will be cut out
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

//INPUT: Accepts a string of directions by reference
//OUTPUT: None
//Updates directions with shortcuts
void optimize(String &directions) {
    String longer[10] = {"LUR","LUS","LUL","RUL","SUL","SUS"};
    String shorter[10] = {"U","R","S","U","R","U"};
    for (int count = 0; count <= sizeof(longer); count++){
      if (directions.endsWith(longer[count])){
        directions.replace(longer[count],shorter[count]);
      }
    }
}


