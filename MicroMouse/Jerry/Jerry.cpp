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
#include "Jerry.h"
#include "Arduino.h"

//Constructor
Jerry::Jerry(int steps_per_revolution, int motor1_1, int motor1_2, int motor1_3, int motor1_4, int motor2_1, int motor2_2, int motor2_3, int motor2_4) : _motorLeft(Stepper(steps_per_revolution, motor1_1, motor1_2, motor1_3, motor1_4)), _motorRight(Stepper(steps_per_revolution, motor2_1, motor2_2, motor2_3, motor2_4)) {
		this->_motor1_1 = motor1_1;
		this->_motor1_2 = motor1_2;
		this->_motor1_3 = motor1_3;
		this->_motor1_4 = motor1_4;
		this->_motor2_1 = motor2_1;
		this->_motor2_2 = motor2_2;
		this->_motor2_3 = motor2_3;
		this->_motor2_4 = motor2_4;
		pinMode(this->_motor1_1, OUTPUT);
		pinMode(this->_motor1_2, OUTPUT);
		pinMode(this->_motor1_3, OUTPUT);
		pinMode(this->_motor1_4, OUTPUT);
		pinMode(this->_motor2_1, OUTPUT);
		pinMode(this->_motor2_2, OUTPUT);
		pinMode(this->_motor2_3, OUTPUT);
		pinMode(this->_motor2_4, OUTPUT);
		_steps_per_revolution = steps_per_revolution;
		//Initialize data members to a default value
		this->_speed = 150;
		_motorRight.setSpeed(_speed);
		_motorLeft.setSpeed(_speed);
		this->_turnSpeed = 95;
		this->_turnAngle = 140;
		this->_debug = false;
		this->_pingRate = 100000;
		this->_max_distance = 6000;
		motorsOff();
}

int* Jerry::getDistances(){
	_sensor_distances[0] = _volatile_left_distance;
	_sensor_distances[1] = _volatile_middle_distance;
	_sensor_distances[2] = _volatile_right_distance;
	return _sensor_distances;
}

void Jerry::setMaxDistance(int user_distance){
	_max_distance = user_distance;
}



//pulseRight
//Pulse right wall
//Inputs: None
//Outputs: Integer - wall distance in cm
int Jerry::pulseRight() {
	digitalWrite(_trigger1, LOW);
	delayMicroseconds(2);
	digitalWrite(_trigger1, HIGH);
	delayMicroseconds(10);
	digitalWrite(_trigger1, LOW);

	//Read the echo pin
	_duration = pulseIn(_echo1, HIGH, _max_distance);

	//Calculate distance
	_distance = _duration*0.034/2;
	if(_debug){
		Serial.print("Right distance: "); Serial.println(_distance);
	}
	return _distance;
}


//pulseLeft
//Pulse left wall
//Inputs: None
//Outputs: Integer - wall distance in cm
int Jerry::pulseLeft() {
	digitalWrite(_trigger2, LOW);
	delayMicroseconds(2);
	digitalWrite(_trigger2, HIGH);
	delayMicroseconds(10);
	digitalWrite(_trigger2, LOW);

	//Read the echo pin
	_duration = pulseIn(_echo2, HIGH, _max_distance);

	//Calculate distance
	_distance = _duration*0.034/2;
	if(_debug){
		Serial.print("Left distance: "); Serial.println(_distance);
	}
	return _distance;
}

//pulseMiddle
//Pulse middle wall
//Inputs: None
//Outputs: Integer - wall distance in cm
int Jerry::pulseMiddle() {
	digitalWrite(_trigger3, LOW);
	delayMicroseconds(2);
	digitalWrite(_trigger3, HIGH);
	delayMicroseconds(10);
	digitalWrite(_trigger3, LOW);

	//Read the echo pin
	_duration = pulseIn(_echo3, HIGH, _max_distance);

	//Calculate distance
	_distance = _duration*0.034/2;
	if(_debug){
		Serial.print("Middle distance: "); Serial.println(_distance);
	}
	return _distance;
}

void Jerry::pingDistances() {
	if( _current_sensor == 0){
	_volatile_right_distance = pulseRight();
	_current_sensor++;
	}
	else if(_current_sensor == 1){
	_volatile_middle_distance = pulseMiddle();
	_current_sensor++;
	}
	else if(_current_sensor == 2){
	_volatile_left_distance = pulseLeft();
	_current_sensor = 0;
	}
}

/*
	Initialize sensors
	Inputs: 6 Ints - echo and trigger pins
	Outputs: None
*/
IntervalTimer distanceChecker;
void Jerry::initializeSensors(int pingRate, int echo1, int trigger1, int echo2, int trigger2, int echo3, int trigger3){
	_current_sensor = 0;
	_pingRate = pingRate;
	_trigger1 = trigger1;
	_echo1 = echo1;
	_trigger2 = trigger2;
	_echo2 = echo2;
	_trigger3 = trigger3;
	_echo3 = echo3;
	pinMode(_trigger1, OUTPUT);
  	pinMode(_echo1, INPUT);
  	pinMode(_trigger2, OUTPUT);
  	pinMode(_echo2, INPUT);
  	pinMode(_trigger3, OUTPUT);
  	pinMode(_echo3, INPUT);
  	//distanceChecker.begin(&Jerry::pingDistances, 10000);
}



/*
	Initialize switches into inputs
	Inputs: Int- 4 switch positions
	Outputs: None
*/
void Jerry::initializeSwitches(int switch1, int switch2, int switch3, int switch4){
	if(_debug){
		Serial.println("Initializing switches");
	}
	_switches[0] = switch1;
	_switches[1] = switch2;
	_switches[2] = switch3;
	_switches[3] = switch4;
	for(int i = 0; i < 4; i++){
		pinMode(_switches[i], INPUT);
	}
}

/*
	Read and output integer value of 4 switches
	Input: None
	Output: Int- switch value
*/
int Jerry::readSwitches(){
	_switch_value = 0; //Must constantly reset switch count, otherwise it reaches rediculously large numbers //FIXED
	for (int i = 0; i < 4; i++) {
    	_switch_value += (int) digitalRead(_switches[i]) * (int) pow(2, i);
  	}
  	return _switch_value;
}

//Enable Debug Outputs
//Inputs: Boolean
//Outputs; None
void Jerry::setDebug(bool choice){
	this->_debug = choice;
	if(_debug){
		Serial.begin(9600);
	}
	else{
		Serial.end();
	}
}

//Set Turn Speed
//Inputs: Int - turn speed
//Outputs: None
void Jerry::setTurnSpeed(int turn_speed){
	this->_turnSpeed = turn_speed;
}

/*
	Set Speed of Bot
	Inputs: Int- speed
	Outputs: None
*/
void Jerry::setSpeed(int user_speed){
	this->_speed = user_speed;
	_motorLeft.setSpeed(_speed);
	_motorRight.setSpeed(_speed);
	if(_debug){
		Serial.print("Setting Speed to ");Serial.println(_speed);
	}
}

void Jerry::setTurnAngle(int turn_angle){
	this->_turnAngle = turn_angle;
}

//Pivot robot right
//Inputs: None
//Outputs: None
void Jerry::turnRight(){
	if(this->_debug){
		Serial.println("Turning Right");
	}
	_motorRight.setSpeed(_turnSpeed);
	_motorLeft.setSpeed(_turnSpeed);
	for(int i = 0; i < this->_turnAngle; i++){
    	_motorLeft.step(1);
    	//Skip half the steps since one wheel has to turn twice as long as the other
    	if(i%2 == 0){
    		_motorRight.step(1);
    	}
    	
	}
	_motorRight.setSpeed(_speed);
	_motorLeft.setSpeed(_speed);
  motorsOff();
}

//Pivot robot left
//Inputs: None
//Outputs: None
void Jerry::turnLeft(){
	if(this->_debug){
		Serial.println("Turning Left");
	}
	_motorRight.setSpeed(_turnSpeed);
	_motorLeft.setSpeed(_turnSpeed);
	for(int i = 0; i < this->_turnAngle; i++){
		//Skip half the steps since one wheel has to turn twice as long as the other
		_motorRight.step(-1);
		if(i%2 == 0){
			_motorLeft.step(-1);
    	}
    	
	}
	_motorRight.setSpeed(_speed);
	_motorLeft.setSpeed(_speed);
	motorsOff();
}

/*
	Turn bot around
	Inputs: None
	Outputs: None
*/
void Jerry::turnAround(){
	if(this->_debug){
		Serial.println("Turning Around");
	}
	_motorRight.setSpeed(_turnSpeed);
	_motorLeft.setSpeed(_turnSpeed);
	for(int i = 0; i < _steps_per_revolution; i++){
		//Skip half the steps since one wheel has to turn twice as long as the other
		_motorRight.step(-1);
		_motorLeft.step(-1);
    	
    	
	}
	_motorRight.setSpeed(_speed);
	_motorLeft.setSpeed(_speed);
	motorsOff();
}

//Turn left Motor Off
//Inputs: None
//Outputs: None
void Jerry::leftMotorOff(){
	digitalWrite(_motor2_1, LOW);
    digitalWrite(_motor2_2, HIGH);
    digitalWrite(_motor2_3, LOW);
    digitalWrite(_motor2_4, HIGH);
}

//Turn right Motor Off
//Inputs: None
//Outputs: None
void Jerry::rightMotorOff(){
	digitalWrite(_motor1_1, LOW);
    digitalWrite(_motor1_2, HIGH);
    digitalWrite(_motor1_3, LOW);
    digitalWrite(_motor1_4, HIGH);
}

//Turn Both Motors Off
//Inputs: None
//Outputs: None
void Jerry::motorsOff(){
	if(this->_debug){
		Serial.println("Turning Motors Off");
	}
	leftMotorOff();
	rightMotorOff();
}

/*
	Move the robot forward
	Inputs: int - number of steps
	Outputs: None
*/
void Jerry::moveForward(int steps){
	if(this->_debug){
		Serial.println("Moving Forward");
	}
	for(int i = 0; i < steps; i++){
    	_motorLeft.step(1);
    	_motorRight.step(-1);
  	}
  	motorsOff();
}

