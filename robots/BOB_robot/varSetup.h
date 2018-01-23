Servo L_U;
Servo R_U;
Servo L_B;
Servo R_B;
int pos = 90;
int posLU = pos;
int posRU = pos-4;
int posLB = pos+6;
int posRB = pos;

int delayTime = 150;

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

