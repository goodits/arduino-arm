#ifndef Motor_h
#define Motor_h

#include "Arduino.h"
#include <Servo.h>

class Motor {
  public:
    
    void init(int pin, int default_value, int min_safe, int max_safe) {
       motor.attach(pin); 
       motor_default_value = default_value;
       motor_max_safe = max_safe;
       motor_min_safe = min_safe;
    }
    
    void smoothMove(int new_value) {
      int current_value = motor.read();
      Serial.println("n:" + String(new_value) + " max:" + String(motor_max_safe) +" min:" + String(motor_min_safe));
      if (new_value > motor_max_safe) {
         new_value = motor_max_safe;
      }
      else if (new_value < motor_min_safe) {
        new_value = motor_min_safe;
      }   
    
     Serial.println("v:" + String(new_value));
     if (new_value > current_value) {
        while (new_value > current_value) {
          current_value = current_value + 2;
          motor.write(current_value);
          delay(50);
        }
      }
      else {
        while (new_value < current_value) {
          current_value = current_value - 2;
          motor.write(current_value);
          delay(50);
        }
      }
      Serial.println("got finish move");
    }
    
    void quickMove(int new_value) {
      motor.write(new_value);
      delay(50);
    }
    
    void toMax() {
       smoothMove(motor_max_safe);
    }
    
    void toMin() {
       smoothMove(motor_min_safe);
    }
    
    void reset() {
      quickMove(motor_default_value);
    }
    
    int readValue() {
      return motor.read();
    }
    
    int motor_max_safe;
    int motor_min_safe;
    int motor_default_value;
    
  private:
    Servo motor;
      
};

#endif
