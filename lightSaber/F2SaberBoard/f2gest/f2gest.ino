#include "SoftwareSerial.h"
#include "BY8x0116P.h"
BY8x0116P myPlayer;

const int indLED = 7;
const int button = 8;

const int seg[] = {3,5,6,9};
const int sNum = 4;

boolean saberMode = false;

void setup() {
  Serial.begin(9600);
  pinMode(indLED, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(indLED, HIGH);
  digitalWrite(button, HIGH);
  for(int i=0; i<=sNum; i++){
    pinMode(seg[i], OUTPUT);
    digitalWrite(seg[i], LOW);
    delay(10);
  }
  myPlayer.init(4);
  digitalWrite(indLED, LOW);
}

void loop() {
  if(digitalRead(button)==0){
    if(!saberMode){
      Serial.println("SABER ON");
      digitalWrite(indLED, HIGH);
      saberON();
    }else if(saberMode){
      Serial.println("SABER OFF");
      digitalWrite(indLED, LOW);
      saberOFF();
    }
  }else{
    Serial.println("UNPRESSED");
  }
}
void saberON(){
  saberMode = true;
  myPlayer.playFile(1, 30);
  delay(100);
  for(int i=0; i<=sNum; i++){
   digitalWrite(seg[i], HIGH);
    delay(50);
  }
  delay(3000);
}

void saberOFF(){
  saberMode = false;
  myPlayer.playFile(2, 30);
  delay(1000);
  for(int i=sNum; i>=0; i--){
    digitalWrite(seg[i], LOW);
    delay(50);
  }
  delay(3000);
}
