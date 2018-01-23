int fogyLight = 1;
int lsinLight = 2;
int rsinLight = 3;
int headLight = 4;
int backLight = 5;

int RPWM_R = 6; 
int enR_R = 7;
int LPWM_R = 9;
int enL_R = 8;

int RPWM_L = 10; 
int enR_L = 12;
int LPWM_L = 11;
int enL_L = 13;

int motorSpeed = 0;
int incAmount = 5;
int stat = 0;
void setup(){
  Serial.begin (9600);
  pinMode(LPWM_R, OUTPUT); 
  pinMode(RPWM_R, OUTPUT); 
  pinMode(enL_R, OUTPUT);
  pinMode(enR_R, OUTPUT);
  pinMode(LPWM_L, OUTPUT); 
  pinMode(RPWM_L, OUTPUT); 
  pinMode(enL_L, OUTPUT);
  pinMode(enR_L, OUTPUT);
  
  digitalWrite(enL_L, HIGH);
  digitalWrite(enR_L, HIGH);
  digitalWrite(enL_R, HIGH);
  digitalWrite(enR_R, HIGH);
  
  pinMode(fogyLight, OUTPUT);
  pinMode(rsinLight, OUTPUT);
  pinMode(lsin Light, OUTPUT);
  pinMode(headLight, OUTPUT);
  pinMode(backLight, OUTPUT);

  digitalWrite(fogyLight, LOW);
  digitalWrite(rsinLight, LOW);
  digitalWrite(lsinLight, LOW);
  digitalWrite(headLight, LOW);
  digitalWrite(backLight, LOW);
}

void loop() {
  if(stat<2){
    analogWrite(RPWM_R,motorSpeed);
    digitalWrite(LPWM_R, LOW);
    analogWrite(RPWM_L,motorSpeed);
    digitalWrite(LPWM_L, LOW);
    digitalWrite(headLight, HIGH);
    digitalWrite(backLight, LOW);
  }else{
    analogWrite(LPWM_R,motorSpeed);
    digitalWrite(RPWM_R, LOW);
    analogWrite(LPWM_L,motorSpeed);
    digitalWrite(RPWM_L, LOW);
    digitalWrite(headLight, LOW);
    digitalWrite(backLight, HIGH);
  }
    motorSpeed = motorSpeed + incAmount;
    if (motorSpeed == 0 || motorSpeed == 255) {
      incAmount= -incAmount ; 
      stat++;
    }
  delay(100);
  if(stat==4){
    stat=0;
  }
  Serial.println(stat);
}
