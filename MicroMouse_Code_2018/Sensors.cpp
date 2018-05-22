#include "Sensors.h"

//Initializing an external functions so ISR can run properly
static void sensorISR();

//Pinout for the ultrasonic sensors
const uint8_t ECHO1 = 8;
const uint8_t ECHO2 = 2;
const uint8_t ECHO3 = 10;
const uint8_t TRIG1 = 9;
const uint8_t TRIG2 = 3;
const uint8_t TRIG3 = 11;
volatile uint16_t Sensors::runningAvgLeft[4]={};
volatile uint16_t Sensors::runningAvgRight[4]={};
volatile uint16_t Sensors::runningAvgMiddle[4]={};

//Constructor
Sensors::Sensors( ) {
	//Set all the running average arrays to zero
	for( int i = 0; i < 4; i++ ) {
		runningAvgLeft[i] = 0;
		runningAvgRight[i] = 0;
		runningAvgMiddle[i] = 0;
	}
	timeout = 6000;
	interval = 10000;
}

//Initialize the pins for all the sensors
//Currently setup for ultrasonic sensors
void Sensors::init( uint32_t interval ) {
  	pinMode( ECHO2 ,INPUT );
  	pinMode( ECHO1 ,INPUT );
  	pinMode( ECHO3 ,INPUT );
  	pinMode( TRIG1 ,OUTPUT );
  	pinMode( TRIG2 ,OUTPUT );
  	pinMode( TRIG3 ,OUTPUT );
	this->interval = interval;
	sensorTimer.begin( sensorISR, this->interval );	
	sensorTimer.priority( 50 );
}

void Sensors::setTimeout( uint32_t timeout ) {
	this->timeout = timeout;
}

//Return the averaged out right distance
uint16_t Sensors::getRightDistance( ) {
	uint16_t sum = 0;
	for( int i = 0; i < 4; i++ ) {
		sum += runningAvgRight[i];
	}
	float avg = (float)sum/4.0;
	return avg;
}

//Return the averaged out left distance
uint16_t Sensors::getLeftDistance( ) {
	noInterrupts();
	uint16_t sum = 0;
	for( int i = 0; i < 4; i++ ) {
		sum += runningAvgLeft[i];
	}
	float avg = (float)sum/4.0;
	interrupts();
	return avg;
}

//Return the averaged out middle distance
uint16_t Sensors::getMiddleDistance( ) {
	noInterrupts();
	uint16_t sum = 0;
	for( int i = 0; i < 4; i++ ) {
		sum += runningAvgMiddle[i];
	}
	interrupts();
	return sum/4.0;
}

//Update all the distances of the sensors
//and input them into the running average array
void Sensors::updateDistances() {
	static volatile uint8_t index = 0;
	runningAvgLeft[index] = pingLeft();
	runningAvgRight[index] = pingRight();
	runningAvgMiddle[index] = pingMiddle();
	index++;
	if( index > 3 ) index = 0;
}

//Return a single instance of the right sensor
volatile uint16_t Sensors::pingRight() {
    digitalWrite(TRIG2, LOW);
  	delayMicroseconds(2);
  	digitalWrite(TRIG2, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(TRIG2, LOW);

  	//Read the echo pin
  	int duration = pulseIn(ECHO2, HIGH, timeout);

  	//Calculate distance
  	float distance = (float) duration*0.034/2;

  	return distance;	
}

//Return a single instance of the middle sensor
volatile uint16_t Sensors::pingLeft() {
    digitalWrite(TRIG3, LOW);
  	delayMicroseconds(2);
  	digitalWrite(TRIG3, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(TRIG3, LOW);

  	//Read the echo pin
  	int duration = pulseIn(ECHO3, HIGH, timeout);

  	//Calculate distance
  	float distance = (float)duration*0.034/2;

  	return distance;	
}

//Return a single instance of the middle sensor
volatile uint16_t Sensors::pingMiddle() {
  	digitalWrite(TRIG1, LOW);
  	delayMicroseconds(2);
  	digitalWrite(TRIG1, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(TRIG1, LOW);

  	//Read the echo pin
  	int duration = pulseIn(ECHO1, HIGH, timeout);

  	//Calculate distance
  	float distance = (float) duration*0.034/2;

  	return distance;	
}

Sensors sensorInterrupt;

//External interrupt function that points toward internal function, it's somewhat hacky but it works.
static void sensorISR() {
	sensorInterrupt.updateDistances();
}
