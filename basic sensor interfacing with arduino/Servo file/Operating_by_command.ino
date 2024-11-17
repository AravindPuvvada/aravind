#include<Servo.h>
Servo user;
int i;
void setup() {
Serial.begin(9600);
user.attach(2);
}
void loop() {
  if (Serial.available())
  {
   
    i=Serial.parseInt();
    while(Serial.available())
    {
      Serial.read();
    }
    if(i>= 0 && i<= 180)
    {
     Serial.println(i);
     user.write(i);
     delay(1000);
    }
    else
    {
      Serial.println("Invalid");
    }
  }
}
