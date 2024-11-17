#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <TimeLib.h>  // Include the Time library for handling time

File data;

// Define the pins for the EM18 RFID reader
const int rfidRxPin = 2; // RX pin of EM18
const int rfidTxPin = 3; // TX pin of EM18

// Create a SoftwareSerial instance
SoftwareSerial rfidSerial(rfidRxPin, rfidTxPin);

// Map RFID tag to names
String getPersonName(String rfidTag) {
  if (rfidTag == "20047D7CB49") {  // Replace with actual RFID tag for Aravind
    return "Aravind";
  } else if (rfidTag == "20048356B04") {  // Replace with actual RFID tag for Vishnu
    return "Vishnu";
  } else {
    return "Unknown";  // Default if the tag is not recognized
  }
}

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

  // Create or open a CSV file
  data = SD.open("data.csv", FILE_WRITE);
  if (data) {
    // Add a header row for the CSV file
    data.println("ID_Pass,Arrival_Time,Bus_Service_Order,Ticket_Service_Time,Depart_Time");
    data.close();
  }
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

    // Get the name associated with the RFID tag
    String personName = getPersonName(rfidData);

    // Get the current time for ticket service (this is a placeholder for actual time management)
    String arrivalTime ="10:00"; // Replace with actual time handling
    String ticketServiceTime = String(hour()) + ":" + String(minute());
    String departTime = "11:00"; // Replace with actual departure time

    // Open file to write data in CSV format
    data = SD.open("data.csv", FILE_WRITE);
    if (data) {
      // Write RFID tag, arrival time, and other data as comma-separated values
      data.print(rfidData);
      data.print(",");  // ID_Pass
      data.print(arrivalTime);
      data.print(",");  // Arrival_Time
      data.print("1");  // Bus_Service_Order
      data.print(",");  // Ticket_Service_Time
      data.print(ticketServiceTime);
      data.print(",");  // Depart_Time
      data.println(departTime);
      data.close();

      // Print to Serial Monitor
      Serial.print("RFID Tag: ");
      Serial.print(rfidData);
      Serial.print(", Name: ");
      Serial.println(personName);
    } else {
      Serial.println("Cannot open file");
    }
  }
}
