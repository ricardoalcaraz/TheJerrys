/*
---------------------------Jerry the Micromouse------------------------------
	
	NOTES:
	Care has to be taken with the speed
	Motors use approximately 1A each at 100 rpm and .5A at 200 rpm
	150rpm is a good balance of speed and torque
	
	Functions available:
		moveForward(int number_of_steps);
		turnRight();
		turnLeft();
		turnAround();
		setSpeed(int speed);
		setTurnAngle(int angle_in_steps);
		setDebug(bool choice);
		setTurnSpeed(int turn_speed);
		initializeSwitches(int switch1, int switch2, int switch3, int switch4);
		readSwitches();


*/
#include "Arduino.h"
#include "Stepper.h"
#ifndef Jerry_h
#define Jerry_h



class Jerry {
	public:
		//Constructors
		Jerry(int steps_revolution, int motor1_1, int motor1_2, int motor1_3, int motor1_4, int motor2_1, int motor2_2, int motor2_3, int motor2_4);
		//void setSensors(int sensor_echo1, int sensor_trigger1, int sensor_echo2, int sensor_trigger2, int sensor_echo3, int sensor_trigger3);
		//void setSwitches(int switches[4]);
		void moveForward(int number_of_steps);
		void turnRight();
		void turnLeft();
		void turnAround();
		//set speed
		void setSpeed(int speed);
		//turn angle
		void setTurnAngle(int angle_in_steps);
		void setDebug(bool choice);
		void setTurnSpeed(int turn_speed);
		void initializeSwitches(int switch1, int switch2, int switch3, int switch4);
		int readSwitches();
		void initializeSensors(int pingRate, int echo1, int trigger1, int echo2, int trigger2, int echo3, int trigger3);
		int* getDistances();
		void setMaxDistance(int user_distance);




	private:
		//Motors
		Stepper _motorLeft;
		Stepper _motorRight;
		int _steps_per_revolution;
		int _speed;
		int _turnAngle;
		int _turnSpeed;
		int _motor1_1;
		int _motor1_2;
		int _motor1_3;
		int _motor1_4;
		int _motor2_1;
		int _motor2_2;
		int _motor2_3;
		int _motor2_4;
		void motorsOff();
		void leftMotorOff();
		void rightMotorOff();
		//Sensors
		int _pingRate;
		int _current_sensor;
		int _distance;
		int _duration;
		int _max_distance;
		void pingDistances();
		int pulseRight();
		int pulseLeft();
		int pulseMiddle();
		int _trigger1;
		int _echo1;
		int _trigger2;
		int _echo2;
		int _trigger3;
		int _echo3;
		int _sensor_distances[4];
		volatile int _volatile_left_distance;
		volatile int _volatile_right_distance;
		volatile int _volatile_middle_distance;
		//Switches
		int _switches[4];
		int _switch_value;
		//Debug Mode
		bool _debug;
		
};



#endif