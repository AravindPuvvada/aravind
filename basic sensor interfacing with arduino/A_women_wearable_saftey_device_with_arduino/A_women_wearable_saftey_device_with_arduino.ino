#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

// Create instances for SoftwareSerial and LiquidCrystal
SoftwareSerial sim800l(8,9); // RX, TX
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // RS, E, D4, D5, D6, D7

int sw=10;
int buzzer=11;

void setup() {
  // Initialize SIM800L communication
  pinMode(buzzer,OUTPUT);
  sim800l.begin(9600);
  Serial.begin(9600);
  delay(1000);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.clear();
  project_name();
}

void loop() {
  if(digitalRead(sw)==0)
  {
  Serial.println("Button Pressed");
  lcd.print("SMS Sent!!");
  sendSMS("+919398594569", "Somebody is in the danger");
  digitalWrite(buzzer,HIGH);
  delay(5000); // Delay between sending SMS
  }
  lcd.clear();
  digitalWrite(buzzer,LOW);
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
void project_name()
{
  lcd.setCursor(0,0);
  lcd.print(" Women Wearable");
  lcd.setCursor(0,1);
  lcd.print(" Saftey Device");
  delay(3000);
  lcd.clear();
}
