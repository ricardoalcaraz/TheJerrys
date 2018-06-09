#include "Sensors.h"

//Pinout for the ultrasonic sensors

const uint8_t ECHO1 = 8; //middle
const uint8_t ECHO2 = 2; //left
const uint8_t ECHO3 = 10; //right
const uint8_t TRIG1 = 9; //middle
const uint8_t TRIG2 = 3; //left
const uint8_t TRIG3 = 11; //right

//Constructor
Sensors::Sensors( ) {
}

//Initialize the pins for all the sensors
//Currently setup for ultrasonic sensors
void Sensors::init() {
    pinMode( ECHO2 ,INPUT );
    pinMode( ECHO1 ,INPUT );
    pinMode( ECHO3 ,INPUT );
    pinMode( TRIG1 ,OUTPUT );
    pinMode( TRIG2 ,OUTPUT );
    pinMode( TRIG3 ,OUTPUT );

}

int Sensors::getRightDistance(){
    digitalWrite(TRIG2, LOW);
    delayMicroseconds(2);
  
    digitalWrite(TRIG2, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG2, LOW);

    int duration = pulseIn(ECHO2, HIGH);

    int distance= duration*0.034/2;
    return distance;
}

int Sensors::getMiddleDistance(){
    digitalWrite(TRIG1, LOW);
    delayMicroseconds(2);
  
    digitalWrite(TRIG1, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG1, LOW);

    int duration = pulseIn(ECHO1, HIGH);

    int distance= duration*0.034/2;
    return distance;
}

int Sensors::getLeftDistance(){
    digitalWrite(TRIG3, LOW);
    delayMicroseconds(2);
  
    digitalWrite(TRIG3, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG3, LOW);

    int duration = pulseIn(ECHO3, HIGH);

    int distance= duration*0.034/2;
    return distance;
}

