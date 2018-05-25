#include "Sensors.h"
#include "Motors.h"

Sensors sensors;
Motors motors;

void setup() {
	//sensors.init( 100000 );
	motors.init();
    sensors.init(30000);
	motors.stop();
	Serial.begin( 57600 );
	motors.setSpeed(70);
	while( !Serial );
	UTurn();
}

void loop() {
	delay(1000);	
}

void UTurn() {
	//motors.moveBackward();
	while( sensors.getLeftDistance() < 5 ){ 
	Serial.println("Moving backwards");
	}
	Serial.println("Done");
	motors.stop();
}
