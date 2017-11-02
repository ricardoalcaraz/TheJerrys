String directions;
int stepCounter;
void setup() {
  Serial.begin(9600);

  Serial.println("-----SOLVING FIRST TIME-------");
  Serial.println("turn L");
  directions.concat('L');
  directions = optimize(directions);
  Serial.println(directions);
  isGoal(directions,stepCounter);

  Serial.println("turn U");
  directions.concat('U');
  directions = optimize(directions);
  Serial.println(directions);
  
  Serial.println("turn L");
  directions.concat('L');
  directions = optimize(directions);
  Serial.println(directions);
  isGoal(directions,stepCounter);
  
  Serial.println("turn U");
  directions.concat('U');
  directions = optimize(directions);
  Serial.println(directions);
  isGoal(directions,stepCounter);
  
  Serial.println("turn L");
  directions.concat('L');
  directions = optimize(directions);
  Serial.println(directions);
  isGoal(directions,stepCounter);
  
  Serial.println("Turn R");
  directions.concat('R');
  directions = optimize(directions);
  Serial.println(directions);
  isGoal(directions,stepCounter);

  Serial.println("Turn R");
  directions.concat('R');
  directions = optimize(directions);
  Serial.println(directions);
  isGoal(directions,stepCounter);


  Serial.println("Turn R");
  directions.concat('R');
  directions = optimize(directions);
  Serial.println(directions);
  isGoal(directions,stepCounter);



  Serial.println("-------OPTIMIZED SOLVE------");
  recall(directions);
}

void loop() {
}

String optimize(String directions) {
    String longer[10] = {"LUR","LUS","LUL","RUL","SUL","SUS"};
    String shorter[10] = {"U","R","S","U","R","U"};
    for (int count = 0; count <= sizeof(longer); count++){
      if (directions.endsWith(longer[count])){
        directions.replace(longer[count],shorter[count]);
      }
    }
  return directions;
}

void recall(String directions) {
  for (int i = 0; i <= directions.length(); i++) {
    Serial.println(directions[i]);
  }
}

bool isGoal(String directions, int stepCount){
  if (directions.endsWith("RRR") & stepCount < 150){
    Serial.println("Found Goal");
    return true;
  }
  else{
    Serial.println("No Goal");
    return false;
  }

}

