#include <TimedAction.h>
#include <Servo.h> 
#include "myVariables.h"
#include "preFunctions.h"

void setup() {
  Serial.begin(9600);
  initMe();
}

void loop() {
  if(digitalRead(j_up)==0 && digitalRead(j_right)==0){
    moveTo(5);
  }else if(digitalRead(j_right)==0 && digitalRead(j_down)==0){
    moveTo(6);
  }else if(digitalRead(j_down)==0 && digitalRead(j_left)==0){
    moveTo(7);
  }else if(digitalRead(j_left)==0 && digitalRead(j_up)==0){
    moveTo(8);
  }else if(digitalRead(j_up)==0){
    moveTo(1);
  }else if(digitalRead(j_down)==0){
    moveTo(2);
  }else if(digitalRead(j_left)==0){
    moveTo(3);
  }else if(digitalRead(j_right)==0){
    moveTo(4);
  }else{
    moveTo(0);
  }
  
  
  if(digitalRead(j_right)==0){
    
  }
  if(digitalRead(j_left)==0){
    
  }
  checkHeadLight();
  checkFlashLight();
  checkBreak
  Light();
  checkLightL();
  checkLightR();
  delay(100);
}
