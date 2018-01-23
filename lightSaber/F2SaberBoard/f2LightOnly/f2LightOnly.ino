

const int seg[] = {3,5,6,9};
const int sNum = 4;
void setup() {
  for(int i=0; i<=sNum; i++){
    pinMode(seg[i], OUTPUT);
    digitalWrite(seg[i], LOW);
    delay(10);
  }
}

void loop() {
  for(int i=0; i<=sNum; i++){
   digitalWrite(seg[i], HIGH);
    delay(50);
  }
  delay(500);
  for(int i=sNum; i>=0; i--){
    digitalWrite(seg[i], LOW);
    delay(50);
  }
  delay(1000);
}
