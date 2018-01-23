//This is an example of how you would control 1 stepper

#include <AccelStepper.h>
String dir = "left";
int motorSpeed = 4800; //maximum steps per second (about 3rps / at 16 microsteps)
int motorAccel = 80000; //steps/second/second to accelerate

int motorDirPin = 8; //digital pin 2
int motorStepPin = 9; //digital pin 3

int frontPin=10;
int endPin=11;
//set up the accelStepper intance
//the "1" tells it we are using a driver
AccelStepper stepper(1, motorStepPin, motorDirPin);
void setup(){
  Serial.begin(9600);
  stepper.setMaxSpeed(motorSpeed);
  stepper.setSpeed(motorSpeed);
  stepper.setAcceleration(motorAccel);

  //stepper.moveTo(64000); //move 32000 steps (should be 10 rev)
  pinMode(frontPin, INPUT);
  pinMode(endPin, INPUT);
  digitalWrite(frontPin, HIGH);
  digitalWrite(endPin, HIGH);
}

void loop(){
  if(digitalRead(frontPin)==LOW){
    dir="right";
    stepper.moveTo(stepper.currentPosition()-96000);
  }else if(digitalRead(endPin)==LOW){
    dir="left";
    stepper.moveTo(stepper.currentPosition()+96000);
  }
  //Serial.println(dir);
  
  //if stepper is at desired location
  if (stepper.distanceToGo() == 0){
    if(digitalRead(frontPin)==LOW){
      dir="right";
      stepper.moveTo(stepper.currentPosition()-96000);
    }else if(digitalRead(endPin)==LOW){
      dir="left";
      stepper.moveTo(stepper.currentPosition()+96000);
    }
  }
  //these must be called as often as possible to ensure smooth operation
  //any delay will cause jerky motion
  stepper.run();
}

