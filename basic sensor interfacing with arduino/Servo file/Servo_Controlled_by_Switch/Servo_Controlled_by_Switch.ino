#include<Servo.h>
int relay=2;
int led=3;
int sw=8;
int s2=5;
Servo user;
void setup() 
{
  user.attach(9);
  user.write(0);
  pinMode(relay,OUTPUT);
  pinMode(led,OUTPUT);
}

void loop() {
  
  if(digitalRead(sw)==0)
  {
    digitalWrite(relay,LOW);
    user.write(180);
    delay(1000);
    digitalWrite(led,HIGH);
  }
  else if(digitalRead(s2)==0)
  {
    digitalWrite(led,LOW);
    user.write(0);
    delay(1000);
    digitalWrite(relay,HIGH);
  }
  
}
