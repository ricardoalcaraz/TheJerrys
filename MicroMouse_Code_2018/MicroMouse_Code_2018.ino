#include "Sensors.h"
#include "Motors.h"

Sensors sensors;
Motors motors;

String directions;
int stepCounter;
int incomingByte = 0;
const uint16_t FORWARD = 4000;     // Clears block and some extra to be safe
const uint16_t TANKLEFT = 200;    // 90 degree turn left
const uint16_t TANKRIGHT = 200;   // 90 degree turn right
const uint16_t UTURN = 430;       // 180 degree turn

void setup() {
    Serial.begin( 57600 );
    motors.init();
    sensors.init();
    delay(500);  

}

void loop() {
//    Serial.print(sensors.getLeftDistance()); Serial.print("    "); Serial.println(sensors.getRightDistance());
    if (Serial.available() > 0) {
        // read the incoming byte:
        incomingByte = Serial.read();
        if (incomingByte == 'w') {
            autoForward(FORWARD);
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
            autoForward(200);
        }
    }
//    delay(5);
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
    uint16_t speed = 5;
    
    //int left, right; //Initialize here if pinging less often
    
    for (int i = 0; i < STEPS; i += 5){ //larger multiples than 1 since I tried stepping additional steps below
        int left = sensors.getLeftDistance();
        int right = sensors.getRightDistance(); 
//        if (i % 50 == 0){
//            left = sensors.getLeftDistance();
//            right = sensors.getRightDistance();
//        }
        //Didn't write a case where they are equal to and step equally since the odd sizing of the robot never had them equal to each other, feel free to experiment
        if (left > right){
//            leftSpeed++;
//            rightSpeed++;
            motors.leftForward(1, speed - 4);
            motors.rightForward(2, speed + 4);
        }
        else{
//            leftSpeed--;
//            rightSpeed++;
            motors.leftForward(2, speed + 4);
            motors.rightForward(1, speed - 4);

        }
    }  
       
}

