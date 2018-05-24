#ifndef Motors_h
#define Motors_h

#include "Arduino.h"

/*
--------------------Created by Ricardo Alcaraz-----------------
	Class created to abstract the motor functions into its own
	class. This will allow the ability to move and turn with
	stepper motors as the motors used
---------------------------------------------------------------
*/
class Motors {

	public:
		//Constructor
		Motors( );
		void init( );
		void setSpeed(uint8_t speed);
		void moveForward( );
		void moveForward( uint32_t steps );
		void moveBackward( );
		void moveBackward( uint32_t steps );
		void stop( );
		void go( );
		void turnLeft( );
		void turnLeft( uint32_t steps );
		void turnRight( );
		void turnRight( uint32_t steps );
		void turnAround( );
		void setStepsPerRevolution( uint16_t steps );
		static uint16_t stepsPerRevolution;
		static uint32_t speed;
		void takeAStep();
	private:
		IntervalTimer motorTimer;
		uint32_t interval;
};

#endif 

extern Motors motorInterrupt;
