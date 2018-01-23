int buzzpin=9;
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(buzzpin, OUTPUT);
  delay(1000);
} 

void loop()  {
  for(int val = 0; val<=150; val+=5){
    beep(7,val);
  }
  for(int val = 150; val>0; val-=5){
    beep(7,val);
  }
}

void beep(unsigned char delayms, unsigned char volum){
  analogWrite(buzzpin, volum);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(buzzpin, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
}
