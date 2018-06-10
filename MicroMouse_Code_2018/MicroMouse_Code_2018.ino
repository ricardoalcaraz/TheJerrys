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
const uint16_t UTURN = 430;       // 180 degree turn
double SETPOINT = 4;

//pid settings and gains
#define OUTPUT_MIN 0
#define OUTPUT_MAX 4
#define KP 1.5
#define KI .0002
#define KD 1.5

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
            autoForward(FORWARD);
            delay(100);
}





//Input: None
//Output: Intersection turn decision
char getTurn(){
    //Get room
    //wall threshold based on distance to middle of next room
    unsigned int wallDistance = 15;
    String room = (String(sensors.getLeftDistance()   < wallDistance) + 
                   String(sensors.getMiddleDistance() < wallDistance) + 
                   String(sensors.getRightDistance()  < wallDistance));
   //Decide turn based on left hand rule
    if      (room == "100") return  'S';
    else if (room == "101") return NULL;
    else if (room == "110") return  'R';
    else if (room == "111") return  'U';
    else                    return  'L';
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

