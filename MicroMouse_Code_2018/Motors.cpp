#include "Motors.h"

//Initializing external function so ISR can work properly
static void motorISR();

//Pinout for the stepper motors
const uint8_t EN1 = 20;
const uint8_t EN2 = 21;
const uint8_t STEP1 = 4;
const uint8_t STEP2 = 5;
const uint8_t DIR1 = 6;
const uint8_t DIR2 = 7;

uint32_t Motors::speed = 100;
uint16_t stepsPerRevolution = 250;

Motors::Motors( ) {

}

void Motors::init( ) {
  	pinMode( EN1, OUTPUT);
  	pinMode( EN2, OUTPUT);
  	pinMode( STEP1, OUTPUT);
  	pinMode( STEP2, OUTPUT);
  	pinMode( DIR1, OUTPUT);
  	pinMode( DIR2, OUTPUT);
  	digitalWrite( EN1, HIGH );
  	digitalWrite( EN2, HIGH );
	//Set the default direction to forward 
	digitalWrite( DIR1, HIGH );
	digitalWrite( DIR2, HIGH );
	motorTimer.begin( motorISR, speed );
	motorTimer.priority( 128 );
}

//Enables the motor so they can move
void Motors::go( ) {
	digitalWrite( EN1, LOW );
	digitalWrite( EN2, LOW );
}

void Motors::setSpeed( uint8_t speed ){
	this->speed = speed;
}
//Stops the motors from moving
void Motors::stop ( ) {
  	digitalWrite( EN1, HIGH );
  	digitalWrite( EN2, HIGH );
}

//Continuosly move forward
void Motors::moveForward( ) {
	digitalWrite( DIR1, HIGH );
	digitalWrite( DIR2, HIGH );
}

//Move forward only a certain amount of steps
void Motors::moveForward( uint32_t steps ) {
	noInterrupts();
	stop();
	digitalWrite( DIR1, HIGH );
	digitalWrite( DIR2, HIGH );
	go();
	for( uint32_t i = 0; i < steps*2; i++ ) {
		digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
		delayMicroseconds(speed);
		digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
	}
	stop();
	interrupts();
}

void Motors::takeAStep() {
	//Write a square wave to the two step pins to move
	//motors forward
	digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
	digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
}

Motors motorInterrupt;

static void motorISR() {
	motorInterrupt.takeAStep();
}
