#ifndef Claw_h
#define Claw_h

#include "Arduino.h"
#include "Motor.h"

class Claw {

  Motor motor;

  public:
    void init(int pin, int default_value, int max_safe, int min_safe)  { 
      motor.init(pin, default_value, max_safe, min_safe);
    }
    
    void setValue(int value) {
      motor.smoothMove(value);
    }
    
    void reset() {
      motor.reset();
    }
    
    void openUp() {
      motor.toMin(); 
    }
    
    void closeUp() {
      motor.toMax(); 
    }
    
    int readValue() {
      return motor.readValue();
    }
};

#endif
