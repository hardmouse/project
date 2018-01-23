const int LmotorPin1 = 3;
const int LmotorPin2 = 4;
const int LenablePin = 5;
const int RenablePin = 6;
const int RmotorPin1 = 7;
const int RmotorPin2 = 8;
const int ledPin = 13;
void setup() {
  // set all the other pins you're using as outputs:
  pinMode(LmotorPin1, OUTPUT);
  pinMode(LmotorPin2, OUTPUT);
  pinMode(LenablePin, OUTPUT);
  pinMode(RmotorPin1, OUTPUT);
  pinMode(RmotorPin2, OUTPUT);
  pinMode(RenablePin, OUTPUT);
  digitalWrite(LenablePin, HIGH);
  digitalWrite(RenablePin, HIGH);
  pinMode(ledPin, OUTPUT);
}
void loop() {
    digitalWrite(ledPin, HIGH);
    digitalWrite(LmotorPin1, LOW);
    digitalWrite(LmotorPin2, HIGH);
    digitalWrite(RmotorPin1, LOW);
    digitalWrite(RmotorPin2, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    digitalWrite(LmotorPin1, HIGH);
    digitalWrite(LmotorPin2, LOW);
    digitalWrite(RmotorPin1, HIGH);
    digitalWrite(RmotorPin2, LOW);
    delay(1000);
    digitalWrite(ledPin, HIGH);
    digitalWrite(LmotorPin1, LOW);
    digitalWrite(LmotorPin2, HIGH);
    digitalWrite(RmotorPin1, HIGH);
    digitalWrite(RmotorPin2, LOW);
    delay(1000);
    digitalWrite(ledPin, LOW);
    digitalWrite(LmotorPin1, HIGH);
    digitalWrite(LmotorPin2, LOW);
    digitalWrite(RmotorPin1, LOW);
    digitalWrite(RmotorPin2, HIGH);
    delay(1000);
}
