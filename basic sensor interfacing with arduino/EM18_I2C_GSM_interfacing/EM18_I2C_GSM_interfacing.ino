#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial rfid(2, 3); // RX, TX
SoftwareSerial sim800l(8,9); // RX, TX

LiquidCrystal_I2C lcd(0x27, 16, 2);

String rfidTag = ""; // Variable to store RFID tag
String correctTag = "120048356B04"; // Correct RFID tag ID

void setup() {
  Serial.begin(9600); 
  sim800l.begin(9600); // Start serial communication with GSM module
  rfid.begin(9600);    // Start serial communication with RFID reader
  lcd.init();                 
  lcd.backlight();
  Serial.println("Place the RFID card/tag near the reader...");
  lcd.setCursor(0,0);
  lcd.print("Place RFID tag");
}

void loop() {
  if (rfid.available()) {
    char c = rfid.read();  
    rfidTag += c;          
    if (rfidTag.length() == 12) {
      Serial.print("RFID Tag: ");
      Serial.println(rfidTag);  // Print the full tag to Serial Monitor

      if (rfidTag == correctTag) {
        Serial.println("Successfully login");
        sendSMS("+918919389844","Succesfully Login");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Successfully");
        lcd.setCursor(0, 1);
        lcd.print("login");
      } else {
        Serial.println("Unauthorized tag");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Access Denied");
      }

      rfidTag = ""; // Clear the string for the next tag
    }
  }
}
void sendSMS(const char* phoneNumber, const char* message) {
  sim800l.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  sim800l.print("AT+CMGS=\"");
  sim800l.print(phoneNumber);
  sim800l.println("\"");
  delay(1000);
  sim800l.print(message);
  sim800l.write(0x1A); // Send Ctrl+Z to finish message
  delay(1000);
  Serial.println("SMS Sent");
}
