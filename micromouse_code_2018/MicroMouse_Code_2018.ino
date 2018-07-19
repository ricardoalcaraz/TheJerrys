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

const uint16_t CELL = 47;     // Suggested: 40 Clears block and some extra to be safe
const uint16_t CELLRESET = 200;   //Centers the robot
const uint16_t TANKLEFT = 230;    // 90 degree turn left
const uint16_t TANKRIGHT = 230;   // 90 degree turn right
const uint16_t UTURN = 450;       // 180 degree turn
const uint16_t CALLIBRATE = 25; //Steps to get to center of cell upon detecting an opening Suggested: 20

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
  delay(1500);
  leftStepper.begin(10, 4);
  rightStepper.begin(10, 4);
  leftDistancePID.setTimeStep(1);
  rightDistancePID.setTimeStep(1);

  //single test
    autoForward(CELL);
    
    autoForward(10);
    motors.tankLeft(TANKLEFT);
    autoForward(CELL);

    autoForward(CELL);
    
    autoForward(10);
    motors.tankLeft(TANKLEFT);
    autoForward(CELL);
    
    autoForward(CELL);
}

void loop() {
    if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
      if (incomingByte == 'w') {
          autoForward(CELL);

      }
      else if (incomingByte == 'a'){
          autoForward(10);
          motors.tankLeft(TANKLEFT);
          autoForward(CELL);
      }
      else if (incomingByte == 'd'){
          autoForward(10);
          motors.tankRight(TANKRIGHT);
          autoForward(CELL);
      }
    }

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

/*
void autoForward(int steps) {
    int leftDistance = sensors.getLeftDistance();
    int rightDistance = sensors.getRightDistance();
    int middleDistance = sensors.getMiddleDistance();
    
    motors.turnOn();
//    noInterrupts();
    bool rstOnce = false; //Prevents repeated if/else flow
    if (  (leftDistance > 15) || (rightDistance > 15)  ) {
        //rstOnce = true : rstOnce = false;
        rstOnce = true;
        Serial.println("Stared at an intersection");
    }
    //If leaving/starting at a cell with a possible intersection, use normal hardcoded cell traversal and prevent multiple resets
       
    //FIXME: Prevent pid from acting if missing wall and moving forward
    bool leftIntersection = (  leftDistance > 15 );
    bool rightIntersection = (  rightDistance > 15 );

    for (int i = steps; i > 0; i --){
        leftDistance = sensors.getLeftDistance();
        rightDistance = sensors.getRightDistance();
        middleDistance = sensors.getMiddleDistance();
        if (   (  (leftDistance > 15) || (rightDistance > 15)  ) && rstOnce == false   ){
            Serial.println("Entering intersection");
            //Constantly check if entering a cell with a possible intersection and callibrate it to go to the middle
            steps = CLEARANCE; 
            rstOnce = true;
        }
        
        //call PID calculations every loop
        // If-else statements are attempting to prevent robot swerving left/right when reaching an intersection
        leftDistancePID.run();
        rightDistancePID.run();
        for(int i = 0; i < 2; i++){
          rightStepper.rotate(ROTATE+leftDrive);
          leftStepper.rotate(ROTATE+rightDrive);
        }
    }
//    interrupts();
}
*/

void autoForward(int STEPS) {
    motors.turnOn();
    noInterrupts();

    int WALLTHRESHOLD = 12;

    rightDistance = sensors.getRightDistance();
    leftDistance = sensors.getLeftDistance();

    bool callibrateStepsOnce = (  (rightDistance > WALLTHRESHOLD) || (leftDistance > WALLTHRESHOLD)  ); //Prevents repeated if/else flow. Cannot use isIntersection since isIntersection uses middle wall
    
    for (int i = STEPS; i > 0; i--){

        rightDistance = sensors.getRightDistance();
        leftDistance = sensors.getLeftDistance(); 

        if ( ( (rightDistance > WALLTHRESHOLD) || (leftDistance > WALLTHRESHOLD) ) && !callibrateStepsOnce  ){
            //If an intersection is reached, and has not alreayd been recallibrated, recallibrate steps
            callibrateStepsOnce = true;
            i = CALLIBRATE;
        }
    
        //call PID calculations every loop
        // FIXME: If-else statements are attempting to prevent robot swerving left/right when reaching an intersection
        leftDistancePID.run();
        rightDistancePID.run();
        for(int i = 0; i < 2; i++){
          rightStepper.rotate(ROTATE+leftDrive);
          leftStepper.rotate(ROTATE+rightDrive);
        }
    }
    interrupts();
}
