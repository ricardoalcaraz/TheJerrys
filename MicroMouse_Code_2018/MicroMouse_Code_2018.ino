#include "Sensors.h"
#include "Motors.h"
#include <AutoPID.h>

Sensors sensors;
Motors motors;

String directions;
int stepCounter;
int incomingByte = 0;
const uint16_t CELL = 350;     // Clears block and some extra to be safe
const uint16_t CELLRESET = 200;   //Centers the robot 
const uint16_t TANKLEFT = 200;    // 90 degree turn left
const uint16_t TANKRIGHT = 200;   // 90 degree turn right
const uint16_t UTURN = 400;       // 180 degree turn
const uint16_t CLEARANCE = 200;       // 180 degree turn

double SETPOINT = 4;

//pid settings and gains
#define OUTPUT_MIN 0.5  // Suggested: 0.5
#define OUTPUT_MAX 10.0  // Suggested: 1.5
#define KP 2.0          // Suggested: 2.0
#define KI 0.000       // Suggested: .0002
#define KD 0          // Suggested: 1.5

double leftDistance, middleDistance, rightDistance, rightDrive, leftDrive;


//input/output variables passed by reference, so they are updated automatically
AutoPID leftDistancePID(&leftDistance, &SETPOINT, &rightDrive, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
AutoPID rightDistancePID(&rightDistance, &SETPOINT, &leftDrive, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

void setup() {
  Serial.begin( 57600 );
  motors.init();
  sensors.init();
  delay(1000);

  leftDistancePID.setTimeStep(1);
  rightDistancePID.setTimeStep(1);
}

void loop() {
    if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
      if (incomingByte == 'w') {
      }
      else if (incomingByte == 's'){
          motors.uTurn(UTURN);
      }
      else if (incomingByte == 'a'){
          motors.tankLeft(TANKLEFT);
      }
      else if (incomingByte == 'd'){
          motors.tankRight(TANKRIGHT);
      }
      else if (incomingByte == 'x'){
          motors.turnOff();
      }
      else if (incomingByte == 'q'){
          autoForward(CELL);
      }
    }
    delay(5);
/*
  char turn = getTurnt();
  if (turn > 0) {
    Serial.println(turn);
  }

  if (turn == 'L') {
    autoForward(300); // makes the robot ram into the wall for consistentcy -- Making a left turn into a path with no wall in front of it is currently impossible (big problem)
    motors.tankLeft(TANKLEFT);
  }
  else if (turn == 'S') {
    autoForward(380);
  }
  else if (turn == 'R') {
    autoForward(300); // makes the robot ram into the wall for consistentcy -- never need to turn right with no wall in front except during optimized path (small problem)
    motors.tankRight(TANKRIGHT);
  }
  else if (turn == 'U') {
    autoForward(300); // makes the robot ram into the wall for consistentcy -- there will always be a wall to crash into (no problem)
    motors.uTurn(UTURN);
  }
  else autoForward(390);

  delay(5); // increase this to go cell by cell
*/
}



char getTurn() {
  String debounce;
  //Get room
  //wall threshold based on distance to middle of next room
  unsigned int wallDistance = 15;

  for (int i = 0; i < 20; i++) {
    leftDistance = sensors.getLeftDistance();
    rightDistance = sensors.getRightDistance();
    middleDistance = sensors.getMiddleDistance();

    Serial.print(leftDistance); Serial.print("      "); Serial.print(middleDistance); Serial.print("       "); Serial.print("     "); Serial.println(rightDistance);

    String room = (String(leftDistance   < wallDistance) +
                   String(middleDistance < wallDistance) +
                   String(rightDistance  < wallDistance));
    //Decide turn based on left hand rule
    if      (room == "100") debounce +=  'S';
    else if (room == "101") debounce += NULL;
    else if (room == "110") debounce +=  'R';
    else if (room == "111") debounce +=  'U';
    else                    debounce +=  'L';
    delay(25); //FIXME: Helps to debounce and space signals out, but may stall PID forward
  }

  //Signal debouncing
  if      (debounce.indexOf("SSSSSSSSSSS") > 0) return 'S';
  else if (debounce.indexOf("RRRRRRRRRRR") > 0) return 'R';
  else if (debounce.indexOf("UUUUUUUUUUU") > 0) return 'U';
  else if (debounce.indexOf("LLLLLLLLLLL") > 0) return 'L';
  else return NULL;
}

//Input: None
//Output: Intersection turn decision
char getTurnt() {
  int wallDistance = 15;
  leftDistance = sensors.getLeftDistance();
  rightDistance = sensors.getRightDistance();
  middleDistance = sensors.getMiddleDistance();

  String room = (String(leftDistance   < wallDistance) +
                 String(middleDistance < wallDistance) +
                 String(rightDistance  < wallDistance));
  if      (room == "100") return 'S';
  else if (room == "101") return NULL;
  else if (room == "110") return 'R';
  else if (room == "111") return 'U';
  else                    return 'L';
}


//Input: None
//Output: Boolean representing if there is an intersection
bool isIntersection() {
  int wallThreshold = 15;
  if ( (sensors.getLeftDistance()   < wallThreshold) &&
       (sensors.getMiddleDistance() > wallThreshold) &&
       (sensors.getRightDistance()  < wallThreshold)
     ) return false;
  else  return true;
}


void autoForward(int STEPS) {
    double speed = 500;
    bool rst = (  (sensors.getLeftDistance() > 15) || (sensors.getRightDistance() > 15)  ) ? true : false;
    //Initialize if we started in an intersection
    //If entering a cell with a possible intersection, we want to callibrate it to go to the middle
    //If leaving a cell with a possible itnersection, just use the hardcoded full cell traversal
    bool leftIntersection = (  (sensors.getLeftDistance() > 15)  );
    bool rightIntersection = (  ( sensors.getRightDistance() > 15)  );
  
  for (int i = STEPS; i > 0; i -= 7) { //larger multiples than 1 since I tried stepping additional steps below
    leftDistance = sensors.getLeftDistance();
    rightDistance = sensors.getRightDistance();

    //call PID calculations every loop
    // If-else statements are attempting to prevent robot swerving left/right when reaching an intersection
    leftDistancePID.run();
    rightDistancePID.run();

    if (leftDistance < 15) {
      motors.rightForward(7, speed + rightDrive * 500);
      Serial.println("Took this path");
    }
    else {
      motors.rightForward(7, speed + 300);
       if (rst == false){ //Must have a one time trigger since distances are constantly returned
        rst = true;
        i = CELLRESET;
        Serial.println("No, Took this path");
      }
    }

    if (rightDistance < 15){
      motors.leftForward(7, speed + leftDrive * 500);
      Serial.println("fuck ya motha");
    }
    else {
      motors.leftForward(7, speed + 300);
      if (rst == false){ //Must have a one time trigger since distances are constantly returned
        rst = true;
        i = CELLRESET;
        Serial.println("shut up");
      }
    }
    /* rightDistancePID.run();
      leftDistancePID.run();

      motors.rightForward(7, speed + rightDrive*500);
      motors.leftForward(7, speed + leftDrive*500);*/

  }
}
//Serial.print(leftDistance); Serial.print("      ");Serial.print(leftDrive); Serial.print("     "); Serial.print(rightDistance); Serial.print("     ");Serial.println(rightDrive);



