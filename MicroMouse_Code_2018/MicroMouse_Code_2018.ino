#include "Sensors.h"
#include "Motors.h"

Sensors sensors;
Motors motors;
String directions;
int stepCounter;
int incomingByte = 0;


void setup() {
    Serial.begin( 57600 );
    motor_init();
    delay(500);  
}

void loop() {
    if (Serial.available() > 0) {
        // read the incoming byte:
        incomingByte = Serial.read();
        if (incomingByte == 'a') {
            //test some function
        }
        else if (incomingByte == 'd'){
            //some some function
        }
    }
}


