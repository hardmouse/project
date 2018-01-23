const int xpin = A1;
const int ypin = A0;
const int buzzpin=9;
//const int testpin=5;
const int lightpin=3;
int brightness = 110;
int fadeAmount = 10;
void setup(){
  Serial.begin(9600);
  pinMode(buzzpin, OUTPUT);
  pinMode(lightpin, OUTPUT);
  //pinMode(testpin, OUTPUT);
}
void loop(){
  //analogWrite(testpin, brightness);
  analogWrite(lightpin, brightness);
  brightness = brightness + fadeAmount;
  
  Serial.println(brightness);
  if (brightness == 110 || brightness == 250) {
    fadeAmount = -fadeAmount ; 
  }
  
  int xx = abs(analogRead(xpin)/10-26);
  int yy = abs(analogRead(ypin)/10-26);
  int val = sqrt(xx*xx+yy*yy);
  
  //analogWrite(lightpin, val);
  swing(val*val,8);//2nd val is better in range 5~10
  /*
  Serial.print("X:");
  Serial.print("\t");
  Serial.print(xx);
  Serial.print("\t");
  Serial.print("Y:");
  Serial.println(yy);
  */
}

void swing(unsigned char volum, unsigned char delayT){
  analogWrite(buzzpin, volum);
  delay(delayT);
  analogWrite(buzzpin, 0);
  delay(delayT);
}
