const int xpin = A7;
const int ypin = A6;
const int zpin = A4;
const int buzzpin=9;
const int lightpinR=3;
const int lightpinG=5;
const int lightpinB=6;
int brightness = 110;
int fadeAmount = 10;
void setup(){
  Serial.begin(9600);
  pinMode(buzzpin, OUTPUT);
  pinMode(lightpinR, OUTPUT);
  pinMode(lightpinG, OUTPUT);
  pinMode(lightpinB, OUTPUT);
}
void loop(){
  analogWrite(lightpinR, brightness);
  analogWrite(lightpinG, brightness);
  analogWrite(lightpinB, brightness);
  brightness = brightness + fadeAmount;
  
  //Serial.println(brightness);
  if (brightness == 110 || brightness == 250) {
    fadeAmount = -fadeAmount ; 
  }
  
  int xx = abs(analogRead(xpin));
  int yy = abs(analogRead(ypin));
  int zz = abs(analogRead(zpin));
  int val = sqrt(xx*xx+yy*yy);
  
  //analogWrite(lightpin, val);
  swing(val*val,8);//2nd val is better in range 5~10
  
  Serial.print("X:");
  Serial.print("\t");
  Serial.print(xx);
  Serial.print("Z:");
  Serial.print("\t");
  Serial.print(zz);
  Serial.print("\t");
  Serial.print("Y:");
  Serial.println(yy);
  
}

void swing(unsigned char volum, unsigned char delayT){
  analogWrite(buzzpin, volum);
  delay(delayT);
  analogWrite(buzzpin, 0);
  delay(delayT);
}
