#include <Wire.h>

int val11;
int val2;

void setup()
{  
  //pinMode(LED1,OUTPUT);  
  Serial.begin(9600);  
  Serial.println("Emartee.Com");  
  Serial.println("Voltage: ");  
  Serial.print("V");
}
void loop()
{      
  float temp;      
  val11=analogRead(1);      
  temp=val11/4.092;      
  val11=(int)temp;//      
  val2=((val11%100)/10);      
  Serial.print(val2);       
  Serial.println("V");          
  delay(1000);
}                     

