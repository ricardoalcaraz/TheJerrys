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
volatile double Sensors::runningAvgLeft[arraySize]={};
volatile double Sensors::runningAvgRight[arraySize]={};
volatile double Sensors::runningAvgMiddle[arraySize]={};

//Constructor
Sensors::Sensors( ) {
	//Set all the running average arrays to zero
	for( int i = 0; i < arraySize; i++ ) {
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
double Sensors::getRightDistance( ) {
	uint16_t sum = 0;
	for( int i = 0; i < arraySize; i++ ) {
		sum += runningAvgRight[i];
	}
	double avg = sum/(double)arraySize+1;
	return avg;
}

//Return the averaged out left distance
double Sensors::getLeftDistance( ) {
	noInterrupts();
	double sum = 0;
	for( int i = 0; i < arraySize; i++ ) {
		sum += runningAvgLeft[i];
	}
	double avg = sum/(double)arraySize+1;
	interrupts();
	return avg;
}

//Return the averaged out middle distance
double Sensors::getMiddleDistance( ) {
	noInterrupts();
	double sum = 0;
	for( int i = 0; i < arraySize; i++ ) {
		sum += runningAvgMiddle[i];
	}
	interrupts();
	return sum/(double)arraySize+1;
}

//Update all the distances of the sensors
//and input them into the running average array
void Sensors::updateDistances() {
	static volatile uint8_t index = 0;
	static volatile uint8_t sensorCount = 0;
	switch( sensorCount ) {
		case 0:
			runningAvgLeft[index] = pingLeft();
			break;
		case 1:
			runningAvgRight[index] = pingRight();
			break;
		case 2:
			runningAvgMiddle[index] = pingMiddle();
			break;
	}
	index++;
	sensorCount++;
	if( index == arraySize ) index = 0;
	if( sensorCount == 3 ) sensorCount = 0;
}

//Return a single instance of the right sensor
volatile double Sensors::pingRight() {
      digitalWrite(TRIG2, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG2, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG2, LOW);

    //Read the echo pin
    int duration = pulseIn(ECHO2, HIGH, timeout);

    //Calculate distance
    double distance = (double) duration*0.034/2;

    return distance;
}

//Return a single instance of the middle sensor
volatile double Sensors::pingLeft() {
    digitalWrite(TRIG3, LOW);
  	delayMicroseconds(2);
  	digitalWrite(TRIG3, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(TRIG3, LOW);

  	//Read the echo pin
  	int duration = pulseIn(ECHO3, HIGH, timeout);

  	//Calculate distance
  	double distance = (double) duration*0.034/2;

  	return distance;
}

//Return a single instance of the middle sensor
volatile double Sensors::pingMiddle() {
  	digitalWrite(TRIG1, LOW);
  	delayMicroseconds(2);
  	digitalWrite(TRIG1, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(TRIG1, LOW);

  	//Read the echo pin
  	int duration = pulseIn(ECHO1, HIGH, timeout);

  	//Calculate distance
  	double distance = (double) duration*0.034/2;

  	return distance;
}

Sensors sensorInterrupt;

//External interrupt function that points toward internal function, it's somewhat hacky but it works.
static void sensorISR() {
	sensorInterrupt.updateDistances();
}
