#include <NewPing.h>
#include <Stepper.h>

// Constant Variables
#define STEPS 200 //Steps per revolution
#define SONAR_NUM 3 //Number of sensors
#define MAX_DISTANCE 200 //Max Distance we want to measure
#define PING_INTERVAL 33//Milliseconds between pings


//Green black red blue from left to right
//Stepper Pins
#define stepperRight 11
#define stepperRightDir 12
#define stepperLeft 21
#define stepperLeftDir 20

//UltraSonic Sensor Pins
#define ECHO_1 5
#define TRIGGER_1 6
#define ECHO_2 17
#define TRIGGER_2 16
#define ECHO_3 2
#define TRIGGER_3 3

//Initializing Sonar Pins
NewPing sonar[SONAR_NUM]{
  NewPing(ECHO_1, TRIGGER_1, MAX_DISTANCE),
  NewPing(ECHO_2, TRIGGER_2, MAX_DISTANCE),
  NewPing(ECHO_3, TRIGGER_3, MAX_DISTANCE),
};

unsigned long pingTimer[SONAR_NUM]; //When each sensor pings
unsigned int cm[SONAR_NUM]; //Store ping distances
int currentSensor = 0; //Which Sensor is active


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Initializing motor output pins
  pinMode(stepperRight, OUTPUT);
  pinMode(stepperLeft, OUTPUT);
  //Initialize Timers for Sensors
  pingTimer[0] = millis() + 75; //First ping start in ms
  for( int i = 1; i < SONAR_NUM; i++){
    pingTimer[i] = pingTimer[i-1] + PING_INTERVAL;
  }
  
}

void loop() {
  for(int i = 0; i < SONAR_NUM; i++){
    if(millis() >=pingTimer[i]){
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;
      if(i == 0 && currentSensor == SONAR_NUM - 1){
       oneSensorCycle(); // Do something with results.
      }
      sonar[currentSensor].timer_stop();
      currentSensor = i;
      cm[currentSensor] = 0;
      sonar[currentSensor].ping_timer(echoCheck);
    }
  }
  // Rest of code goes here

  
  moveForward();
  
}

void moveForward(){
  //digitalWrite(stepperRightDir, HIGH);
  digitalWrite(stepperLeftDir, HIGH);
  for(int i = 0; i < STEPS; i++){
      digitalWrite(stepperRight, HIGH);
      digitalWrite(stepperLeft, HIGH);
      digitalWrite(stepperRight, LOW);
      digitalWrite(stepperLeft, LOW);
  }
  
}

void echoCheck() { // If ping echo, set distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}
 
void oneSensorCycle() { // Do something with the results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.print("cm ");
  }
  Serial.println();
}
