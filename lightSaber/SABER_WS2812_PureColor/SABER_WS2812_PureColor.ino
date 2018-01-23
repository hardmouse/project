#include <FastLED.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

#define LED_PIN     9
#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define NUM_LEDS    123

#define BRIGHTNESS  255
#define FRAMES_PER_SECOND 120

CRGB leds[NUM_LEDS];

CRGBPalette16 gPal;
SoftwareSerial mySerial(2, 3); // RX, TX

int loopyLoop = 0; // loop for timer
const int LED = 13;
const int LED_BTN = 10;
const int vib = A1;
const int button = A0;
int vibCur = 0;
int vibBef = 0;
int vibCount = 0;
int vibVal = 0;
long currentColor = 0;
int buttonHoldTime = 0;
int fadeAmount = 1;
int standBrightness = 5;
boolean buttonHold = false;
boolean saberEngage = false;
int saberMode = 1; // 1.standby, 2.saber on. 3.saber off.
int brightnessON = 201;

void setup() {
  delay(200); // sanity delay
  pinMode(vib, INPUT); 
  pinMode(LED, OUTPUT); 
  pinMode(LED_BTN, OUTPUT); 
  pinMode(button, INPUT); 
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  randomSeed(analogRead(vib));
  digitalWrite(LED, HIGH);
  digitalWrite(LED_BTN, HIGH);
  digitalWrite(button, HIGH);
  mySerial.begin (9600);
  Serial.begin(9600);
  mp3_set_serial (mySerial);
  mp3_set_volume (20);
  mp3_play (8); //init sound
  for(int i = NUM_LEDS-1; i >= 0; i--) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  randomSeed(analogRead(vib));
  currentColor = random(0,255);
  delay(1500);
}

void loop(){
  checkButton();
  checkVib();
  if(saberMode==1){
    standby();
  }else if(saberMode==2){
    saberON();
  }else if(saberMode==3){
    saberONing();
  }else if(saberMode==4){
    saberOFF();
  }
}
void checkVib(){
  vibVal = analogRead(vib);
  vibCur = vibVal;
  int vibTemp = abs(vibBef - vibCur);
  if(saberMode ==3 && vibCount<2){
    if(vibTemp>210){
      playClash();
      for(int j=0; j<=3; j++){
        for(int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CHSV(currentColor,255,255);
        }
        FastLED.show();
        delay(10);
        for(int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CRGB::White;
        }
        FastLED.show();
        delay(10);
      }
      loopyLoop=350;
      //Serial.println("Wave");
    }else if(vibTemp>160){
      playWave();
      loopyLoop=400;
      //Serial.println("Clash"); 
    }else{
      //Serial.println("Normal");
      vibCount = 0;
    }
  }else if(saberMode==1){
    if(vibTemp>250){
      long tempRan = random(0,30);
      if(tempRan == 1){
        mp3_play (15);
      }else if(tempRan == 2){
        mp3_play (16);
      }else if(tempRan == 3){
        mp3_play (17);
      }else if(tempRan == 4){
        mp3_play (18);
      }else if(tempRan == 5){
        mp3_play (19);
      }else if(tempRan == 6){
        mp3_play (20);
      }else if(tempRan == 7){
        mp3_play (21);
      }else if(tempRan == 8){
        mp3_play (22);
      }
    }
  }
  vibBef = vibCur;
}
void checkButton(){
  // to determin the button mode and count the time
  // Read 0 = pressed, 1 = free/open/unpress
  if(digitalRead(button)==0){
    buttonHold = true;
    if(buttonHoldTime<=500){
      buttonHoldTime++;
    }
  }else{
    buttonHold = false;
  }
  if(buttonHold == false && buttonHoldTime > 10 && buttonHoldTime < 1000){
    if(saberMode==1){
      saberMode=2;
      buttonHoldTime=0;
    }
    if(saberMode==3 && buttonHoldTime > 10 && buttonHoldTime < 500){
      loopyLoop=490;
      randomSeed(analogRead(vib));
      currentColor = random(0,255);
      saberMode=2;
      buttonHoldTime=0;
    }
  }
  if(saberMode ==3 && buttonHold == true && buttonHoldTime > 90){
    buttonHoldTime=0;
    saberMode = 4;
  }
  if(buttonHold == false && buttonHoldTime >= 100){
    buttonHoldTime=0;
  }
}
void playWave(){
  long tempRan = random(0,2);
  vibCount++;
  if(tempRan==1){
    mp3_play (6);
  }else{
    mp3_play (7);
  }
}
void playClash(){
  long tempRan = random(0,2);
  vibCount++;
  if(tempRan==1){
    mp3_play (4);
  }else{
    mp3_play (5);
  }
}
void playLoop(){
  long tempRan = random(0,30);
  if(tempRan == 1){
    mp3_play (9);
  }else if(tempRan == 2){
    mp3_play (10);
  }else if(tempRan == 3){
    mp3_play (11);
  }else if(tempRan == 4){
    mp3_play (12);
  }else if(tempRan == 5){
    mp3_play (13);
  }else if(tempRan == 6){
    mp3_play (14);
  }else{
    mp3_play (3);
  }
}
void playClose(){
  mp3_play (2);
  delay(1200);
}
void playOpen(){
  mp3_play (1);
}
void standby(){
  analogWrite(LED_BTN, standBrightness);
  standBrightness = standBrightness + fadeAmount;
  if (standBrightness == 0 || standBrightness == 255) {
    fadeAmount = -fadeAmount ;
  }
  delay(1);
}
void saberOFF(){
  playClose();
  for(int i = NUM_LEDS-1; i >= 0; i--) {
    leds[i] = CRGB::Black;
    FastLED.show();
  }
  saberMode=1;
}
void saberON(){
  playOpen();
  delay(200);
  loopyLoop=490;
  //delay(1200); // wait for sound
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(currentColor,255,255);
    FastLED.show();
    delay(1);
  }
  digitalWrite(LED_BTN, LOW);
  saberMode=3;
  delay(500);
}
void saberONing(){
  digitalWrite(LED_BTN, HIGH);
  if(loopyLoop >= 500){
    playLoop();
    loopyLoop=0;
    vibCount=0;
  }
  loopyLoop++;
  brightnessON = brightnessON + fadeAmount;
  for(int i = 0; i<NUM_LEDS; i++){ 
    leds[i] = CHSV(currentColor,255,brightnessON);
  }
  FastLED.show();
  if (brightnessON == 150 || brightnessON == 255) {
    fadeAmount = -fadeAmount ;
  }
}
