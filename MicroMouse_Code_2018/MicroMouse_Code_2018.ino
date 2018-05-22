#include "Sensors.h"
#include "Motors.h"

Sensors sensors;
Motors motors;

void setup() {
	//sensors.init( 100000 );
	motors.init( );
  	Serial.begin( 57600 );
	while( !Serial );
	Serial.println( "Initializing" );
	motors.go();
}

void loop() {
	for(int i = 255; i > 0; i-=10){
		motors.moveForward( 4000 );
		motors.setSpeed((uint8_t)i);
	}
}
