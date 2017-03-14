#ifndef Pivot_h
#define Pivot_h

#include "Arduino.h"
#include "Motor.h"

class Pivot {

  Motor motor;
  const static int stepValue = 20;
  
  public:
    
    void init(int pin, int default_value, int max_safe, int min_safe)  { 
      motor.init(pin, default_value, max_safe, min_safe);
    }
    
    void setValue(int value) {
      motor.smoothMove(value);
    }
    
    void more() {
      motor.smoothMove(readValue() + stepValue); 
    }
    
    void less() {
      motor.smoothMove(readValue() - stepValue); 
    }
    
    void reset() {
      motor.reset();
    }
    
    int readValue() {
      return motor.readValue();
    }
};

#endif
