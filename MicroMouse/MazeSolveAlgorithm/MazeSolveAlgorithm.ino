//An algorithm to solve a maze using the left hand rule that optimizes a path
int switchPins[4] = {6, 7, 8 , 9}; //Declaring pins for the switches
int switches;  //Initializing switches

String pathTraveled[i]; //FIXME: Does this work?? We will want to append letters to it.
void setup() {
  Serial.begin(9600); //Initialize serial communication
}

void loop() {
	readSwitches(); //Must constantly read switches to know what it must do
}


//-------------------Functions----------------------//

//Constantly reading value of switches and resetting to zero.
//INPUT: Four Switch pins
//Returns the value of switches from 0-15
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
      break;
    case B0100:
      Serial.println("Optimized solving maze at double speed");
	  motor1.speed(300);
	  motor2.speed(300);
	  solveMaze();
	  //return motors to normal speed.
	  motor1.speed(150);
	  motor2.speed(150); 
      break;
  }
  delay(10); //Stability pause
}

void solveMaze() {
	foundGoal = False;
	while foundGoal = False; //Keep trying to solve the maze until we have found the goal
		if checkIntersection() = "L";
			turnLeft();
			//pathTraveled.append("L");
		else if checkIntersection() = "S"
			forward();
			//pathtraveled.append("S");
		else if checkIntersection() = "R"
			turnRight();
			//pathTraveled.append("R");
		else if checkIntersection() = "B"
			backward();
			//pathTraveled.append("B");
		else //Constanty travel forward until sensors detect a sensor
			forward(); //Does not count as a 'step' in path
		optimizePath() //Constantly optimize path after ever intersection
}

void solveOptimized(optimizedpath){
	checkIntersection
}

void optimizePath() {
	//Execeutes after every move, should be in solveMaze()
	//LBR = B
	//LBS = R
	//RBL = B
	//SBL = R
	//SBS = B
	//LBL = S
	//if any of these are in pathtraveled:
		//replace the 3 letters with shorter letter

}


bool foundGoal(){
  //Read sensor
  //if either left or right sensor has a reading greater than 10cm for more than 1ms, (subject to change and experimentation),
	  //turn off motors 1 and 2 to stop moving
	  //return true

}

//DOES NOT append paths to array, just check and turn
String checkIntersection(){
	//Reads sensors
	//If left sensor is open:
		// turnLeft(); Add "L" to path
	//else if front sensor is open:
		// forward() and add "S" to path
	// else if right sensor is open:
		// turnRight() and add "R" to path array

