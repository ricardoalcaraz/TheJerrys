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
  void forward(uint16_t steps);

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


#endif
