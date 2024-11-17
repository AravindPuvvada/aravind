#include <SoftwareSerial.h>

// Create a software serial port for Bluetooth communication
SoftwareSerial bluetooth(0,1); // RX, TX

String receivedString = ""; // String to store incoming data

void setup() {
  // Start the hardware serial communication for debugging
  Serial.begin(9600);
  
  // Start the software serial communication with the Bluetooth module
  bluetooth.begin(9600);
  
  Serial.println("Bluetooth test started.");
}

void loop() {
  // Check if data is available from the Bluetooth module
  while (bluetooth.available()) {
    char receivedChar = bluetooth.read();
    
    if (receivedChar == '\n' || receivedChar == '\r') {
      // Print the message if it's not empty
      if (receivedString.length() > 0) {
        Serial.print("Received: ");
        Serial.println(receivedString);
        receivedString = ""; // Clear the string after processing
      }
    } else {
      // Append the received character to the string buffer
      receivedString += receivedChar;
    }
  }

  // Check if data is available from the serial monitor
  if (Serial.available()) {
    String sendString = Serial.readStringUntil('\n'); // Read a string from Serial Monitor until newline
    bluetooth.println(sendString); // Send the string to Bluetooth module
    Serial.print("Sent: ");
    Serial.println(sendString);
  }
}
