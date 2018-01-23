
void forward(int speedy) {
    L_U.write(posLU);
    R_U.write(posRU);
    L_B.write(posLB+10);
    R_B.write(posRB+10);
    delay(speedy);
    L_U.write(posLU);
    R_U.write(posRU-20);
    L_B.write(posLB+5);
    R_B.write(posRB+10);
    delay(speedy);
    L_U.write(posLU);
    R_U.write(posRU);
    L_B.write(posLB);
    R_B.write(posRB);
    delay(speedy);
    
    L_U.write(posLU);
    R_U.write(posRU);
    L_B.write(posLB-10);
    R_B.write(posRB-10);
    delay(speedy);
    L_U.write(posLU+20);
    R_U.write(posRU);
    L_B.write(posLB-10);
    R_B.write(posRB-5);
    delay(speedy); 
    L_U.write(posLU);
    R_U.write(posRU);
    L_B.write(posLB);
    R_B.write(posRB);
    delay(speedy);
}
void backward(int speedy) {
    L_U.write(posLU);
    R_U.write(posRU);
    L_B.write(posLB);
    R_B.write(posRB+10);
    delay(speedy);
    L_U.write(posLU);
    R_U.write(posRU+20);
    L_B.write(posLB);
    R_B.write(posRB);
    delay(speedy);
    L_U.write(posLU);
    R_U.write(posRU);
    L_B.write(posLB);
    R_B.write(posRB);
    delay(speedy);
    
    L_U.write(posLU);
    R_U.write(posRU);
    L_B.write(posLB-10);
    R_B.write(posRB);
    delay(speedy);
    L_U.write(posLU-20);
    R_U.write(posRU);
    L_B.write(posLB);
    R_B.write(posRB);
    delay(speedy); 
    L_U.write(posLU);
    R_U.write(posRU);
    L_B.write(posLB);
    R_B.write(posRB);
    delay(speedy);
}
void turnleft(int speedy) {
    L_U.write(posLU);
    R_U.write(posRU);
    L_B.write(posLB);
    R_B.write(posRB+10);
    delay(speedy);
    L_U.write(posLU-20);
    R_U.write(posRU+20);
    L_B.write(posLB);
    R_B.write(posRB);
    delay(speedy);
    L_U.write(posLU);
    R_U.write(posRU);
    L_B.write(posLB);
    R_B.write(posRB);
    delay(speedy);
}
void dist() {
  int result=0;
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  result=uS / US_ROUNDTRIP_CM;
  Serial.print("Ping: ");
  Serial.print(result); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  if(result>20 && result<35){
    forward(delayTime);
  }
}

