#include<Servo.h>
Servo angle;
void setup() {
Serial.begin(9600);
angle.attach(4);


}
void loop() {
if(Serial.available()>0)
{
  int val=Serial.read();
  Serial.print("Servo:");
  Serial.println(val);
  if(val=='a')
  {
    angle.write(0);
    delay(1000);
    
  }
  if(val=='b')
  {
    angle.write(10);
    delay(1000);
    
  }
  if(val=='c')
  {
    angle.write(30);
    delay(1000);
    
  }
  if(val=='d')
  {
    angle.write(40);
    delay(1000);
  }
  if(val=='e')
  {
    angle.write(50);
    delay(1000);
  }
  if(val=='f')
  {
    angle.write(60);
    delay(1000);
  }
  if(val=='g')
  {
    angle.write(70);
    delay(1000);
  }
  if(val=='h')
  {
    angle.write(80);
    delay(1000);
  }
  if(val=='i')
  {
    angle.write(90);
    delay(1000);
  }
  if(val=='j')
  {
    angle.write(100);
    delay(1000);
  }
  if(val=='k')
  {
    angle.write(110);
    delay(1000);
  }
  if(val=='l')
  {
    angle.write(120);
    delay(1000);
  }
  if(val=='m')
  {
    angle.write(130);
    delay(1000);
  }
  if(val=='n')
  {
    angle.write(140);
    delay(1000);
  }
  if(val=='0')
  {
    angle.write(150);
    delay(1000);
  }
  if(val=='p')
  {
    angle.write(160);
    delay(1000);
  }
  if(val=='q')
  {
    angle.write(170);
    delay(1000);
  }
  if(val=='r')
  {
    angle.write(180);
    delay(1000);
  }
  delay(1000);
}
}
