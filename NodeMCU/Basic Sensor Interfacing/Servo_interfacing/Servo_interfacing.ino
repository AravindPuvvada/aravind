#include <Servo.h>

const int servoPin = D2; // GPIO pin connected to the servo signal wire
Servo myServo;          // Create a Servo object

void setup() {
  myServo.attach(servoPin); // Attach the servo to the pin
}

void loop() {
  // Move the servo to 0 degrees
  myServo.write(0);
  delay(1000); // Wait for 1 second

  // Move the servo to 90 degrees
  myServo.write(90);
  delay(1000); // Wait for 1 second

  // Move the servo to 180 degrees
  myServo.write(180);
  delay(1000); // Wait for 1 second
}
