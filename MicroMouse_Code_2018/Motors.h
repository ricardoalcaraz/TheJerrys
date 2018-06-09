#ifndef Motors_h
#define Motors_h

#include "Arduino.h"

class Motors {
    public:
        // Constructor
        Motors();
        
        //Initialize
        void init();
        
        // forward
        /* Inputs: steps
        * Outputs: none
        * Moves robot FORWARD "steps" steps.*/
        void leftForward(uint16_t steps, uint16_t speed);
        void rightForward(uint16_t steps, uint16_t speed);
        // backward
        /* Inputs: steps
        * Outputs: none
        * Moves robot BACKWARD "steps" steps.*/
        void backward(uint16_t steps);
        
        // tankLeft
        /* Inputs: steps
        * Outputs: none
        * Rotates robot left "steps" steps.*/
        void tankLeft(uint16_t steps);
        
        // tankRight
        /* Inputs: steps
        * Outputs: none
        * Rotates robot right "steps" steps.*/
        void tankRight(uint16_t steps);

        void uTurn(uint16_t steps);

        void turnOn();
        void turnOff();

//        void s
};

#endif
