/*	2014-01-07 by lisper <leyapin@gmail.com>
 *	control mp3 module by seirial
 *	use mp3TF.h	
 *	test on UNO
 */

#include <mp3TF.h>

mp3TF mp3tf = mp3TF ();

const int xpin = A1;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A3;                  // z-axis (only on 3-axis models)
float cx,cy,cz;
float ox,oy,oz;
int one = 0, two = 0, three = 0;
boolean appear1 = false;
//
void setup () {
  mp3tf.init (&Serial);
  Serial.begin (9600);
  //Serial1.begin (9600);
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
  analogReference(DEFAULT);
}
void playSound (int snd, int dely=1000){
  mp3tf.play (snd);
  ox=cx;
  oy=cy;
  oz=cz;
  delay(2000);
}
//
void loop() {
  int x = analogRead(xpin);
  delay(1); 
  int y = analogRead(ypin);
  delay(1); 
  int z = analogRead(zpin);
  float zero_G = 1000;//512.0; 
  float scale = 2;//102.3;
  //
  cx=((float)x - zero_G)/scale;
  cy=((float)y - zero_G)/scale;
  cz=((float)z - zero_G)/scale;
  int dist = sqrt((ox-cx)*(ox-cx)+(oy-cy)*(oy-cy)+(oz-cz)*(oz-cz));
  if(dist>10){
    //Serial.print(dist);
    Serial.print("\t");
    if(!appear1){
      one=1;
      Serial.print(one);
      appear1=true;
    }else{
      //Serial.print("slash");
      one=2;
      Serial.print(one);
    }
    delay(100);
  }else{
    appear1=false;
    one=0;
    Serial.print(one);
  }
  Serial.print("\t");
  if(one==2 && two==2 && three==2){
    one=0;
    two=0;
    three=0;
    Serial.print("SWINGED");
    playSound(12,1500);
  }else if(one==0){
    if(two==2 && three==1){
      Serial.print("HITTED");
      playSound(1,1500);
    }else if(two==1){
      Serial.print("HITTED");
      playSound(2,1500);
    }else if(three==2 && two==2){
      Serial.print("SWINGED");
      playSound(11,1500);
    }
  }
  /*
  if(dist>20){
   playSound(5,1500);
   }else if(dist>18){
   Serial.print("xxxxxxx");
   playSound(4,1500);
   }else if(dist>15){
   Serial.print("x");
   playSound(3,1500);
   }else if(dist>10){
   Serial.print("x");
   playSound(2,1500);
   }else if(dist>8){
   Serial.print("x");
   playSound(1,1500);
   }else{
   Serial.print("____________");
   //playSound(6,3550);
   }
   */
  Serial.print("\n");
  ox=cx;
  oy=cy;
  oz=cz;
  three=two;
  two=one;
  //playSound(6,3550);
  delay(50);
}

/****************************************************************
 *		mp3TF mp3tf = mp3TF ();
 *	UNO:
 *		Serial.begin (9600);
 *		mp3tf.init (&Serial);
 *	LEONARDO:
 *		Serial1.begin (9600);
 *		mp3tf.init (&Serial1);
 *	
 *	function:
 *		mp3tf.play ();		play once
 *		mp3tf.play (1);		play first
 *		mp3tf.play (3);		play third
 *		mp3tf.pause ();		pause
 *		mp3tf.stop ();		stop
 *		mp3tf.next ();		next
 *		mp3tf.previous ();	previous
 *****************************************************************/



