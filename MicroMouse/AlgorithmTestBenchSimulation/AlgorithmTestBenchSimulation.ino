String directions;
int stepCounter;
void setup() {
  Serial.begin(9600);

  Serial.println("-----SOLVING FIRST TIME-------");
  Serial.println("turn L");
  directions.concat('L');
  stepCounter+=50;
  clearCounter(directions, stepCounter);
  Serial.println(directions);
  Serial.println(stepCounter);
  isGoal(directions,stepCounter);

  Serial.println("turn U");
  directions.concat('U');
  stepCounter+=50;  
  clearCounter(directions, stepCounter);
  optimize(directions);
  Serial.println(directions);
  
  Serial.println("turn L");
  directions.concat('L');
  stepCounter+=50;  
  clearCounter(directions, stepCounter);
  optimize(directions);
  Serial.println(directions);
  Serial.println(stepCounter);  
  isGoal(directions,stepCounter);
  
  Serial.println("turn U");
  directions.concat('U');
  stepCounter+=50;  
  clearCounter(directions, stepCounter);  
  optimize(directions);
  Serial.println(directions);
  Serial.println(stepCounter);  
  isGoal(directions,stepCounter);
  
  Serial.println("turn L");
  directions.concat('L');
  stepCounter+=50;  
  clearCounter(directions, stepCounter);  
  optimize(directions);
  Serial.println(directions);
  Serial.println(stepCounter);  
  isGoal(directions,stepCounter);
  
  Serial.println("Turn R");
  directions.concat('R');
  stepCounter+=50;  
  clearCounter(directions, stepCounter);  
  optimize(directions);
  Serial.println(directions);
  Serial.println(stepCounter);  
  isGoal(directions,stepCounter);

  Serial.println("Turn U");
  directions.concat('U');
  stepCounter+=50;  
  clearCounter(directions, stepCounter);  
  optimize(directions);
  Serial.println(directions);
  Serial.println(stepCounter);  
  isGoal(directions,stepCounter);

  Serial.println("Turn R");
  directions.concat('R');
  stepCounter+=50;  
  clearCounter(directions, stepCounter);  
  optimize(directions);
  Serial.println(directions);
  Serial.println(stepCounter);  
  isGoal(directions,stepCounter);


  Serial.println("Turn R");
  directions.concat('R');
  stepCounter+=50;  
  clearCounter(directions, stepCounter);  
  optimize(directions);
  Serial.println(directions);
  Serial.println(stepCounter);  
  isGoal(directions,stepCounter);

  Serial.println("Turn R");
  directions.concat('R');
  stepCounter+=50;  
  clearCounter(directions, stepCounter);  
  optimize(directions);
  Serial.println(directions);
  Serial.println(stepCounter);  
  isGoal(directions,stepCounter);
  Serial.println("-------OPTIMIZED SOLVE------");

  
  recall(directions);
}

void loop() {
}

void optimize(String &directions) {
    String longer[10] = {"LUR","LUS","LUL","RUL","SUL","SUS"};
    String shorter[10] = {"U","R","S","U","R","U"};
    for (int count = 0; count <= sizeof(longer); count++){
      if (directions.endsWith(longer[count])){
        directions.replace(longer[count],shorter[count]);
      }
    }
}

void recall(String &directions) {
  for (int i = 0; i <= directions.length(); i++) {
    Serial.println(directions[i]);
  }
}

bool isGoal(String &directions, int &stepCount){
  if ( directions.endsWith("RRR") & (stepCount < 150) ){
    Serial.println("Found Goal");
    return true;
  }
  else{
    return false;
  }
}


void clearCounter(String &directions, int &stepCounter){
  if ( ! directions.endsWith("R")){
    stepCounter = 0;
  }
}

