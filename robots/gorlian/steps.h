#define servoNum 11

int currentPos[11];
int targetPos[11];
int moveSpeed = 5000;
int pos = 0;

int divStep = 10;
char val;

const int startPin = 2;
int totalCount=0;

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int eyePin = 11;

Servo myservo[servoNum];

int initPos[]={35,145,120,60,85,98,90,80,100,80,100};
int servoPin[]={2,3,4,5,6,7,8,9,10,12,13};

void loopLight(){
  analogWrite(eyePin, brightness);
  brightness = brightness + fadeAmount;
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }
}
void moveServo(int sNum1 , int sNum2 , int sNum3 , int sNum4 , int sNum5 , int sNum6 , int sNum7 , int sNum8 , int sNum9 , int sNum10 , int sNum11){
  int targetPos[]={sNum1,sNum2,sNum3,sNum4,sNum5,sNum6,sNum7,sNum8,sNum9,sNum10,sNum11};
  //int Pos[]={sPos1,sPos2,sPos3,sPos4,sPos5,sPos6,sPos7,sPos8,sPos9,sPos10,sPos11};
  int div[11];
  for(int i=0; i<servoNum;i++){
    //targetPos[i] = Pos[i];
    div[i] = (targetPos[i] - currentPos[i])/divStep;
  }
  for(int i=0; i<divStep; i++){
    for(int j=0; j<servoNum; j++){
      currentPos[j] = currentPos[j]+div[j];
      myservo[j].write(currentPos[j]);
      /*
      Serial.print("Ser:");
      Serial.print(j);
      Serial.print(":");
      Serial.print(currentPos[j]);
      Serial.println("__");
      */
      delayMicroseconds(moveSpeed);
      loopLight();
    }
  }
}
void standby(){
  moveSpeed = 5000;
  moveServo(initPos[0],initPos[1],initPos[2],initPos[3],initPos[4],initPos[5],initPos[6],initPos[7],initPos[8],initPos[9],initPos[10]);
  //moveServo(initPos[0]-60,initPos[1]+60,initPos[2]+80,initPos[3]-80,initPos[4],initPos[5],initPos[6],initPos[7],initPos[8],initPos[9],initPos[10]);
}

void standby2(){
  moveSpeed = 6000;
  moveServo(initPos[0]-25,initPos[1]+25,initPos[2]-60,initPos[3]+60,initPos[4],initPos[5],initPos[6],initPos[7]-20,initPos[8]+20,initPos[9]-20,initPos[10]+20);
}
