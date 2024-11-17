#include<Servo.h>
Servo.angle
void setup() {
 angle.attach(4);
 angle.write(0);
}

void loop() {
  angle.write(45);
  delay(1000);
  angle.write(90);
  delay(1000);
  angle.write(135);
  delay(1000);
  angle.write(180);
  delay(1000);
}
