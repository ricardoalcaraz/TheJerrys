// Constant Variables
#define STEPS 200 //Steps per revolution
const int max_distance = 6000; //Goes out to about 80cm. Since this reduces the amount of time spent until a pulse is recorded, it can essentially limit the distance it records
const int turn_angle = 50;  //Holds number or steps to swivel
int wallDistance = 10; //Threshold to determine if there is a wall or openings
int middleWallDistance = wallDistance + 2; //Threshold for middle sensor as it eats the wall, preventing a clean turn by allowing for extra clearance
String directions; //Stores directions
int stepCounter; //Tracks for the final goal
int goal_step_counter = 0; //Should be constantly at zero
char intersectionChoice; //Can either be (L)eft, (R)ight, (S)traight, or (U)turn
bool isIntersectionBoolean; //True if there is an intersection. If mouse can only turn left, right, or go back this counts as an intersection


// UltraSonic Sensor Pins
const int trigger1 = 7;
const int echo1 = 8;
const int trigger2 = 2;
const int echo2 = 3;
const int trigger3 = 4;
const int echo3 = 5;
//const int max_distance = 6000; //Goes out to about 80cm. Since this reduces the amount of time spent until a pulse is recorded, it can essentially limit the distance it records
double duration;
int distance;




void setup(){
    Serial.begin(9600);
    pinMode(trigger1, OUTPUT);
    pinMode(echo1, INPUT);
    pinMode(trigger2, OUTPUT);
    pinMode(echo2, INPUT);
    pinMode(trigger3, OUTPUT);
    pinMode(echo3, INPUT);
}

//----------------------------------------------------------//
//------------------MAIN------------------------------------//
//----------------------------------------------------------//
void loop() {
  getIntersection();
  delay(1500);
//    Serial.println(getIntersection());
//    delay(25);

}

//DOES NOT directly append paths to array, just check and turn. We don't want it to append anything otherwise solveOptimized() would constantly add letters
String getIntersection(){
  //Important Note: Must first check whether or not there is an intersection
  //                otherwise a hallway will count as a straight intersection
  
  int left_distance = pulseLeft();
  int middle_distance = pulseMiddle();
  int right_distance = pulseRight();
//  Serial.println("Left: " + (String) left_distance);
//  Serial.println("Middle: " + (String) middle_distance);
//  Serial.println("Right: " + (String) right_distance);
//  Serial.println();
  
  //Only need to check for a hallway, since that is the only time there is no intersection
  if( (middle_distance > middleWallDistance) and (left_distance < wallDistance) and (right_distance < wallDistance) ){
    Serial.println("NO INTERSECTION");
    return "NONE";
  }
  else{
    Serial.println("INTERSECTION");
    return "INTERSECTION";
  }

  /*
  //Using waterfall princniple of control flow statements. Priority: Left, straight, right, turn around
  
  if (left_distance > wallDistance) {
    return "L";
  }
  else if (middle_distance > middleWallDistance) {
    return "S";
  }
  else if (right_distance > wallDistance) {
    return "R";
  }
  else if  ((left_distance < wallDistance) and (middle_distance < middleWallDistance) and (right_distance < wallDistance)) {
    return "U";
  }
  else {
    return "X";
  }
  */
}


int pulseRight() {
  digitalWrite(trigger1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger1, LOW);

  //Read the echo pin
  duration = pulseIn(echo1, HIGH, max_distance);

  //Calculate distance
  distance = duration*0.034/2;

//  Serial.print("Right distance: "); Serial.println(distance);
  return distance;
}

int pulseLeft() {
  digitalWrite(trigger2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger2, LOW);

  //Read the echo pin
  duration = pulseIn(echo2, HIGH, max_distance);

  //Calculate distance
  distance = duration*0.034/2;

//  Serial.print("Left distance: "); Serial.println(distance);
  return distance;
}

int pulseMiddle() {
  digitalWrite(trigger3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger3, LOW);

  //Read the echo pin
  duration = pulseIn(echo3, HIGH, max_distance);

  //Calculate distance
  distance = duration*0.034/2;

//  Serial.print("Middle distance: "); Serial.println(distance);
  return distance;
}
