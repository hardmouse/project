#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(5, 3); // RX, TX

int clashComp = 0;
const int blade=13;
const int clash=A3;
void setup() {
  pinMode(blade,OUTPUT);
  pinMode(clash,INPUT);
  Serial.begin(9600);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);	//set softwareSerial for DFPlayer-mini mp3 module 
  mp3_set_volume (15);
}

void loop() {  
  int val = analogRead(clash);
  int comVal = abs(clashComp - val);
  if(comVal>500){
    Serial.println(val);
    mp3_play (5);
    delay(3000);
  }else{
    mp3_stop ();
  }
  comVal = val;
  delay(10);
}
