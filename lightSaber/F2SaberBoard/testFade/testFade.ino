#include "SoftwareSerial.h"
#include "BY8x0116P.h"
BY8x0116P myPlayer;

const int seg[] = {3,5,6,9};
const int sNum = 4;
int brightness = 0;
int fadeAmount = 5;

void setup() {
  myPlayer.init(2);
  for(int i=0; i<=sNum; i++){
    pinMode(seg[i], OUTPUT);
    digitalWrite(seg[i], LOW);
    delay(10);
  }
}

void loop() {
  for(int i=0; i<=sNum; i++){
    pinMode(seg[i], OUTPUT);
    analogWrite(seg[i], brightness);
    delay(10);
  }
  brightness = brightness + fadeAmount;
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
    myPlayer.playFile(1, 30);
  }
  delay(30);
}
