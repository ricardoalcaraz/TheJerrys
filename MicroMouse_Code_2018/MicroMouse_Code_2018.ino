#include "Sensors.h"
#include "Motors.h"

Sensors sensors;
Motors motors;
String directions;
int stepCounter;

void setup() {
    //sensors.init( 100000 );
    motors.init();
    sensors.init(50000);
    Serial.begin( 57600 );
    while( !Serial );
    Serial.println( "Initializing" );
    motors.stop();
}

void loop() {
    delay(100);	
}


