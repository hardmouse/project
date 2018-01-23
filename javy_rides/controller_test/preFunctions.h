void initMe(){
  pinMode(j_up, INPUT); 
  pinMode(j_down, INPUT); 
  pinMode(j_left, INPUT); 
  pinMode(j_right, INPUT); 
  pinMode(t_up, INPUT); 
  pinMode(t_down, INPUT); 
  pinMode(t_left, INPUT); 
  pinMode(t_right, INPUT); 
  pinMode(t_middle, INPUT);
  pinMode(LED_left, OUTPUT);
  pinMode(LED_right, OUTPUT);
  pinMode(Lit_L, OUTPUT);
  pinMode(Lit_R, OUTPUT);
  pinMode(Lit_flash, OUTPUT);
  pinMode(Lit_break, OUTPUT);
  pinMode(Lit_head, OUTPUT);
  pinMode(Lit_spare, OUTPUT);
  digitalWrite(j_up, HIGH);
  digitalWrite(j_down, HIGH);
  digitalWrite(j_left, HIGH);
  digitalWrite(j_right, HIGH);
  digitalWrite(t_up, HIGH);
  digitalWrite(t_down, HIGH);
  digitalWrite(t_left, HIGH);
  digitalWrite(t_right, HIGH);
  digitalWrite(t_middle, HIGH);
  digitalWrite(Lit_L, LOW);
  digitalWrite(Lit_R, LOW);
  digitalWrite(Lit_flash, LOW);
  digitalWrite(Lit_break, LOW);
  digitalWrite(Lit_head, LOW);
  digitalWrite(Lit_spare, LOW);
  speedPinLeft.attach(8);
  speedPinRight.attach(9);
}
void moveTo(int dir){
  //Serial.println(dir);
  switch (dir) {
  case 1: //forward
    speedLeft++;
    speedRight++;
    if(speedLeft>speedHi){
      speedLeft=speedHi;
    }
    if(speedRight>speedHi){
      speedRight=speedHi;
    }
    break;
  case 2: //backward
    speedLeft--;
    speedRight--;
    if(speedLeft<speedLo){
      speedLeft=speedLo;
    }
    if(speedRight<speedLo){
      speedRight=speedLo;
    }
    break;
  case 3: //left turn
    speedLeft++;
    speedRight--;
    if(speedLeft>speedHi){
      speedLeft=speedHi;
    }
    if(speedRight<speedLo){
      speedRight=speedLo;
    }
    break;
  case 4: //right turn
    speedLeft--;
    speedRight++;
    if(speedLeft<speedLo){
      speedLeft=speedLo;
    }
    if(speedRight>speedHi){
      speedRight=speedHi;
    }
    break;
  case 5: //forward + right
    speedRight++;
    if(speedRight>speedHi){
      speedRight=speedHi;
    }
    if(speedLeft>speedMh){
      speedLeft--;
    }else if(speedLeft<speedMh){
      speedLeft++;
    }
    break;
  case 6: //backward + right
    speedRight--;
    if(speedRight<speedLo){
      speedRight=speedLo;
    }
    if(speedLeft>speedMl){
      speedLeft--;
    }else if(speedLeft<speedMl){
      speedLeft++;
    }
    break;
  case 7: //backward + left
    speedLeft--;
    if(speedLeft<speedLo){
      speedLeft=speedLo;
    }
    if(speedRight>speedMl){
      speedRight--;
    }else if(speedRight<speedMl){
      speedRight++;
    }
    break;
  case 8: //forward + left
    speedLeft++;
    if(speedLeft>speedHi){
      speedLeft=speedHi;
    }
    if(speedRight>speedMh){
      speedRight--;
    }else if(speedRight<speedMh){
      speedRight++;
    }
    break;
  default: //Stop
    if(speedLeft>speedMd+3){
      speedLeft-=5;
    }else if(speedLeft<speedMd-3){
      speedLeft+=5;
    }
    if(speedRight>speedMd+3){
      speedRight-=5;
    }else if(speedRight<speedMd-3){
      speedRight+=5;
    }
    break;
  }
  speedPinLeft.write(speedLeft);
  speedPinRight.write(speedRight);
}
void checkHeadLight(){
  if(digitalRead(t_middle)==0){
    digitalWrite(Lit_head, HIGH);
  }else{
    digitalWrite(Lit_head, LOW);
  }
}
void checkFlashLight(){
  if(digitalRead(t_up)==0){
    digitalWrite(Lit_flash, HIGH);
  }else{
    digitalWrite(Lit_flash, LOW);
  }
}
void checkBreakLight(){
  if(digitalRead(t_down)==0){
    digitalWrite(Lit_break, HIGH);
  }else{
    digitalWrite(Lit_break, LOW);
  }
}
void checkLightL(){
  if(digitalRead(t_left)==0){
    if(lit_L_stat){
      lit_L_stat=false;
      digitalWrite(LED_left, LOW);
      digitalWrite(Lit_L, LOW); 
    }else{
      lit_L_stat=true;
      digitalWrite(LED_left, HIGH);
      digitalWrite(Lit_L, HIGH);
    }
    //Rlight.check();
  }else{
    lit_L_stat=false;
    digitalWrite(LED_left, LOW);
    digitalWrite(Lit_L, LOW);
  }
}

void checkLightR(){
  if(digitalRead(t_right)==0){
    if(lit_R_stat){
      lit_R_stat=false;
      digitalWrite(LED_right, LOW);
      digitalWrite(Lit_R, LOW); 
    }else{
      lit_R_stat=true;
      digitalWrite(LED_right, HIGH);
      digitalWrite(Lit_R, HIGH);
    }
    //Llight.check();
  }else{
    lit_R_stat=false;
    digitalWrite(LED_right, LOW);
    digitalWrite(Lit_R, LOW);
  }
}

// ____________________________________________________TimeAction Start
void flashLight_L(){
  digitalWrite(LED_left, HIGH);
  digitalWrite(Lit_L, HIGH);  
  delay(flashSpeed);
  digitalWrite(LED_left, LOW);
  digitalWrite(Lit_L, LOW);  
  delay(flashSpeed);
}
void flashLight_R(){
  digitalWrite(LED_right, HIGH);
  digitalWrite(Lit_R, HIGH);   
  delay(flashSpeed);
  digitalWrite(LED_right, LOW);
  digitalWrite(Lit_R, LOW);  
  delay(flashSpeed);
}
TimedAction Llight = TimedAction(1000,flashLight_L);
TimedAction Rlight = TimedAction(1000,flashLight_R);


