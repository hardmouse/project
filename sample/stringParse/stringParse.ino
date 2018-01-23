// Jay Yu did this clumsy code with helps from every where. Share this code if you are as clumsy as me.
// 2015 07 09

void setup(void){
  Serial.begin(9600);
}
void loop(void){
  while (Serial.available() < 1) {
  } // Wait until a character is received
  //char val = Serial.read();
  assignVar();
}
void doThis(){
  Serial.println("Do this!!");
}
void doThat(){
  Serial.println("Do that!!");
}
void daddy(){
  Serial.println("Who is your daddy!!");
}
