#include <Servo.h>
#include "Arduino.h"
#include "steps.h"


void setup() { 
  pinMode(eyePin, OUTPUT);
  Serial.begin(9600);
  for(totalCount=0; totalCount<servoNum;totalCount++){
    Serial.println(totalCount);
    myservo[totalCount].attach(servoPin[totalCount]);
    currentPos[totalCount] = initPos[totalCount];
  }
  delay(500);
  standby();
}

void breath(){
  moveSpeed = 8000;
  moveServo(initPos[0]-10,initPos[1]+10,initPos[2]+10,initPos[3]-10,initPos[4],initPos[5],initPos[6],initPos[7],initPos[8],initPos[9],initPos[10]);
  moveServo(initPos[0],initPos[1],initPos[2],initPos[3],initPos[4],initPos[5],initPos[6],initPos[7]+5,initPos[8]-5,initPos[9]+5,initPos[10]-5);
}

void forward(){
  moveSpeed = 6000;
  moveServo(initPos[0],initPos[1],initPos[2],initPos[3],initPos[4],initPos[5],initPos[6],initPos[7],initPos[8],initPos[9],initPos[10]);
  moveServo(initPos[0],initPos[1],initPos[2]+20,initPos[3]-20,initPos[4],initPos[5],initPos[6],initPos[7],initPos[8],initPos[9],initPos[10]);
}
void forward2(){
  moveSpeed = 6000;
  moveServo(initPos[0]-10,initPos[1]+10,initPos[2]+10,initPos[3]-10,initPos[4],initPos[5],initPos[6],initPos[7],initPos[8],initPos[9]-10,initPos[10]+10);
  moveServo(initPos[0]+20,initPos[1]-20,initPos[2]-30,initPos[3]+30,initPos[4],initPos[5],initPos[6],initPos[7]-25,initPos[8]+25,initPos[9]+35,initPos[10]-35);
}
void loop() {
  standby();
  //breath();
  //forward();
  //digitalWrite(eyePin, HIGH);
  
} 
