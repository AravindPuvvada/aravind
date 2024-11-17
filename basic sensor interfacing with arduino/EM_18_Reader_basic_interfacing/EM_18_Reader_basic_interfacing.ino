#include <SoftwareSerial.h>

SoftwareSerial rfid(4,5); // RX, TX

String rfidTag = ""; // Variable to store RFID tag

void setup() {
  Serial.begin(9600);    // Start serial communication with Serial Monitor
  rfid.begin(9600);      // Start communication with EM18 reader
  Serial.println("Place the RFID card/tag near the reader...");
}

void loop() {
  // Check if there is data available from the RFID reader
  if (rfid.available()) {
    char c = rfid.read();  // Read one character
    rfidTag += c;          // Append the character to the RFID tag string
    
    // Check if we have received the full tag (EM18 typically sends 12 characters)
    if (rfidTag.length() == 12) {
      Serial.print("RFID Tag: ");
      Serial.println(rfidTag);  // Print the full tag to Serial Monitor
      rfidTag = "";             // Clear the string for the next tag
    }
  }
}
