//FIXME: make class later
const unsigned int STEP1 = 4; // Right Motor
const unsigned int STEP2 = 5; // Left Motor
const unsigned int DIR1 = 6;
const unsigned int DIR2 = 7;

void motor_init(){
        pinMode(STEP1, OUTPUT);
    pinMode(DIR1, OUTPUT);
    pinMode(STEP2, OUTPUT);
    pinMode(DIR2, OUTPUT);
}

void move_forward(int steps){
    digitalWrite(DIR1 , LOW);
    digitalWrite(DIR2 , HIGH);
    for (int i=0; i<steps; i++){
        digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );          
        digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );   
        delay(5);
    }
}
void move_backward(int steps){
    digitalWrite(DIR1 , HIGH);
    digitalWrite(DIR2 , LOW);
    for (int i=0; i<steps; i++){
        digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );          
        digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );   
        delay(5);
    }
}
void turn_tankleft(int steps){
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
    for (int i=0; i<steps; i++){
        digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
        digitalWrite( STEP1, digitalRead(STEP2) ^ 1 );
        delay(5) ;
    }    
}
void turn_tankright(int steps){
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, LOW);
    for (int i=0; i<steps; i++){
        digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
        digitalWrite( STEP1, digitalRead(STEP2) ^ 1 );
        delay(5) ;
    }    
}
// Use one of the tank turns with an increased amount of steps to U-turn (?)
