#include "Claw.h"
#include "Pivot.h"
#include <Servo.h>
String instruction;

Claw claw;
Pivot twist;
Pivot lean;
Pivot height;

void setup() {
  Serial.begin(9600);
  claw.init(6, 70, 60, 100);
  twist.init(11, 90, 20, 140);
  lean.init(10, 100, 60, 140);
  height.init(9, 80, 20, 100);
  reset();
}

void loop() {

  instruction = Serial.readString();

  if (instruction != "") {
    String firstArg = getArg(instruction, 1);
    String secondArg = getArg(instruction, 2);
    String thirdArg = getArg(instruction, 3);
    
    Pivot pivot;
    if (secondArg == "twist") {
        pivot = twist;
    }
    else if (secondArg == "lean") {
        pivot = lean;
    }
    else if (secondArg == "height") {
        pivot = height;
    }
    
    if (firstArg == "set") {
      pivot.setValue(thirdArg.toInt());
    }
    
    if (firstArg == "more") {
      pivot.more();
    }
    
    if (firstArg == "less") {
      pivot.less();
    }
    
    if (firstArg == "claw") {
      if (secondArg == "open") {
        claw.openUp();
      }
      else if (secondArg == "close") {
        claw.closeUp();  
      }
    }  
    
    if (firstArg == "reset") {
      reset();
    }

    Serial.println("L:" + String(lean.readValue()) + " H:" + String(height.readValue()) + " T:" + String(twist.readValue())  + " C:"+ String(claw.readValue()));
  }

  delay(1000);
}

String getArg(String instruction, int num) {
  int splitIndex = 0;
  int i;
  for (i=1; i<num; i++) {
    splitIndex = instruction.indexOf(' ', splitIndex+1);
    if (splitIndex == -1) {
      return "";
    }
  }
  int splitEnd = instruction.indexOf(' ', splitIndex+1);
  if (i > 1) {
    splitIndex = splitIndex+1; 
  }
  return instruction.substring(splitIndex, splitEnd);
}

void reset() {
  lean.reset();
  height.reset();
  twist.reset();
  claw.reset(); 
}

