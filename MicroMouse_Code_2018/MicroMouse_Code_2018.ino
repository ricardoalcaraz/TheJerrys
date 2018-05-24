#include "Sensors.h"
#include "Motors.h"

Sensors sensors;
Motors motors;

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
    static uint8_t speed = 100;
    if( Serial.available() > 0 ){
        char incomingChar = Serial.read();
        switch (incomingChar) {
            case 'a':
                motors.turnLeft();
                Serial.println( "Turning left");
                break;
            case 'd':
                motors.turnRight();
                Serial.println( "Turning right");
                break;
            case 'x':
                motors.stop();
                break;
            case 'w':
                motors.moveForward(8000);
                Serial.println( "Moving forward ");
                break;
            case '+':
                speed+=10;
                motors.setSpeed(speed);
                Serial.print( "Current speed is now: "); Serial.println( speed );
                break;
            case '-':
                speed-=10;
                motors.setSpeed(speed);
                Serial.print( "Current speed is now: "); Serial.println( speed );
                break;
        }
        motors.stop();
    }

    Serial.print( "Right Distance: " ); Serial.println( sensors.getRightDistance() );
    Serial.print( "Left Distance: " ); Serial.println( sensors.getLeftDistance() );
    Serial.print( "Middle Distance: " ); Serial.println( sensors.getMiddleDistance() );
    delay(100);
}
