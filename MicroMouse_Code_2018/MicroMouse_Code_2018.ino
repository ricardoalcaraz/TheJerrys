#include "Sensors.h"
#include "Motors.h"

Sensors sensors;
Motors motors;
String directions;

void setup() {
    motors.init();
    sensors.init(50000);
    Serial.begin( 57600 );
    while( !Serial );
    Serial.println( "Initializing" );
    motors.stop();
}

void loop() {
    delay(2000);	
	motors.turnRight();
}

void UTurn() {
	//motors.moveBackward();
	while( sensors.getLeftDistance() < 5 ){ 
	Serial.println("Moving backwards");
	}
	Serial.println("Done");
	motors.stop();
}

void turnAroundRightCorner() {
	motors.setSpeed(50);
	motors.moveForward(100);
	motors.turnRight();
}


