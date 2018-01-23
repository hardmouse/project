int counter;
int num;
int c;
int varArray[10];// assuming we got 12 variables in an incoming array.
void doMove(){
  // why use "sizeof(varArray)/2", don't ask. because I don't know. :D
  for(int j=0;j<sizeof(varArray)/2;j++){
    Serial.print(j);
    Serial.print(":");
    Serial.println(varArray[j]);
  }
  if(varArray[1]==123){
    doThis();
  }
  if(varArray[2]==321){
    doThat();
  }
  if(varArray[3]==777){
    daddy();
  }
}
void process_command(){
  // array 0 must be 1 to turn on the led. or led will be off.
  // if array(0) is 1, doMove() will be executed.
  if(varArray[0]==1){
    digitalWrite(13, HIGH);
    doMove();
  }else{
    digitalWrite(13, LOW);
  }
  
  delay(10);
  
}
// The line below is for testing purpose only
// #1|123|321|777|534|55|66|77|88|99|00|1000|101|*
void assignVar(){
  c = Serial.read();
  Serial.println(c);
      if (c == '#'){
        counter = 0;
        num = 0;
      }
      if (isdigit (c)){
        num *= 10;  // previous value is 10 times larger
        num += c - '0';  // add new digit
       }
      if (c == '|'){
        varArray[counter++] = num;
        num = 0;
      }
      if (c == '*'){
        varArray[counter] = num;
        //Serial.print("<-----");
        process_command ();
      }
}
