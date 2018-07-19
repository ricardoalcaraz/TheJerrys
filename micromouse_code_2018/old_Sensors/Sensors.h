#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"


/*
------------------Created by Ricardo Alcaraz----------------
	Class created to abstract the sensors into its own class
	This class will constantly run and grab sensor values
	The values will be put in through a running average to
	clean up the data and get rid of erroneous errors
------------------------------------------------------------
*/
class Sensors {
	
	public:
		//Constructor
		Sensors( );
		
		//Function to initialize the sensors
		void init( uint32_t interval );
		
		//Set the time in interval for how often sensors should update
		void setInterval( uint32_t interval );

		//Set the timeout interval for the ultrasonic sensors
		void setTimeout( uint32_t timeout );

		//Return the distance for the right sensor
		uint16_t getRightDistance();

		//Return the distance for the left sensor
		uint16_t getLeftDistance();

		//Return the distance for the middle sensor
		uint16_t getMiddleDistance();

		//Get a single instance of the right sensor
		volatile uint16_t pingRight();
		
		//Get a single instance of the left sensor
		volatile uint16_t pingLeft();
		
		//Get a single instance of the middle sensor
		volatile uint16_t pingMiddle();

		//Update all the distances
		void updateDistances();

		//Value that signifies how large running average array is
		static const uint8_t arraySize = 3;

		//Holds 4 most recent values for right sensor
		static volatile uint16_t runningAvgRight[arraySize];

		//Holds 4 most recent values for left sensor
		static volatile uint16_t runningAvgLeft[arraySize];

		//Holds 4 most recent values for middle sensor
		static volatile uint16_t runningAvgMiddle[arraySize];

	private:
		
		//Interrupt timer for running the sensors
		IntervalTimer sensorTimer;
		
		//This number represents how often the sensors are being updated
		uint32_t interval; //Value is in microseconds

		//This number represents holds long we'll wait before timeout
		uint32_t timeout; //Number is microseconds
};

#endif

extern Sensors sensorInterrupt;
