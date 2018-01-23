#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(3, 2); // RX, TX
int defaultLED = 13;
int clashComp = 0;
int brightness = 200;    // how bright the LED is
int fadeAmount = 5; 
const int blade=11;
const int clash=A0;
void setup() {
  pinMode(defaultLED,OUTPUT);
  pinMode(blade,OUTPUT);
  pinMode(clash,INPUT);
  Serial.begin(9600);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);	//set softwareSerial for DFPlayer-mini mp3 module 
  mp3_set_volume (20);
  digitalWrite(defaultLED,HIGH);
  delay(100);
  mp3_play (1);
  delay(3000);
}

void loop() {  
  int val = analogRead(clash);
  int comVal = abs(clashComp - val);
  Serial.println(brightness);
  mp3_play (3);
  analogWrite(blade, brightness);
  brightness = brightness + fadeAmount;
  if (brightness <= 200 || brightness >= 255) {
    fadeAmount = -fadeAmount ;
  }
  if (brightness == 255) {
    delay(500);
  }else{
  delay(10);
  }
  /*
  if(comVal>500){
    Serial.println(val);
    mp3_play (5);
    delay(3000);
  }else{
    mp3_stop ();
  }
  comVal = val;
  delay(10);
  */
}
