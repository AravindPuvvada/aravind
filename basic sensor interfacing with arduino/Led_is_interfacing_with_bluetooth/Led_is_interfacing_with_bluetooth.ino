#include <SoftwareSerial.h>

// Create a software serial port for Bluetooth communication
SoftwareSerial bluetooth(10, 11); // RX, TX

const int ledPin = 4; // Pin where the LED is connected
String receivedString = ""; // Variable to store incoming data

void setup() {
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(9600); // Start serial communication for debugging
  bluetooth.begin(9600); // Start software serial communication with Bluetooth module
}

void loop() {
  while (bluetooth.available()) { // Check if data is available to read
    char receivedChar = bluetooth.read(); // Read the incoming byte

    if (receivedChar == '\n' || receivedChar == '\r') { // End of command
      if (receivedString == "on") { // Turn LED ON if command is "on"
        digitalWrite(ledPin, HIGH);
        Serial.println("LED ON"); // Optional: Debugging message
      } else if (receivedString == "off") { // Turn LED OFF if command is "off"
        digitalWrite(ledPin, LOW);
        Serial.println("LED OFF"); // Optional: Debugging message
      }

      receivedString = ""; // Clear the string buffer for the next message
    } else {
      receivedString += receivedChar; // Append character to the string buffer
    }
  }
}
