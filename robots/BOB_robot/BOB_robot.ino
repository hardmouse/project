#include <Servo.h> 
#include <NewPing.h>
#include "varSetup.h"
#include "move.h"

void setup() { 
  L_U.attach(6);
  R_U.attach(9);
  L_B.attach(10);
  R_B.attach(11);
    L_U.write(posLU);
    R_U.write(posRU);
    L_B.write(posLB);
    R_B.write(posRB);
  Serial.begin(115200);
    delay(delayTime);
} 
 
void loop() {
  dist();
  
  //backward(delayTime);
  //turnleft(100);
} 
