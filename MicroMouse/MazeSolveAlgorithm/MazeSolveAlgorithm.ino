//An algorithm to solve a maze using the left hand rule that optimizes

int switchPins[4] = {6, 7, 8 , 9}; //Declaring pins for the switches
int switches;  //Initializing switches

String pathTraveled[i]; //FIXME: Does this work?? We will want to append letters to it.
String optimizedPath[i]; //FIXME: Make a separate path to travel so mouse can solve either short or long way
void setup() {
  Serial.begin(9600); //Initialize serial communication
}

void loop() {
  switches = readSwitches();
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
      break;
  }
  delay(1); //Stability pause
}

//Constantly reading value of switches and resetting to zero.
//INPUT: Four Switch pins
//Returns the value of switches from 0-15
int readSwitches() {
  switches = 0; //Must constantly reset switch count, otherwise it reaches rediculously large numbers
  for (int i = 0; i < 4; i++) {
    pinMode(switchPins[i], INPUT);
    switches += (int) digitalRead(switchPins[i]) * (int) pow(2, i) ;
    return switches;
  }
}

void solveMaze() {
  //If there is no left opening:
  //Move forward
  // else if there is an opening:
  //Turn left
}

void optimizePath() {
  //Execeutes after every move
  //LBR = B
  //LBS = R
  //RBL = B
  //SBL = R
  //SBS = B
  //LBL = S
}


bool foundGoal(){
  //check if sensors have large enough gap.
  //Move mouse forward
  //If one of the sensors hasn't change, we found the goal
    //Return True
  //else return false
}

