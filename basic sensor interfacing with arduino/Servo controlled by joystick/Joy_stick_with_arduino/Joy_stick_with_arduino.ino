#include<Servo.h>

const int x=A1;
const int y=A0;

int valx,valy;
int anglex,angley;

int X_volt,y_volt;
Servo joy;
void setup() {
  Serial.begin(9600);  
  joy.attach(5);
  joy.write(0);
}

void loop() 
{
  valx=analogRead(x);
  valy=analogRead(y);
  X_volt=((valx*5.0)/1023);
  y_volt=((valy*5.0)/1023);
  anglex=map(X_volt,0,5,0,180);
  angley=map(y_volt,0,5,0,180);  
  joy.write(anglex);
  Serial.print("Joy-Stick at x:");
  Serial.println(X_volt);
  Serial.print("Servo-Angle:");
  Serial.println(anglex);
  delay(2000);
}
