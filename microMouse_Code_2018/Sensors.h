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
		double getRightDistance();

		//Return the distance for the left sensor
		double getLeftDistance();

		//Return the distance for the middle sensor
		double getMiddleDistance();

		//Get a single instance of the right sensor
		volatile double pingRight();

		//Get a single instance of the left sensor
		volatile double pingLeft();

		//Get a single instance of the middle sensor
		volatile double pingMiddle();

		//Update all the distances
		void updateDistances();

		//Value that signifies how large running average array is
		static const uint8_t arraySize = 3;

		//Holds 4 most recent values for right sensor
		static volatile double runningAvgRight[arraySize];

		//Holds 4 most recent values for left sensor
		static volatile double runningAvgLeft[arraySize];

		//Holds 4 most recent values for middle sensor
		static volatile double runningAvgMiddle[arraySize];

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
