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

		//Initialize
		/*Initialize the pinout for all the motors*/
		void init( );

		//Set Speed
		/*This accepts a number from 1-255 and scaled it to
		 *a proper speed that the stepper motor can accept
		 *This will set the speed variable*/
		void setSpeed(uint8_t speed);

		//Move Forward
		//NOTE: May be deprecated
		/*Continously move forward through an interrupt routine*/
		void moveForward( );

		//Move Forward
		/*Move forward only a certain amount of steps*/
		void moveForward( uint32_t steps );
		void moveBackward( );
		void moveBackward( uint32_t steps );
		void stop( );
		void go( );
		void turnLeft( );
		void tankTurnLeft( );
		void turnLeft( uint32_t steps );
		void turnRight( );
		void turnRight( uint32_t steps );
		void tankTurnRight( );
		void turnAround( );
		void setStepsPerRevolution( uint16_t steps );
		static uint16_t stepsPerRevolution;
		//Speed variable, held as a microsecond and scaled with the set speed functions
		static uint32_t speed;
		//Take a single step
		void takeAStep();

		//Constant numbers that signify amount of steps until
		//robot turns
		const int turnAroundSteps = 450;
		const uint16_t rightTurnStepAmount = 480;
		const uint16_t leftTurnStepAmount = 480;
		const int rightTankTurnStepAmount = 310;
		const int leftTankTurnStepAmount = 290;
	private:
		IntervalTimer motorTimer;
		uint32_t interval;
};

#endif 

extern Motors motorInterrupt;
