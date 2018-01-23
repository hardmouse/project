#include <Servo.h> 
#include <NewPing.h>
#include <SoftwareSerial.h>
#include "steps.h"
SoftwareSerial Bt(0, 1); // RX, TX

int rightTime=0;

int state;
int flag=0; 

void setup(){
  Serial.begin(9600);

  pinMode(LED_T, OUTPUT);
  pinMode(LED_M, OUTPUT);
  pinMode(LED_B, OUTPUT);
  
  int ss = 2;
  for(int i=0; i<12; i++){
    myservo[i].attach(ss);
    ss++;
    if(12%i==0){
      digitalWrite(LED_T,HIGH);
    }else if(12%i==1){
      digitalWrite(LED_M,HIGH);
    }else if(12%i==2){
      digitalWrite(LED_B,HIGH);
    }
    delay(10);
    myservo[i].write(initPos[i]);
    currentPos[i]=initPos[i];
    if(12%i==0){
      digitalWrite(LED_T,LOW);
    }else if(12%i==1){
      digitalWrite(LED_M,LOW);
    }else if(12%i==2){
      digitalWrite(LED_B,LOW);
    }
    delay(10);
  }
} 
void goForward(){
  servPos6(1, initPos[1]+feetGait, 7, initPos[7]-feetGait, 9, initPos[9]+feetGait, 2, initPos[2]+walkingAdj-hipGait, 4, initPos[4]+hipGait, 10, initPos[10]-walkingAdj-hipGait);
  servPos6(0, initPos[0]-walkingAdj-hipGait, 6, initPos[6]+hipGait, 8, initPos[8]+walkingAdj-hipGait, 3, initPos[3]-feetGait, 5, initPos[5]+feetGait, 11, initPos[11]-feetGait);
  servPos6(1, initPos[1], 7, initPos[7], 9, initPos[9], 2, initPos[2]+walkingAdj+hipGait, 4, initPos[4]-hipGait, 10, initPos[10]-walkingAdj+hipGait);
  servPos6(0, initPos[0]-walkingAdj+hipGait, 6, initPos[6]-hipGait, 8, initPos[8]+walkingAdj+hipGait, 3, initPos[3], 5, initPos[5], 11, initPos[11]);
}

void goBackward(){
  servPos6(1, initPos[1]+feetGait, 7, initPos[7]-feetGait, 9, initPos[9]+feetGait, 2, initPos[2]+walkingAdj+hipGait, 4, initPos[4]-hipGait, 10, initPos[10]-walkingAdj+hipGait);
  servPos6(0, initPos[0]-walkingAdj+hipGait, 6, initPos[6]-hipGait, 8, initPos[8]+walkingAdj+hipGait, 3, initPos[3]-feetGait, 5, initPos[5]+feetGait, 11, initPos[11]-feetGait);
  servPos6(1, initPos[1], 7, initPos[7], 9, initPos[9], 2, initPos[2]+walkingAdj-hipGait, 4, initPos[4]+hipGait, 10, initPos[10]-walkingAdj-hipGait);
  servPos6(0, initPos[0]-walkingAdj-hipGait, 6, initPos[6]+hipGait, 8, initPos[8]+walkingAdj-hipGait, 3, initPos[3], 5, initPos[5], 11, initPos[11]);
}

void turnLeft(){
  servPos6(1, initPos[1], 7, initPos[7], 9, initPos[9], 2, initPos[2]+hipGait, 4, initPos[4]+hipGait, 10, initPos[10]+hipGait);
  servPos6(0, initPos[0]-hipGait, 6, initPos[6]-hipGait, 8, initPos[8]-hipGait, 3, initPos[3], 5, initPos[5], 11, initPos[11]);
  servPos6(1, initPos[1]+feetGait, 7, initPos[7]-feetGait, 9, initPos[9]+feetGait, 2, initPos[2]-hipGait, 4, initPos[4]-hipGait, 10, initPos[10]-hipGait);
  servPos6(0, initPos[0]+hipGait, 6, initPos[6]+hipGait, 8, initPos[8]+hipGait, 3, initPos[3]-feetGait, 5, initPos[5]+feetGait, 11, initPos[11]-feetGait);
}
  
void turnRight(){
  servPos6(1, initPos[1]+feetGait, 7, initPos[7]-feetGait, 9, initPos[9]+feetGait, 2, initPos[2]+hipGait, 4, initPos[4]+hipGait, 10, initPos[10]+hipGait);
  servPos6(3, initPos[3]-feetGait, 5, initPos[5]+feetGait, 11, initPos[11]-feetGait, 0, initPos[0]-hipGait, 6, initPos[6]-hipGait, 8, initPos[8]-hipGait);
  servPos6(1, initPos[1], 7, initPos[7], 9, initPos[9], 2, initPos[2]-hipGait, 4, initPos[4]-hipGait, 10, initPos[10]-hipGait);
  servPos6(3, initPos[3], 5, initPos[5], 11, initPos[11], 0, initPos[0]+hipGait, 6, initPos[6]+hipGait, 8, initPos[8]+hipGait);
}

void standby(){
  servPos6(0, initPos[0], 2, initPos[2], 4, initPos[4], 6, initPos[6], 8, initPos[8], 10, initPos[10]);
  servPos6(1, initPos[1], 3, initPos[3], 5, initPos[5], 7, initPos[7], 9, initPos[9], 11, initPos[11]);
}
void loop() {
  
  if(Serial.available() > 0){
    state = Serial.read();
    flag=0;
    Serial.println(state);
  }
  if (state == '0') {
    standby();
    if(flag == 0){
      Serial.println("Spider: standby");
      flag=1;
    }
  }else if (state == '1') {
    goBackward();
    if(flag == 0){
      Serial.println("Spider: backward");
      flag=1;
    }
  }else if (state == '2') {
    goForward();
    if(flag == 0){
      Serial.println("Spider: forward");
      flag=1;
    }
  }else if (state == '3') {
    turnLeft();
    if(flag == 0){
      Serial.println("Spider: turnLeft");
      flag=1;
    }
  }else if (state == '4') {
    turnRight();
    if(flag == 0){
      Serial.println("Spider: turnRight");
      flag=1;
    }
  }else{
    standby();
  }
  
}

