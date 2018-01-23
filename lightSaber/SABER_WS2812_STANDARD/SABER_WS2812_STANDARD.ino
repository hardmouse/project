#include <FastLED.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

#define LED_PIN     9
#define COLOR_ORDER GRB
#define CHIPSET     WS2812
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
int colorCyc = 0;
int buttonHoldTime = 0;
int buttonUnholdTime = 0;
int fadeAmount = 5;
int standBrightness = 0;
boolean buttonHold = false;
boolean buttonEnable = false;
int saberMode = 1; // 1.standby, 2.saber on. 3.saber off.
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
  gPal = HeatColors_p;
  mySerial.begin (9600);
  Serial.begin(9600);
  mp3_set_serial (mySerial);
  mp3_set_volume (20);
  delay(1000);
  mp3_play (43);
  delay(300); // sanity delay
}

void loop(){
  /*
  Serial.print("\t VIB:");
  Serial.print(vibVal);
  Serial.print("\t Mode:");
  Serial.print(saberMode);
  Serial.print("\t holdTime:");
  Serial.println(buttonHoldTime);
  */
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
  if(saberMode ==3){
    if(vibTemp>100){
      vibCount++;
      loopyLoop=0;
      Serial.println("W");
      //delay(1500);
    }else if(vibTemp>10){
      vibCount++;
      loopyLoop=0;
      Serial.println("C");
      //delay(1500);
    }else{
      //vibCount = 0;
    }
  }
  /*
    Serial.print(vibCount);
    Serial.print("\t:\t");
    Serial.println(vibTemp);
    */
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
    if(buttonUnholdTime<=500){
      buttonUnholdTime++;
    }
  }
  if(buttonHold == false && buttonHoldTime > 10 && buttonHoldTime < 1000){
    if(saberMode==1){
      saberMode=2;
      buttonHoldTime=0;
      buttonUnholdTime=0;
    }
    if(saberMode==3 && buttonHoldTime > 10 && buttonHoldTime < 500){
      loopyLoop=0;
      colorCyc++;
      if(colorCyc>=6){
        colorCyc=0;
      }
      if(colorCyc==0){
        gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
      }else if(colorCyc==1){
        gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::White);
      }else if(colorCyc==2){
        gPal = CRGBPalette16( CRGB::Black, CRGB::Green, CRGB::White);
      }else if(colorCyc==3){
        gPal = CRGBPalette16( CRGB::Black, CRGB::Orange, CRGB::Magenta, CRGB::LightPink);
      }else if(colorCyc==4){
        gPal = CRGBPalette16( CRGB::Black, CRGB::PaleVioletRed, CRGB::LightSkyBlue);
      }else if(colorCyc==5){
        gPal = CRGBPalette16( CRGB::Black, CRGB::Yellow, CRGB::Green, CRGB::White);
      }else if(colorCyc==6){
        gPal = CRGBPalette16( CRGB::Red, CRGB::OrangeRed, CRGB::Red);
      }
      playOpen(colorCyc);
      buttonHoldTime=0;
      buttonUnholdTime=0;
    }
  }
  if(saberMode ==3 && buttonHold == true && buttonHoldTime > 90){
    buttonHoldTime=0;
    buttonUnholdTime=0;
    saberMode = 4;
  }
  if(buttonHold == false && buttonHoldTime >= 100){
    buttonHoldTime=0;
    buttonUnholdTime=0;
  }
}
void playLoop(int snd){
  switch (snd) {
    case 0:
      mp3_play (10);
      break;
    case 1:
      mp3_play (24);
      break;
    case 2:
      mp3_play (17);
      break;
    case 3:
      mp3_play (31);
      break;
    case 4:
      mp3_play (38);
      break;
    case 5:
      mp3_play (3);
      break;
    default:
      // nothing yet
    break;
  }
  delay(300);
}
void playClose(int snd){
  switch (snd) {
    case 0:
      mp3_play (9);
      break;
    case 1:
      mp3_play (23);
      break;
    case 2:
      mp3_play (16);
      break;
    case 3:
      mp3_play (30);
      break;
    case 4:
      mp3_play (37);
      break;
    case 5:
      mp3_play (2);
      break;
    default:
      // nothing yet
    break;
  }
  delay(300);
}
void playOpen(int snd){
  switch (snd) {
    case 0:
      mp3_play (8);
      break;
    case 1:
      mp3_play (22);
      break;
    case 2:
      mp3_play (15);
      break;
    case 3:
      mp3_play (29);
      break;
    case 4:
      mp3_play (36);
      break;
    case 5:
      mp3_play (1);
      break;
    default:
      // nothing yet
    break;
  }
  delay(300);
}
void standby(){
  analogWrite(LED_BTN, standBrightness);
  standBrightness = standBrightness + fadeAmount;
  if (standBrightness == 0 || standBrightness == 255) {
    fadeAmount = -fadeAmount ;
  }
  
  int ranPick = random(44,10000);
  if(ranPick<59){
    mp3_play (ranPick);
    delay(2000);
  }else{
     Serial.println("nothing");
  }
  
  delay(1);
}
void saberOFF(){
  playClose(colorCyc);
  delay(1000);
  for(int i = NUM_LEDS-1; i >= 0; i--) {
    leds[i] = CRGB::Black;
    FastLED.show();
  }
  delay(1000);
  saberMode=1;
}
void saberON(){
  //mp3_play (1);
  playOpen(colorCyc);
  loopyLoop=0;
  //delay(1200); // wait for sound
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;
    FastLED.show();
  }
  digitalWrite(LED_BTN, LOW);
  saberMode=3;
}
void saberONing(){
  digitalWrite(LED_BTN, HIGH);
  if(loopyLoop >=180){
    playLoop(colorCyc);//mp3_play (3);
    loopyLoop=0;
  }
  loopyLoop++;
  //Serial.println(colorCyc);
  random16_add_entropy( random());
  Fire2012WithPalette();
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}
#define COOLING  45
// Default 120, suggested range 50-200.
#define SPARKING 90


void Fire2012WithPalette(){
  static byte heat[NUM_LEDS];
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
    for( int j = 0; j < NUM_LEDS; j++) {
      byte colorindex = scale8( heat[j], 240);
      leds[j] = ColorFromPalette( gPal, colorindex);
    }
}

