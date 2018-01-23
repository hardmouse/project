#include "SoftwareSerial.h"
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(12, 11); // RX, TX

const int seg[] = {3,5,6,9};
const int sNum = 4;
void setup() {
  Serial.begin(9600);
  mp3_set_serial (mySerial);
  mp3_set_volume (20);
  mp3_play (8); //init sound
  for(int i=0; i<=sNum; i++){
    pinMode(seg[i], OUTPUT);
    digitalWrite(seg[i], LOW);
    delay(10);
  }
}

void loop() {
  mp3_play (1);
  delay(100);
  for(int i=0; i<=sNum; i++){
    digitalWrite(seg[i], HIGH);
    delay(50);
  }
  delay(3000);
  mp3_play (3);
  delay(1000);
  mp3_play (4);
  delay(1000);
  mp3_play (2);
  delay(1000);
  for(int i=sNum; i>=0; i--){
    digitalWrite(seg[i], LOW);
    delay(50);
  }
  delay(3000);
}
