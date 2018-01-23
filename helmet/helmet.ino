#include <Servo.h> 
 
Servo myservo_L;
Servo myservo_R;
Servo myservo_D;
boolean coverOpen = false;
int speedy=10;
int val = 0;
int posL = 133;
int posR = 75;
int posD = 101;
int led = 10;
int putton=6; 
int stupidCount = 0;
void maskOpen(){
  if(coverOpen==true){
    Serial.println("close");
    posL = 136;
    posR = 75;
    for(val=0; val<=80; val++){
      posL = 136 - val;
      posR = 75 + val;
      myservo_L.write(posL);
      myservo_R.write(posR); 
      delay(speedy);
    }
    posD = 21;
    myservo_D.write(posD);
    digitalWrite(led, HIGH);
    coverOpen=false;
  }else{
    Serial.println("open");    
    posL = 56;
    posR = 152;
    for(val=0; val<=80; val++){
      posL = 56 + val;
      posR = 152 - val;
      myservo_L.write(posL);
      myservo_R.write(posR); 
      delay(speedy);
    }
    posD = 101;
    myservo_D.write(posD);
    digitalWrite(led, LOW);
    coverOpen=true;
  }
}
 
void setup(){ 
  Serial.begin(9600);
  myservo_L.attach(9);
  myservo_R.attach(8);
  myservo_D.attach(7);
  pinMode(led, OUTPUT);
  pinMode(putton, INPUT);
  digitalWrite(putton, HIGH);
    posL = 56; //56
    posR = 152; //152
    posD = 25; //low val = low pos. 55=lowest,
    myservo_L.write(posL);
    myservo_R.write(posR); 
    delay(100);
    myservo_D.write(posD); 
    digitalWrite(led, HIGH);
    coverOpen=false;
} 

void loop(){
  /*
  Serial.print(stupidCount);
  Serial.print("   :    ");
  Serial.println(digitalRead(putton));
  */
  if(digitalRead(putton)==1){
    stupidCount++;
    if(stupidCount>30){
      stupidCount=0;
      maskOpen();
    }
  }else{
    stupidCount=0;
  }
  delay(10);
} 
