const int xpin = A0;
const int ypin = A1;
void setup(){
  Serial.begin(9600);
}
void loop(){
  int xx = analogRead(xpin)/10-26;
  int yy = analogRead(ypin)/10-26;
  Serial.print("X:");
  Serial.print("\t");
  Serial.print(xx);
  Serial.print("\t");
  Serial.print("Y:");
  Serial.println(yy);
}
