#include "Sensors.h"
#include "Motors.h"

Sensors sensors;
Motors motors;
String directions;
int stepCounter;
int incomingByte = 0;
const uint16_t FORWARD = 200;
const uint16_t BACKWARD = 200;
const uint16_t LEFT = 200;
const uint16_t RIGHT = 200;
const uint16_t UTURN = 430;


void setup() {
    Serial.begin( 57600 );
    motors.init();
    delay(500);  
}

void loop() {
    if (Serial.available() > 0) {
        // read the incoming byte:
        incomingByte = Serial.read();
        if (incomingByte == 'w') {
            motors.forward(FORWARD);
        }
        else if (incomingByte == 's'){
            motors.backward(BACKWARD);
        }
        else if (incomingByte == 'a'){
            motors.tankLeft(LEFT);
        }
        else if (incomingByte == 'd'){
            motors.tankRight(RIGHT);
        }
        else if (incomingByte == 'x'){
            motors.uTurn(UTURN);
        }
    }
}


