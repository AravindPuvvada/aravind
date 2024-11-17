#include <ESP32Servo.h>

// Create a servo object
Servo user;

void setup() {
  // Attach the servo on pin 26 to the servo object
  user.attach(23);
}

void loop() {
  // Move the servo to 45 degrees
  user.write(45);
  delay(1000); // Wait for 1 second

  // Move the servo to 90 degrees
  user.write(90);
  delay(1000); // Wait for 1 second

  // Move the servo to 135 degrees
  user.write(135);
  delay(1000); // Wait for 1 second

  // Move the servo to 180 degrees
  user.write(180);
  delay(1000); // Wait for 1 second
}
