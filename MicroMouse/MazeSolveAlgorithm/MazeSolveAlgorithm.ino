//An algorithm to solve a maze using the left hand rule and optimization.
//Will be implemented into main file
int switchPins[4] = {6, 7, 8 , 9}; //Declaring pins for the switches
int switches;  //Initializing switches
//initialize an array to hold the path traveled and set as empty
//setup an end integer, if the sensors have a reading of <10 cm, terminate the program and start optimization because we found the finish line

void setup() {
  Serial.begin(9600); //Initialize serial communication
}

void loop() {
  switches = 0; //Constantly resetting switches
  for (int i = 0; i < 4; i++){
    pinMode(switchPins[i], INPUT);
    switches += (int) digitalRead(switchPins[i]) * (int) pow(2, i) ;
  }
  switch (switches){
    case B0000: //Machine will be off
      Serial.println("Awaiting instruction");
      break;
    case B0001: //Machine will start solving maze
      Serial.println("Starting to solve maze.");
      break;
    case B0010: //Machine will solve maze with the optimized path
      Serial.println("Solving with optimized path.");
      break;
    case B0100:
      Serial.println("Solving with optimized path at double speed.");
      break;
  }
  delay(1); //Stability pause
}


void optimizePath(){
  //Execeutes after every move
//LBR = B
//LBS = R
//RBL = B
//SBL = R
//SBS = B
//LBL = S
}


void solveMaze(){
  //If there is no left opening:
      //Move forward
    // else if there is an opening:
      //Turn left
}

