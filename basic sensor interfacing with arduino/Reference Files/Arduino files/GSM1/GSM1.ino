#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

// Create instances for SoftwareSerial and LiquidCrystal
SoftwareSerial sim800l(0, 1); // RX, TX
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // RS, E, D4, D5, D6, D7

void setup() {
  // Initialize SIM800L communication
  sim800l.begin(9600);
  delay(1000);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sending SMS...");
}

void loop() {
  // Send SMS to multiple phone numbers
  sendSMS("+916281104093", "STT-MANI.");
  sendSMS("+919494956343", "STT-MANI.");
  delay(5000); // Delay between sending SMS

  // You can add more logic or functionality here if needed
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
}
