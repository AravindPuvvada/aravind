#include <Servo.h>

Servo myServo;  // Create a Servo object

void setup() {
  myServo.attach(12);  // Attach the servo to pin 9 (you can change the pin number)
}

void loop() {
  // Sweep from 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos += 45) {
    myServo.write(pos);            // Set the servo position
    delay(1000);                     // Wait for the servo to reach the position
  }

  // Sweep from 180 to 0 degrees
  for (int pos = 180; pos >= 0; pos -= 45) {
    myServo.write(pos);            // Set the servo position
    delay(1000);                     // Wait for the servo to reach the position
  }
}
