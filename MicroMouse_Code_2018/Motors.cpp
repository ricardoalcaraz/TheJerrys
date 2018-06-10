#include "Motors.h"

// Right Motor
const uint8_t STEP1 = 4; 
const uint8_t DIR1 = 6;
const uint8_t EN1 = 20;

// Left Motor
const uint8_t STEP2 = 5; 
const uint8_t DIR2 = 7;
const uint8_t EN2 = 21;


Motors::Motors() {
}

void Motors::init(){
    pinMode(STEP1, OUTPUT);
    pinMode(DIR1, OUTPUT);
    pinMode(STEP2, OUTPUT);
    pinMode(DIR2, OUTPUT);
    pinMode(EN1, OUTPUT);
    pinMode(EN2, OUTPUT);
    turnOff();
}

void Motors::leftForward(uint16_t steps, double speed){
    turnOn();
    digitalWrite(DIR1 , LOW);
    for (int i=0; i<steps; i++){
        digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );             
        delay(speed);
    }
    turnOff();
}
void Motors::rightForward(uint16_t steps, double speed){
    turnOn();
    digitalWrite(DIR2 , HIGH);
    for (int i=0; i<steps; i++){  
        digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );   
        delay(speed);
    }
    turnOff();
}
void Motors::backward(uint16_t steps){
    turnOn();
    digitalWrite(DIR1 , HIGH);
    digitalWrite(DIR2 , LOW);
    for (int i=0; i<steps; i++){
        digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );          
        digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );   
        delay(5);
    }
    turnOff();
}
void Motors::tankLeft(uint16_t steps){
    turnOn();
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, LOW);
    for (int i=0; i<steps; i++){
        digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
        digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
        delay(5) ;
    }    
    turnOff();
}
void Motors::tankRight(uint16_t steps){
    turnOn();
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
    for (int i=0; i<steps; i++){
        digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
        digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
        delay(5) ;
    }    
    turnOff();
}

void Motors::uTurn(uint16_t steps){
    turnOn();
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, LOW);
    for (int i=0; i<steps; i++){
        digitalWrite( STEP1, digitalRead(STEP1) ^ 1 );
        digitalWrite( STEP2, digitalRead(STEP2) ^ 1 );
        delay(5) ;
    }    
    turnOff();
}

void Motors::turnOn(){
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, LOW);
}

void Motors::turnOff(){
    digitalWrite(EN1, HIGH);
    digitalWrite(EN2, HIGH);
}
