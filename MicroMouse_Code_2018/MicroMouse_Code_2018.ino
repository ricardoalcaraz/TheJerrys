#include "Sensors.h"
const uint8_t EN1 = 20;
const uint8_t EN2 = 21;
const uint8_t STEP1 = 4;
const uint8_t STEP2 = 5;
const uint8_t DIR1 = 6;
const uint8_t DIR2 = 7;

Sensors sensors;

void setup() {
	sensors.init( 100000 );
  	pinMode( EN1, OUTPUT);
  	pinMode( EN2, OUTPUT);
  	pinMode( STEP1, OUTPUT);
  	pinMode( STEP2, OUTPUT);
  	pinMode( DIR1, OUTPUT);
  	pinMode( DIR2, OUTPUT);
  	digitalWrite( EN1, HIGH );
  	digitalWrite( EN2, HIGH );
  	Serial.begin( 57600 );
	while( !Serial );
	Serial.println( "Initializing" );
}

void loop() {
	Serial.print( "Right Distance: " ); Serial.println( sensors.getRightDistance() );
  	Serial.print("Left Distance: "); Serial.println( sensors.getLeftDistance() );
  	Serial.print("Middle Distance: "); Serial.println( sensors.getMiddleDistance() );
  delay(1000);
}
