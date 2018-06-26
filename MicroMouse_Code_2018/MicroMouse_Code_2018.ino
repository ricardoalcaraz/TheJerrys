#include "Sensors.h"
#include "Motors.h"
#include <AutoPID.h>
#include "A4988.h"

#define MOTOR_STEPS 200
#define LEFT_DIR 7
#define RIGHT_DIR 6
#define LEFT_STEP 5
#define RIGHT_STEP 4
#define LEFT_ENABLE 21
#define RIGHT_ENABLE 20


Sensors sensors;
Motors motors;
A4988 leftStepper( 250, LEFT_DIR, LEFT_STEP, LEFT_ENABLE );
A4988 rightStepper( 250, RIGHT_DIR, RIGHT_STEP, RIGHT_ENABLE );

String directions;
int stepCounter;
int incomingByte = 0;

const uint16_t CELL = 350;     // Clears block and some extra to be safe
const uint16_t CELLRESET = 200;   //Centers the robot
const uint16_t TANKLEFT = 200;    // 90 degree turn left
const uint16_t TANKRIGHT = 200;   // 90 degree turn right
const uint16_t UTURN = 450;       // 180 degree turn
const uint16_t CLEARANCE = 200;       // 180 degree turn

double SETPOINT = 2.33;

//pid settings and gains
#define OUTPUT_MIN 0.0  // Suggested: 0.0
#define OUTPUT_MAX 2.0  // Suggested: 2.0
#define KP 1.25         // Suggested: 1.25
#define KI 0.001       // Suggested: .001
#define KD 2.0          // Suggested: 2.0
#define ROTATE 0.75 // Suggested 0.75

double leftDistance, middleDistance, rightDistance, rightDrive, leftDrive;


//input/output variables passed by reference, so they are updated automatically
AutoPID leftDistancePID(&leftDistance, &SETPOINT, &rightDrive, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
AutoPID rightDistancePID(&rightDistance, &SETPOINT, &leftDrive, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

void setup() {
  Serial.begin( 57600 );
  //motors.init();
  sensors.init( 50000 );
  delay(1000);
  leftStepper.begin(10, 4);
  rightStepper.begin(10, 4);
  leftDistancePID.setTimeStep(1);
  rightDistancePID.setTimeStep(1);
}

void loop() {
  for (int i = 0; i < 999; i++){
    
      rightDistance = sensors.getRightDistance();
      leftDistance = sensors.getLeftDistance();
      middleDistance = sensors.getMiddleDistance();
      if (middleDistance < 3){
        motors.uTurn(UTURN);
      }
      else{
        autoForward(200, leftDistance, rightDistance, middleDistance);
      }
  }
    /*
    if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
      if (incomingByte == 'w') {
      }
      else if (incomingByte == 's'){
          motors.uTurn(UTURN);
      }
    }
    */
}



//Input: None
//Output: Intersection turn decision
char getTurn() {
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
  if ( (leftDistance   < wallThreshold) &&
       (middleDistance > wallThreshold) &&
       (rightDistance  < wallThreshold)
     ) return false;
  else return true;
}


void autoForward(int STEPS, int rightDistance, int leftDistance, int middleDistance) {
    motors.turnOn();
    noInterrupts();
    bool rst = (  (leftDistance > 15) || (rightDistance > 15)  ) ? true : false;
    //Initialize if we started in an intersection
    //If entering a cell with a possible intersection, we want to callibrate it to go to the middle
    //If leaving a cell with a possible itnersection, just use the hardcoded full cell traversal
    bool leftIntersection = (  leftDistance > 15 );
    bool rightIntersection = (  rightDistance > 15 );

    //call PID calculations every loop
    // If-else statements are attempting to prevent robot swerving left/right when reaching an intersection
    leftDistancePID.run();
    rightDistancePID.run();
    for(int i = 0; i < 2; i++){
      rightStepper.rotate(ROTATE+leftDrive);
      leftStepper.rotate(ROTATE+rightDrive);
    }
    interrupts();
}
