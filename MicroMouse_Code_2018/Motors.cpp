#include "Motor.h"

//Initializing external function so ISR can work properly
static void motorISR();

//Pinout for the stepper motors
const uint8_t EN1 = 20;
const uint8_t EN2 = 21;
const uint8_t STEP1 = 4;
const uint8_t STEP2 = 5;
const uint8_t DIR1 = 6;
const uint8_t DIR2 = 7;

uint8_t Motors::speed = 100;
uint16_t stepsPerRevolution = 250;

Motors::Motors( ) {

}

Motors::init( ) {
  	pinMode( EN1, OUTPUT);
  	pinMode( EN2, OUTPUT);
  	pinMode( STEP1, OUTPUT);
  	pinMode( STEP2, OUTPUT);
  	pinMode( DIR1, OUTPUT);
  	pinMode( DIR2, OUTPUT);
  	digitalWrite( EN1, HIGH );
  	digitalWrite( EN2, HIGH );
	//Set the default direction to forward 
	/*Since the motors are mirrored, the direction value has
	 *to be opposite of each other to move in the same 
	 *direction*/
	digitalWrite( DIR1, HIGH );
	digitalWrite( DIR2, LOW );
}

Motors::go( ) {
	digitalWrite( EN1, LOW );
	digitalWrite( EN2, LOW );
}

Motors::moveForward( ) {
	digitalWrite( DIR1, HIGH );
	digitalWrite( DIR2, LOW );
}

Motors::moveForward(

Motors::takeAStep() {
	//Write a square wave to the two step pins to move
	//motors forward
	digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
	digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
}

Motors motorInterrupt;

static void motorISR() {
	motorInterrupt.takeAStep();
}
