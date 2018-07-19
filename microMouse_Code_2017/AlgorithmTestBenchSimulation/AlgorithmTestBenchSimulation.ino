String directions;
int stepCounter;
void setup() {
  Serial.begin(9600);
//  solveMaze1();
  solveMaze2();
}

void loop() {
}

void solveMaze1(){
  //Simulation path: LUL UL RRR
  //Expected optimized path: R RRR

  Serial.println("-----SOLVING FIRST TIME-------");
  makeTurn("L");
  makeTurn("U");
  makeTurn("L");
  makeTurn("U");
  makeTurn("L");
  makeTurn("R");
  makeTurn("R");
  makeTurn("R");
  makeTurn("R");
  
  Serial.println("-----Optimized SOLVE-------");
  recall(directions);
}

void solveMaze2(){
  //Simulation path of maze: RSR LLR ULL RLL RRR
  //Expected optimized path: RSR LSR LL RRR
  Serial.println("-----SOLVING FIRST TIME-------");
  makeTurn("R");
  makeTurn("S");
  makeTurn("R");
  
  makeTurn("L");
  makeTurn("L");
  makeTurn("R");
  
  makeTurn("U");
  makeTurn("L");
  makeTurn("L");
  
  makeTurn("R");
  makeTurn("L");
  makeTurn("L");
  
  makeTurn("R");
  makeTurn("R");
  makeTurn("R");
  
  Serial.println("-----Optimized SOLVE-------");
  recall(directions);
  
}


void makeTurn(String turn){
  Serial.println("Turned: " + turn);
  directions.concat(turn);
  optimize(directions);
  
  stepCounter+=50;
  if ( ! directions.endsWith("R")){
    stepCounter = 0;
  }
  
  Serial.println("Optimized Directions: " + directions);
  Serial.println(stepCounter);
  isGoal(directions,stepCounter);
  Serial.println();
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
    Serial.print(directions[i]);
  }
}

bool isGoal(String &directions, int &stepCount){
  if ( directions.endsWith("RRR") & (stepCount <= 150) ){
    Serial.println("Found Goal");
    return true;
  }
  return false;
}



