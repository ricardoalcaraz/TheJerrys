void test(){
     static uint8_t speed = 70;
    if( Serial.available() > 0 ){
        char incomingChar = Serial.read();
        switch (incomingChar) {
            case 'a':
                motors.turnLeft();
                Serial.println( "Turning left");
                break;
            case 'd':
                motors.turnRight();
                Serial.println( "Turning right");
                break;
            case 'x':
                motors.stop();
                break;
            case 'w':
                motors.moveForward(200);
                Serial.println( "Moving forward ");
                break;
      case 'c':
        motors.tankTurnLeft( );
        Serial.println("Turning left tank style");
        break;
      case 'q':
        motors.tankTurnRight( );
        Serial.println("Turning right tank style");
        break;
            case '+':
                speed+=10;
                motors.setSpeed(speed);
                Serial.print( "Current speed is now: "); Serial.println( speed );
                break;
            case '-':
                speed-=10;
                motors.setSpeed(speed);
                Serial.print( "Current speed is now: "); Serial.println( speed );
                break;
      case 't':
        while( sensors.getLeftDistance() < 5 ) {
          motors.moveForward(100);
        } 
        motors.moveForward(175);
        motors.turnLeft();
        break;
      case 'u':
        motors.turnAround();
        Serial.println("Turning around");
        break;
        }
        motors.stop();
    }

    Serial.print( "Right Distance: " ); Serial.println( sensors.getRightDistance() );
    Serial.print( "Left Distance: " ); Serial.println( sensors.getLeftDistance() );
    Serial.print( "Middle Distance: " ); Serial.println( sensors.getMiddleDistance() );
}

//Input: None
//Output: Intersection decision
char getIntersection(){
    String room = (String(sensors.getLeftDistance() < 5) +  String(sensors.getMiddleDistance() < 5) +  String(sensors.getRightDistance() < 5));
    if      (room == "100") return  'S';
    else if (room == "101") return NULL;
    else if (room == "110") return  'R';
    else if (room == "111") return  'U';
    else                    return  'L';
}


//Input: None
//Output: Boolean representing if there is an intersection
bool isIntersection(){
    if ( (sensors.getLeftDistance() < 5)   &&  
         (sensors.getMiddleDistance() > 5) && 
         (sensors.getRightDistance() < 5)  
        ) return false;
    else  return true;
}

//Input: directions
//Output: None
void optimize(String &directions) {
    String longer[10]  = {"LUR","LUS","LUL","RUL","SUL","SUS"};
    String shorter[10] = { "U" , "R" , "S" , "U" , "R" , "U" };
    for (int count = 0; count <= sizeof(longer); count++){
      if (directions.endsWith(longer[count])){
        directions.replace(longer[count],shorter[count]);
      }
    }
}

//Input: directions and motor step count
//Output: Boolean indicating if goal is found
bool isGoal(String &directions, int &stepCount){
  if ( directions.endsWith("RRR") & (stepCount <= 150) ){
    Serial.println("Found Goal");
    return true;
  }
  return false;
}
