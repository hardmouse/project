int speedMax = 250;
int speedMin = 5000;
int speedy = 250;
int PotH = 0;
int PotV = 0;
String dir = "left";
const int motorDirPin = 9; //digital pin 2
const int motorStepPin = 8; //digital pin 3
const int endPin=7;
const int frontPin=6;
int potPinH = A0;
int potPinV = A1;
void setup() {
  Serial.begin(9600);
  pinMode(motorDirPin, OUTPUT);
  pinMode(motorStepPin, OUTPUT);
  digitalWrite(motorDirPin, LOW);
  digitalWrite(motorStepPin, LOW);
  pinMode(frontPin, INPUT);
  pinMode(endPin, INPUT);
  digitalWrite(frontPin, HIGH);
  digitalWrite(endPin, HIGH);
}

void loop() {
  PotH = analogRead(potPinH);
  PotH = map(PotH, 0, 1023, -100, 100);
  PotV = analogRead(potPinV);
  PotV = map(PotV, 0, 1023, 500, -500);
  if(PotV>50){
    if(speedy > speedMax){
      speedy-=PotV/10;
      //Serial.print("++++++++++++++++");
    }
  }else if(PotV<-50){
    if(speedy < speedMin){
      speedy-=PotV/10;
      //Serial.print("----------------");
    }
  }
  if(speedy > speedMin){
    speedy=speedMin;
  }
  if(speedy < speedMax){
    speedy=speedMax;
  }
  /*
  Serial.print(PotV);
  Serial.print(":");
  Serial.println(speedy);
  */
  if(digitalRead(frontPin)==LOW){
    dir="right";
  }else if(digitalRead(endPin)==LOW){
    dir="left";
  }
  digitalWrite(motorStepPin, HIGH);
  delayMicroseconds(speedy); 
  digitalWrite(motorStepPin, LOW); 
  delayMicroseconds(speedy);
  if(dir=="right"){
    digitalWrite(motorDirPin, LOW);
  }else{
    digitalWrite(motorDirPin, HIGH);
  }
}


