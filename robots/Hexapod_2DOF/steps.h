#define LED_T  A0
#define LED_M  A1
#define LED_B  A2
Servo myservo[12];
int initPos[]={90,90,100,90,90,90,90,90,80,90,100,90};
int currentPos[12];
int targetPos[12];
int moveSpeed = 4;
int pos = 0;

char val;

int walkingAdj=30;
int feetGait=50;
int hipGait=25;

int myStep = 35;
int divStep = 10;

void servPos6(int sNum1, int sPos1, int sNum2, int sPos2, int sNum3, int sPos3, int sNum4, int sPos4, int sNum5, int sPos5, int sNum6, int sPos6){
  int Num[]={sNum1,sNum2,sNum3,sNum4,sNum5,sNum6};
  int Pos[]={sPos1,sPos2,sPos3,sPos4,sPos5,sPos6};
  int div[6];
  for(int i=0; i<6;i++){
    targetPos[Num[i]] = Pos[i];
    div[i] = (Pos[i] - currentPos[Num[i]])/divStep;
  }
  for(int i=0; i<divStep; i++){
    for(int j=0; j<6; j++){
      currentPos[Num[j]] = currentPos[Num[j]]+div[j];
      myservo[Num[j]].write(currentPos[Num[j]]);
      int randNumber = random(0, 6);
        if(randNumber==0){
          digitalWrite(LED_T,LOW);
        }else if(randNumber==1){
          digitalWrite(LED_M,LOW);
        }else if(randNumber==2){
          digitalWrite(LED_B,LOW);
        }else if(randNumber==3){
          digitalWrite(LED_T,HIGH);
        }else if(randNumber==4){
          digitalWrite(LED_M,HIGH);
        }else if(randNumber==5){
          digitalWrite(LED_B,HIGH);
        }
      delay(moveSpeed);
    }
  }
}
