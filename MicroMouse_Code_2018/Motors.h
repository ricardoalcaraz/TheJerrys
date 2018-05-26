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
		
		//Move backward
		/*Move the motors backward continously through an interrupt service routine*/
		void moveBackward( );

		//Move backward
		/*Move backward a certain amount of steps not through an interrupt service routine*/
		void moveBackward( uint32_t steps );

		//Stop all motor functions
		void stop( );

		//Continue all motor functions
		void go( );

		//Turn Left
		/*Turn the motors left on a pivot*/
		void turnLeft( );

		//Turn left style
		/*Turn the motors left on a tank style turn where the wheels reverse*/
		void tankTurnLeft( );

		//Turn left a certain amount of steps
		void turnLeft( int32_t steps );

		//Turn right
		/*Turn the motors to a perfect 90 degree angle*/
		void turnRight( );

		//Turn back right
		/*Turn right on a backwards pivot*/
		void turnBackRight( );

		//Turn back left
		/*Turn the motors on a backwards pivot*/
		void turnBackLeft( );

		//Turn Right
		/*Turn right a specific number of steps*/
		void turnRight( int32_t steps );

		//Turn right tank style
		/*Turn right with both wheels moving opposite directions*/
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
		const uint16_t rightTurnStepAmount = 435;
		const uint16_t leftTurnStepAmount = 420;
		const int rightTankTurnStepAmount = 290;
		const int leftTankTurnStepAmount = 270;
		void setLeftSpeed( uint8_t speed );
		void setRightSpeed( uint8_t speed );
		void takeRightStep();
		void takeLeftStep();

	private:
		IntervalTimer motorTimer;
		IntervalTimer rightMotorTimer;
		IntervalTimer leftMotorTimer;
		uint32_t interval;
		static uint32_t leftSpeed;
		static uint32_t rightSpeed;
};

#endif 

extern Motors motorInterrupt;
