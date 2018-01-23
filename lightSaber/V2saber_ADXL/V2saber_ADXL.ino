const int xpin = A0;                  // x-axis of the accelerometer
const int ypin = A1;                  // y-axis
const int zpin = A2;                  // z-axis (only on 3-axis models)
//
int Xcurr,Ycurr,Zcurr,Xb4,Yb4,Zb4,DisCurr,Disb4;
int sampleDelay = 100;   //number of milliseconds between readings
void setup()
{
  // initialize the serial communications:
  Serial.begin(9600);
  //
  //Make sure the analog-to-digital converter takes its reference voltage from
  // the AREF pin
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
  Xcurr=0;
  Ycurr=0;
  Zcurr=0;
  Xb4=0;
  Yb4=0;
  Zb4=0;
}
void loop()
{
  int x = analogRead(xpin);
  //
  //add a small delay between pin readings.  I read that you should
  //do this but haven't tested the importance
  delay(1);
  //
  int y = analogRead(ypin);
  //
  //add a small delay between pin readings.  I read that you should
  //do this but haven't tested the importance
  delay(1);
  //
  int z = analogRead(zpin);
  //
  //zero_G is the reading we expect from the sensor when it detects
  //no acceleration.  Subtract this value from the sensor reading to
  //get a shifted sensor reading.
  float zero_G = 512.0;
  //
  //scale is the number of units we expect the sensor reading to
  //change when the acceleration along an axis changes by 1G.
  //Divide the shifted sensor reading by scale to get acceleration in Gs.
  float scale = 102.3;
  //
  Xcurr=((float)x - zero_G) / scale*100;
  Ycurr=((float)y - zero_G) / scale*100;
  Zcurr=((float)z - zero_G) / scale*100;
  /*
  Serial.print(Xcurr);
  Serial.print("\t");
  //
  Serial.print(Ycurr);
  Serial.print("\t");
  //
  Serial.print(Zcurr);
  Serial.print("\n");
  //
  // delay before next reading:
  */
  int tempX = abs(Xb4-Xcurr)*abs(Xb4-Xcurr);
  int tempY = abs(Yb4-Ycurr)*abs(Yb4-Ycurr);
  int tempZ = abs(Zb4-Zcurr)*abs(Zb4-Zcurr);
  DisCurr = sqrt(tempX+tempY+tempZ);
  Serial.print(DisCurr);
  Serial.print("\n");
  delay(sampleDelay);
  
  Xb4=Xcurr;
  Yb4=Ycurr;
  Zb4=Zcurr;
}

