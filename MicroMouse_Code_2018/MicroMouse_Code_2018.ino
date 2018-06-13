#include "Sensors.h"
#include "Motors.h"
#include <AutoPID.h>

Sensors sensors;
Motors motors;

String directions;
int stepCounter;
int incomingByte = 0;
const uint16_t FORWARD = 4000;     // Clears block and some extra to be safe
const uint16_t TANKLEFT = 200;    // 90 degree turn left
const uint16_t TANKRIGHT = 200;   // 90 degree turn right
const uint16_t UTURN = 400;       // 180 degree turn
const uint16_t CLEARANCE = 200;       // 180 degree turn

double SETPOINT = 4;

//pid settings and gains
#define OUTPUT_MIN 0.5  // Suggested: 0
#define OUTPUT_MAX 1.5  // Suggested: 4
#define KP 2.0          // Suggested: 1.5
#define KI 0.0002            // Suggested: .0002
#define KD 1.5            // Suggested: 1.5

double leftDistance, rightDistance, rightDrive, leftDrive;


//input/output variables passed by reference, so they are updated automatically
AutoPID leftDistancePID(&leftDistance, &SETPOINT, &rightDrive, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
AutoPID rightDistancePID(&rightDistance, &SETPOINT, &leftDrive, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

void setup() {
    Serial.begin( 57600 );
    motors.init();
    sensors.init();
    delay(500);  

    leftDistancePID.setTimeStep(1);
    rightDistancePID.setTimeStep(1);
}

void loop() {
//    Serial.print(sensors.getLeftDistance()); Serial.print("    "); Serial.println(sensors.getRightDistance());
//    if (Serial.available() > 0) {
//        // read the incoming byte:
//        incomingByte = Serial.read();
//        if (incomingByte == 'w') {
//            autoForward(FORWARD);
//        }
//        else if (incomingByte == 's'){
//            motors.uTurn(UTURN);
//        }
//        else if (incomingByte == 'a'){
//            motors.tankLeft(TANKLEFT);
//        }
//        else if (incomingByte == 'd'){
//            motors.tankRight(TANKRIGHT);
//        }
//        else if (incomingByte == 'x'){
//            motors.turnOff();
//        }
//        else if (incomingByte == 'q'){
//            autoForward(200);
//        }
//    }
//    delay(5);

    /*
    char turn = getTurn();
    if (turn == 'L') motors.tankLeft(TANKLEFT);
    else if (turn == 'S') autoForward(600);
    else if (turn == 'R') motors.tankRight(TANKRIGHT);
    else if (turn == 'U') motors.uTurn(UTURN);
    else autoForward(100);
    */
      
}





//Input: None
//Output: Intersection turn decision
char getTurn(){
    String debounce;
    //Get room
    //wall threshold based on distance to middle of next room
    unsigned int wallDistance = 15;

    for (int i = 0; i < 20; i++){
    
        String room = (String(sensors.getLeftDistance()   < wallDistance) + 
                       String(sensors.getMiddleDistance() < wallDistance) + 
                       String(sensors.getRightDistance()  < wallDistance));
       //Decide turn based on left hand rule
        if      (room == "100") debounce+=  'S';
        else if (room == "101") debounce+= NULL;
        else if (room == "110") debounce+=  'R';
        else if (room == "111") debounce+=  'U';
        else                    debounce+=  'L';
        //delay(25); //FIXME: Helps to debounce and space signals out, but may stall PID forward
    }

    //Signal debouncing
    if      (debounce.indexOf("SSSSSSSSSS") > 0) return 'S';
    else if (debounce.indexOf("RRRRRRRRRR") > 0) return 'R';
    else if (debounce.indexOf("UUUUUUUUUU") > 0) return 'U';
    else if (debounce.indexOf("LLLLLLLLLL") > 0) return 'L';
    else return NULL;
    
}


//Input: None
//Output: Boolean representing if there is an intersection
bool isIntersection(){
    int wallThreshold = 15;
    if ( (sensors.getLeftDistance()   < wallThreshold) &&  
         (sensors.getMiddleDistance() > wallThreshold) && 
         (sensors.getRightDistance()  < wallThreshold)  
        ) return false;
    else  return true;
}


void autoForward(int STEPS){
    double speed = 500;
    
    //int left, right; //Initialize here if pinging less often
    
    for (int i = 0; i < STEPS; i += 7){ //larger multiples than 1 since I tried stepping additional steps below
        leftDistance = sensors.getLeftDistance();
        rightDistance = sensors.getRightDistance(); 

        //call PID calculations every loop
        leftDistancePID.run();
        rightDistancePID.run();
        
        Serial.print(leftDistance); Serial.print("      ");Serial.print(leftDrive); Serial.print("     "); Serial.print(rightDistance); Serial.print("     ");Serial.println(rightDrive);
        motors.leftForward(7, speed + leftDrive*500);
        motors.rightForward(7, speed + rightDrive*500);

    }
}  

