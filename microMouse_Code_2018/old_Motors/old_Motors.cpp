#include "Motors.h"

//Initializing external function so ISR can work properly
static void motorISR();

static void leftMotorISR();

static void rightMotorISR();

//Pinout for the stepper motors
const uint8_t EN1 = 20;
const uint8_t EN2 = 21;
const uint8_t STEP1 = 4;
const uint8_t STEP2 = 5;
const uint8_t DIR1 = 6;
const uint8_t DIR2 = 7;

uint32_t Motors::speed = 50;
uint16_t stepsPerRevolution = 250;
uint32_t Motors::leftSpeed = 50;
uint32_t Motors::rightSpeed = 50;

Motors::Motors( ) {

}

//Initialize all the motor functions
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
	digitalWrite( DIR1, LOW  );
	digitalWrite( DIR2, HIGH );
	motorTimer.priority( 10 );
	rightMotorTimer.priority( 10 );
	leftMotorTimer.priority( 10 );
	setSpeed(100);
	setRightSpeed(52);
	setLeftSpeed(50);
}

//Enables the motor so they can move
void Motors::go( ) {
	digitalWrite( EN1, LOW );
	digitalWrite( EN2, LOW );
}

//set the speed to an arbitrary value from
void Motors::setSpeed( uint8_t speed ){
	speed = constrain( speed, 1,255 );
	this->speed = map(speed,1,255,3500,1000);
	motorTimer.update(speed);
}

void Motors::setRightSpeed( uint8_t speed ) {
	speed = constrain( speed, 1,255 );
	this->rightSpeed = map(speed,1,255,3500,1000);
	rightMotorTimer.update(speed);
}

void Motors::setLeftSpeed( uint8_t speed ) {
	speed = constrain( speed, 1,255 );
	this->leftSpeed = map(speed,1,255,3500,1000);
	leftMotorTimer.update(speed);
}

//Stops the motors from moving
void Motors::stop ( ) {
  	digitalWrite( EN1, HIGH );
  	digitalWrite( EN2, HIGH );
	motorTimer.end();
	leftMotorTimer.end();
	rightMotorTimer.end();
}

//Continuosly move forward
void Motors::moveForward( ) {
	digitalWrite( DIR1, LOW  );
	digitalWrite( DIR2, HIGH );
	leftMotorTimer.begin( leftMotorISR, leftSpeed );
	rightMotorTimer.begin( rightMotorISR, rightSpeed);
	go();
}

//Turn left
void Motors::turnLeft( ) {
	noInterrupts();
	stop();
	digitalWrite( DIR1, LOW  );
	digitalWrite( DIR2, HIGH );
	go();
	if( speed > 40 ) {
		uint32_t temp = this->speed;
		uint8_t tempSpeed = 40; 
		for( int i = 0; i < leftTurnStepAmount; i++ ) {
			digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
			delayMicroseconds(speed);
			if( (i) % 5 == 0 && tempSpeed < speed ) {
				tempSpeed++;
				setSpeed( tempSpeed );
			}
		}
		this->speed = temp;
	} else {
		for( uint32_t i = 0; i < leftTurnStepAmount; i++ ) {
			digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );	
		}
	}
	stop();
	interrupts();
}

//Turn left
void Motors::tankTurnLeft( ) {
	noInterrupts();
	stop();
	digitalWrite( DIR1, LOW  );
	digitalWrite( DIR2, LOW );
	go();
	if( speed > 30 ) {
		uint32_t temp = this->speed;
		uint8_t tempSpeed = 30; 
		for( int i = 0; i < leftTankTurnStepAmount; i++ ) {
			digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
			digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
			delayMicroseconds(speed);
			if( (i) % 15 == 0 && tempSpeed < speed ) {
				tempSpeed++;
				setSpeed( tempSpeed );
			}
		}
		setSpeed( temp );
	} else {
		for( uint32_t i = 0; i < leftTankTurnStepAmount; i++ ) {
			digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
			digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
			delayMicroseconds(speed);

		}
	}
	stop();
	interrupts();
}

//Turn right tank style 
void Motors::tankTurnRight( ) {
	noInterrupts();
	stop();
	digitalWrite( DIR1, HIGH );
	digitalWrite( DIR2, HIGH );
	go();
	if( speed > 30 ) {
		uint32_t temp = this->speed;
		uint8_t tempSpeed = 30; 
		for( int i = 0; i < rightTankTurnStepAmount; i++ ) {
			digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
			delayMicroseconds(speed);
			digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
			if( (i) % 15 == 0 && tempSpeed < speed ) {
				tempSpeed++;
				setSpeed( tempSpeed );
			}
		}
		this->speed = temp;
	} else {
		for( uint32_t i = 0; i < rightTankTurnStepAmount; i++ ) {
			digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
			delayMicroseconds(speed);
			digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
		}
	}	
	stop();
	interrupts();
	
}

//Turn right 
void Motors::turnRight( ) {
	noInterrupts();
	stop();
	digitalWrite( DIR1, LOW  );
	digitalWrite( DIR2, HIGH );
	go();
	if( speed > 30 ) {
		uint32_t temp = this->speed;
		uint8_t tempSpeed = 40; 
		for( int i = 0; i < rightTurnStepAmount; i++ ) {
			digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
			delayMicroseconds(speed);
			if( (i) % 5 == 0 && tempSpeed < speed ) {
				tempSpeed++;
				setSpeed( tempSpeed );
			}
			if( i%3==0 ) {
				digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
			}
		}
		this->speed = temp;
	} else {
		for( uint32_t i = 0; i < rightTurnStepAmount; i++ ) {
			digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );	
		}
	}
	digitalWrite( DIR1, LOW );
	digitalWrite( DIR2, LOW );
	delay(1);
	digitalWrite( DIR1, LOW  );
	digitalWrite( DIR2, HIGH );
	stop();
	interrupts();
}

//Turn right
/*Overloaded functions with options to turn right on a
 * pivot with only wheel*/
void Motors::turnRight( int32_t steps ) {
	noInterrupts(); //Disable interrupts for smooth operation

	/*If steps are negative then move the left wheel backward instead of forward*/
	if( steps < 0 ) {
		digitalWrite(DIR2, LOW);
	}else {
		digitalWrite(DIR2, HIGH);
	}
	go();	
	/*Take the aforementioned amount of steps*/
	for( int32_t i = 0; i < abs( steps) ; i++ ) {
		takeLeftStep();
		delayMicroseconds(speed);
	}
	stop();
	interrupts();
}

//Turn left
/*Overloaded functions with options to turn left on a
 * pivot with only wheel*/
void Motors::turnLeft( int32_t steps ) {
	noInterrupts(); //Disable interrupts for smooth operation

	/*If steps are negative then move the left wheel backward instead of forward*/
	if( steps < 0 ) {
		digitalWrite(DIR1, LOW);
	}else {
		digitalWrite(DIR1, LOW );
	}
	go();
	/*Take the aforementioned amount of steps*/
	for( int32_t i = 0; i < abs( steps ); i++ ) {
		takeRightStep();
		delayMicroseconds(speed);
	}
	stop();
	interrupts();
}

//Turn back right
/*Turn right on a backwards pivot*/
void Motors::turnBackRight() {
	noInterrupts();
	stop();
	digitalWrite( DIR1, LOW );
	digitalWrite( DIR2, LOW );
	go();
	if( speed > 30 ) {
		uint32_t temp = this->speed;
		uint8_t tempSpeed = 40; 
		for( int i = 0; i < rightTurnStepAmount; i++ ) {
			digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
			delayMicroseconds(speed);
			if( (i) % 5 == 0 && tempSpeed < speed ) {
				tempSpeed++;
				setSpeed( tempSpeed );
			}
		}
		this->speed = temp;
	} else {
		for( uint32_t i = 0; i < rightTurnStepAmount; i++ ) {
			digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );	
		}
	}
	stop();
	interrupts();
}

//Turn back left
/*Turn the motors on a backwards pivot*/
void Motors::turnBackLeft() {
	noInterrupts();
	stop();
	digitalWrite( DIR1, LOW );
	digitalWrite( DIR2, LOW );
	go();
	if( speed > 40 ) {
		uint32_t temp = this->speed;
		uint8_t tempSpeed = 40; 
		for( int i = 0; i < leftTurnStepAmount; i++ ) {
			digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
			delayMicroseconds(speed);
			if( (i) % 5 == 0 && tempSpeed < speed ) {
				tempSpeed++;
				setSpeed( tempSpeed );
			}
		}
		this->speed = temp;
	} else {
		for( uint32_t i = 0; i < leftTurnStepAmount; i++ ) {
			digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );	
		}
	}
	stop();
	interrupts();
}

//Move forward only a certain amount of steps
void Motors::moveForward( uint32_t steps ) {
	noInterrupts();
	stop();
	digitalWrite( DIR1, LOW  );
	digitalWrite( DIR2, HIGH );
	go();
	if( speed > 30 ) {
		uint32_t temp = this->speed;
		uint8_t tempSpeed = 30; 
		for( int i = 0; i < steps; i++ ) {
			digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
			delayMicroseconds(speed);
			digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
			if( (i) % 15 == 0 && tempSpeed < speed ) {
				tempSpeed++;
				setSpeed( tempSpeed );
			}
		}
		this->speed = temp;
	} else {
		for( uint32_t i = 0; i < steps*2; i++ ) {
			digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
			delayMicroseconds(speed);
			digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
		}
	}	
	stop();
	interrupts();
}

//Move Backward
/*Move backward continously through an interrupt service routine*/
void Motors::moveBackward( ) {
	stop();
	digitalWrite( DIR1, LOW );
	digitalWrite( DIR2, LOW );
	leftMotorTimer.begin( leftMotorISR, speed );
	rightMotorTimer.begin( rightMotorISR, speed);
	go();
}

//Move Backward
/*Move backward a certain amount of steps*/
void Motors::moveBackward( uint32_t steps ) {
	noInterrupts();
	stop();
	digitalWrite( DIR1, HIGH );
	digitalWrite( DIR2, LOW  );
	go();
	if( speed > 30 ) {
		uint32_t temp = this->speed;
		uint8_t tempSpeed = 30; 
		for( int i = 0; i < steps; i++ ) {
			digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
			delayMicroseconds(speed);
			digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
			if( (i) % 15 == 0 && tempSpeed < speed ) {
				tempSpeed++;
				setSpeed( tempSpeed );
			}
		}
		this->speed = temp;
	} else {
		for( uint32_t i = 0; i < steps*2; i++ ) {
			digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
			delayMicroseconds(speed);
			digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
		}
	}	
	stop();
	interrupts();
}

//Specially tuned function that will turn
//the robot 360 degrees
void Motors::turnAround( ) {
	noInterrupts();
	stop();
	digitalWrite( DIR1, LOW  );
	digitalWrite( DIR2, LOW );
	go();
	if( speed > 30 ) {
		uint32_t temp = this->speed;
		uint8_t tempSpeed = 30; 
		for( int i = 0; i < turnAroundSteps; i++ ) {
			digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
			delayMicroseconds(speed);
			digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
			if( (i) % 15 == 0 && tempSpeed < speed ) {
				tempSpeed++;
				setSpeed( tempSpeed );
			}
		}
		this->speed = temp;
	} else {
		for( uint32_t i = 0; i < turnAroundSteps; i++ ) {
			digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
			delayMicroseconds(speed);
			digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
		}
	}	
	stop();
	interrupts();
}

void Motors::takeAStep() {
	//Write a square wave to the two step pins to move
	//motors forward
	digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );//right motor
	digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );//left motor
}

void Motors::takeRightStep() {
	digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
}

void Motors::takeLeftStep() {
	digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
}

void Motors::test() {
    digitalWrite(STEP1,HIGH); // Enables the motor to move in a particular direction
    for(int x = 0; x < 200; x++) {
        digitalWrite(STEP1,HIGH); 
        delayMicroseconds(500); 
        digitalWrite(STEP1,LOW); 
        delayMicroseconds(500); 
    }      
    //digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
}

Motors motorInterrupt;

static void motorISR() {
	motorInterrupt.takeAStep();
}

static void leftMotorISR() {
	motorInterrupt.takeLeftStep();
}

static void rightMotorISR() {
	motorInterrupt.takeRightStep();
}
