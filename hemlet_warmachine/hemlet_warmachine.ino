#include <Servo.h> 
 
Servo myservo_U;
Servo myservo_D;
boolean coverOpen = false;
int speedy=10;
int val = 0;
int posU = 36;
int posD = 120;
int led = 10;
const int putton = 12; 
int stupidCount = 0;
void maskOpen(){
  if(coverOpen==true){ //如果面罩是是否開著的判斷, true表示是開著的
    Serial.println("close"); //偵測用
    posU = 133; //上面舵機的起始位置
    posD = 97; //下面舵機的起始位置
    for(val=0; val<=46; val++){ //針對所使用的舵機及硬體配置，開合角度的值各有不同，我的是46
      posD = 97 + val; //下面舵機先動作
      myservo_D.write(posD); 
      delay(speedy);
    }
    for(val=0; val<=97; val++){ //針對所使用的舵機及硬體配置，開合角度的值各有不同，我的是97
      posU = 133 - val; //上面舵機再動作
      myservo_U.write(posU);
      delay(speedy);
    }
    digitalWrite(led, HIGH);
    /*
    for(int brightness=0; brightness<=255; brightness++){ // 動作做完開LED
      analogWrite(led, brightness);
      delay(10);
    }
    */
    //digitalWrite(led, HIGH);
    coverOpen=false; //所有動作做完,宣告(coverOpen)面罩是關上的狀態
  }else{ // 如果coverOpen是蓋上的...
    Serial.println("open");
    /*
    for(int brightness=255; brightness>0; brightness--){ //把LED關起來
      analogWrite(led, brightness);
      delay(1);
    }
    */
    digitalWrite(led, LOW);
    posU = 36; //上面舵機的起始位置
    posD = 143; //下面舵機的起始位置

	//這比較特殊點，我的舵機關上時的數據剛好差一半，所以除2剛好(下面的程式有一行val2 = val/2;)
	//讓兩個舵機同時進行動作，所以只執行一個FOR迴圈

    int val2 = 0; //宣告對應值
    for(val=0; val<=97; val++){
      posU = 36 + val;
      myservo_U.write(posU);
      val2 = val/2;
      posD = 143 - val2;
      myservo_D.write(posD);
      delay(speedy);
    }
    myservo_D.write(97); // 這程式比較笨些~上面執行完後，下面的舵機位置其實是在差不多 85~90左右吧? 我的要97才能正確密合，所以強行定成97
    //digitalWrite(led, LOW);
    coverOpen=true; //所有動作做完,宣告(coverOpen)面罩是開啟的狀態
  }
}
 
void setup(){ 
  Serial.begin(9600);
  myservo_U.attach(13);
  myservo_D.attach(11);
  pinMode(led, OUTPUT);
  pinMode(putton, INPUT);
  digitalWrite(putton, HIGH);
    posU = 36; //36~133=97
    posD = 143; //97~143=46
    myservo_U.write(posU);
    myservo_D.write(posD); 
    delay(100);
    digitalWrite(led, HIGH);
    coverOpen=false;
} 

void loop(){
  /*
  Serial.print(stupidCount);
  Serial.print("   :    ");
  */
  Serial.println(digitalRead(putton));
  if(digitalRead(putton)==1){
    Serial.println("YYY");
    maskOpen();
  }
  delay(10);
} 
