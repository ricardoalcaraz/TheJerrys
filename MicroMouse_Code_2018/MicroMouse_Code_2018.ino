#include "Sensors.h"
#include "Motors.h"

Sensors sensors;
Motors motors;
String directions;

void setup() {
    motors.init();
    sensors.init(50000);
    Serial.begin( 57600 );
    Serial.println( "Initializing" );
    motors.stop();
	motors.setSpeed(20);
	motors.setLeftSpeed(20);
	motors.setRightSpeed(20);
	delay(5000);
}

void loop() {
	motors.moveForward();
  motors.go();
  delay(10000);
  /*
	//Keep moving unless there is an intersection or dead end
	while( sensors.getRightDistance() < 5 && sensors.getLeftDistance() < 5 && sensors.getMiddleDistance() > 2 );
	motors.stop();

	//Dead end scenario
	if( sensors.getMiddleDistance() < 5 && sensors.getRightDistance() < 5 && sensors.getRightDistance() < 5 ){
		motors.moveBackward();
		while( sensors.getLeftDistance() < 5 && sensors.getRightDistance() < 5 );
		motors.stop();
		if( sensors.getRightDistance() > 5 ){
			rightBackTurn();
		} else if( sensors.getLeftDistance() > 5 ) {
			leftBackTurn();
		}
	}
	//Intersection with left turn scenario
	if(sensors.getLeftDistance() > 5){
		turnAroundLeftCorner();
	}

	//Intersection with options to go forward but not left
	else if( sensors.getMiddleDistance() > 5 ){
		motors.moveForward();
		while(sensors.getRightDistance() > 5 || sensors.getLeftDistance() > 5);
		motors.stop();
	}
	else if( sensors.getRightDistance() > 5 ) {
		turnAroundRightCorner();
	}
	motors.stop();
	delay(100);
	motors.moveForward(50);
  */
/*
	Serial.print( "Right Distance: " ); Serial.println( sensors.getRightDistance() );
    Serial.print( "Left Distance: " ); Serial.println( sensors.getLeftDistance() );
    Serial.print( "Middle Distance: " ); Serial.println( sensors.getMiddleDistance() );
	delay(500);
*/
}

void leftBackTurn() {
	//motors.moveBackward();
	motors.turnLeft(75);
	motors.turnRight(-175);
	motors.turnLeft(80);
}

void rightBackTurn() {
	motors.turnRight(75);
	motors.turnLeft(-175);
	motors.turnRight(90);
}

void turnAroundRightCorner() {
	motors.moveForward(70);
	motors.turnRight();
}

void turnAroundLeftCorner() {
	motors.moveForward(70);
	motors.turnLeft();
}
