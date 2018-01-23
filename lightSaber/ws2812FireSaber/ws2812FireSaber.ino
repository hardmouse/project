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

// Fire2012 with programmable Color Palette
//
// This code is the same fire simulation as the original "Fire2012",
// but each heat cell's temperature is translated to color through a FastLED
// programmable color palette, instead of through the "HeatColor(...)" function.
//
// Four different static color palettes are provided here, plus one dynamic one.
// 
// The three static ones are: 
//   1. the FastLED built-in HeatColors_p -- this is the default, and it looks
//      pretty much exactly like the original Fire2012.
//
//  To use any of the other palettes below, just "uncomment" the corresponding code.
//
//   2. a gradient from black to red to yellow to white, which is
//      visually similar to the HeatColors_p, and helps to illustrate
//      what the 'heat colors' palette is actually doing,
//   3. a similar gradient, but in blue colors rather than red ones,
//      i.e. from black to blue to aqua to white, which results in
//      an "icy blue" fire effect,
//   4. a simplified three-step gradient, from black to red to white, just to show
//      that these gradients need not have four components; two or
//      three are possible, too, even if they don't look quite as nice for fire.
//
// The dynamic palette shows how you can change the basic 'hue' of the
// color palette every time through the loop, producing "rainbow fire".

CRGBPalette16 gPal;
SoftwareSerial mySerial(2, 3); // RX, TX

int loopyLoop = 0; // loop for timer
const int LED = 13;
const int vib = A1;
const int button = A0;
int vibVal = 0;
int colorCyc = 0;
int buttonTime = 0;
int buttonHold = 0;
int saberMode = 1; //1.standby, 2.saber on. 
boolean buttonEnable = false;
void setup() {
  delay(200); // sanity delay
  pinMode(vib, INPUT); 
  pinMode(LED, OUTPUT); 
  pinMode(button, INPUT); 
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  digitalWrite(LED, HIGH);
  digitalWrite(button, HIGH);
  // This first palette is the basic 'black body radiation' colors,
  // which run from black to red to bright yellow to white.
  gPal = HeatColors_p;
  
  // These are other ways to set up the color palette for the 'fire'.
  // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
  
  // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);
  
  // Third, here's a simpler, three-step gradient, from black to red to white
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);    //set softwareSerial for DFPlayer-mini mp3 module 
                       // delay 10ms to set volume
  mp3_set_volume (20);
  delay(1000);
  //mp3_play (1);
  delay(300); // sanity delay
}

void loop(){
  if(saberMode==1){
    standby();
  }else if(saberMode==2){
    saberON();
  }else if(saberMode==3){
    saberOFF();
  }
}
void standby(){
  if(digitalRead(button)==0 && !buttonEnable){
    buttonEnable=true;
    mp3_play (1);
    saberMode=2;
  }
  if(digitalRead(button)==1){
    buttonEnable=false;
  }
  /*
  for(int i = NUM_LEDS-1; i >= 0; i--) {
    leds[i] = CRGB::Black;
    FastLED.show();
  }
  */
}
void saberOFF(){
  for(int i = NUM_LEDS-1; i >= 0; i--) {
    /*
    // Set the i'th led to red 
    leds[i] = CRGB::Red;
    // Show the leds
    */
    // now that we've shown the leds, reset the i'th led to black
    leds[i] = CRGB::Black;
    FastLED.show();
    // Wait a little bit before we loop around and do it again
    //delay(1);
    if(i==120){
      mp3_play (2);
    }
  }
  delay(1000);
  saberMode=1;
}
void saberON(){
  if(loopyLoop >=180){
    mp3_play (3);
    loopyLoop=0;
  }
  //Serial.println(loopyLoop);
  loopyLoop++;
  Serial.print(analogRead(vib));
  Serial.print(":");
 
  if(digitalRead(button)==0){
    buttonTime++;
    if(buttonTime>200){
      buttonTime=0;
      saberMode=3;
    }
  }
  if(digitalRead(button)==1){
    buttonEnable=false;
    buttonTime = 0;
  }
  // if button pressed
  if(digitalRead(button)==0 && !buttonEnable){
    buttonTime=0;
    buttonEnable=true;
    loopyLoop=0;
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
    colorCyc++;
    mp3_play (1);
    delay(300); // sanity delay
  }
  Serial.println(colorCyc);
  // Add entropy to random number generator; we use a lot of it.
  random16_add_entropy( random());

  // Fourth, the most sophisticated: this one sets up a new palette every
  // time through the loop, based on a hue that changes every time.
  // The palette is a gradient from black, to a dark color based on the hue,
  // to a light color based on the hue, to white.
  //
  //   static uint8_t hue = 0;
  //   hue++;
  //   CRGB darkcolor  = CHSV(hue,255,192); // pure hue, three-quarters brightness
  //   CRGB lightcolor = CHSV(hue,128,255); // half 'whitened', full brightness
  //   gPal = CRGBPalette16( CRGB::Black, darkcolor, lightcolor, CRGB::White);


  Fire2012WithPalette(); // run simulation frame, using palette colors
  
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}


// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
//// 
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation, 
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking. 
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100 
#define COOLING  45

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 90


void Fire2012WithPalette(){
// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( heat[j], 240);
      leds[j] = ColorFromPalette( gPal, colorindex);
    }
}

