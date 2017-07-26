//An algorithm to solve a maze using the left hand rule that optimizes a path
int switchPins[4] = {6, 7, 8 , 9}; //Declaring pins for the switches
int switches;  //Initializing switches
int stepCount = 0; //Record number of steps taken to determine if goal is reached
int wallDistance = 5; //Setting threshold to determine if there is a wall or opening

String directions;
void setup() {
  Serial.begin(9600); //Initialize serial communication
}

void loop() {
	readSwitches(); //Must constantly read switches to know what it must do
}


//-------------------Functions----------------------//

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
      Serial.println("Solving maze");
      solveMaze();
      break;
    case B0010: //Machine will solve maze with the optimized path
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
}
//INPUT: None
//OUTPUT: None
//Purpose: Function solves the maze using left hand rule
void solveMaze() {
  while foundGoal() = False{ //Keep trying to solve the maze until we have found the goal
    //If sensors say it can turn left, turn left and add "L" to the directions
    if (checkIntersection() = "L"){
      turnLeft();
      directions += "L";
		}
    //If sensors  can move forward, but cannot move left, continue going forward and add "S" to directions. It is important to add "S" here.
    else if (checkIntersection() = "S"){
      forward();
      directions += "S";
		}
    //If motor can only turn right, then turn right and record it.
    else if (checkIntersection() = "R"){
      turnRight();
      directions += "R";
	  }
    //If motor can only make a u-turn, do so and record it.
    else if (checkIntersection() = "B"){
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

void solveOptimized(directions){

  //Keep going forward, if at an intersection, do the upcoming element turn.
//	checkIntersection
}

void optimizePath(directions) {
  String shortcuts[10] = {"LBR","LBS","RBL","SBL","SBS","LBL"}; //Notice how all the optimizations have "B" in the middle
  for (shortcuts[i]; shortcuts[i] <= 11; i++){
    if (i in directions){
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


bool foundGoal(){}
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
String checkIntersection(){
  if (pulseLeft() > wallDistance){
    return "L";
  }
  else if (pulseMiddle() > wallDistance){
    return "S";
  }
  else if (pulseRight() > wallDistance){
    return "R";
  }
  else if (pulseLeft() > wallDistance) and (pulseMiddle() > wallDistance) and (pulseRight() > wallDistance){
    return "B";
  }
}
