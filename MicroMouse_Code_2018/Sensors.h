#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"

class Sensors {
	public:
		Sensors();
		
		//Function to initialize the sensors
		void init(  );
		
		//Return the distance for the left sensor
		int getLeftDistance();

        //Return the distance for the middle sensor
        int getMiddleDistance();

        //Return the distance for the right sensor
        int getRightDistance();
};

#endif

