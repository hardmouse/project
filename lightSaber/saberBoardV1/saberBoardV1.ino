#include "SoftwareSerial.h"
#include "BY8x0116P.h"
BY8x0116P myPlayer;

int led1 = 3;
int led2 = 5;
int led3 = 6;
int led4 = 9;
int brightness = 0;
int fadeAmount = 5;

void setup() {
  myPlayer.init(2);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  analogWrite(led1, brightness);
  analogWrite(led2, brightness);
  analogWrite(led3, brightness);
  analogWrite(led4, brightness);
  brightness = brightness + fadeAmount;
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
    myPlayer.playFile(1, 30);
  }
  delay(30);
}
