#include <Servo.h>
Servo myServos[12];
int servoPins[12] = {2,3,4,5,6,7,8,9,10,11,12,13};
int pinCount = 12;
int brightness = 80;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    myServos[thisPin].attach(servoPins[thisPin]);
  }
}

void loop() {
  Serial.println(brightness);
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    myServos[thisPin].write(brightness);
  }
  brightness = brightness + fadeAmount;

  if (brightness == 80 || brightness == 100) {
    fadeAmount = -fadeAmount ;
  }
  delay(50);
}

