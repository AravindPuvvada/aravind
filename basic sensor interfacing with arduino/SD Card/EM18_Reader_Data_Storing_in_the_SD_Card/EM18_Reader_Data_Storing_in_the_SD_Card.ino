#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

File data;

// Define the pins for the EM18 RFID reader
const int rfidRxPin = 2; // RX pin of EM18
const int rfidTxPin = 3; // TX pin of EM18

// Create a SoftwareSerial instance
SoftwareSerial rfidSerial(rfidRxPin, rfidTxPin);

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
  rfidSerial.begin(9600); // EM18 communicates at 9600 baud

  Serial.print("SD Card init...");
  // Test if wiring is correct
  if (!SD.begin(10)) {
    Serial.println("init failed..");
    while (1);
  }
  Serial.println("init ok");
}

void loop() {
  // Check if an RFID tag is available
  if (rfidSerial.available()) {
    String rfidData = "";
    while (rfidSerial.available()) {
      char c = rfidSerial.read(); // Read each character from the RFID reader
      rfidData += c; // Append the character to the rfidData string
    }

    // Remove any unwanted characters (if necessary)
    rfidData.trim(); // Remove leading/trailing whitespace

    // Generate a random number for demonstration
    int number = random(0, 10); // Create random number
    String stringData = "Tag: " + rfidData + ", Number: " + (String)number; // Combine RFID and random number

    // Open file to write data
    data = SD.open("data.txt", FILE_WRITE);
    if (data) {
      data.println(stringData); // Print the data to file
      data.close();
      Serial.println(stringData); // Print to Serial Monitor
    } else {
      Serial.println("Cannot open file");
    }
  }
}
