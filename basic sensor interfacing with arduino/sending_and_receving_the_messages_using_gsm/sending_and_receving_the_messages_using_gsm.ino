#include <SoftwareSerial.h>
SoftwareSerial sim(2, 3); //Tx of GSM to arduino pin 2, Rx of GSM to arduino pin 3
#include <LiquidCrystal.h>
const int rs = 10, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int _timeout;
String _buffer;
String number = "+919494956343"; //-> change with your number
unsigned long previousMillis = 0;
const long interval = 60000; // 60 seconds (you can adjust this)

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Subscribe");
  lcd.setCursor(0, 1);
  lcd.print("STT-MANI");
  Serial.begin(9600);
  _buffer.reserve(50);
  Serial.println("System Started...");
  sim.begin(9600);
  delay(1000);
  Serial.println("GSM SIM800L Module Ready...");
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Automatically check for incoming messages
  RecieveMessage();

  // Automatically send a message every 60 seconds (or based on condition)
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Pass a message when calling SendMessage()
    SendMessage("Hello, how are you?");  // Example message to be sent
  }

  // Display info on the LCD
  lcd.setCursor(0, 0);
  lcd.print("  GSM SIM 800L ");
  lcd.setCursor(0, 1);
  lcd.print("Caller ID Projct");

  // Check if GSM module sends any data
  if (sim.available() > 0) {
    Serial.write(sim.read());
  }
}

void SendMessage(String message) {
  sim.println("AT+CMGF=1");    // Set SMS mode to text
  delay(200);
  sim.println("AT+CMGS=\"" + number + "\"\r"); // Send SMS to predefined number
  delay(200);
  sim.println(message);  // Send the message content
  delay(100);
  sim.println((char)26); // ASCII code of CTRL+Z
  delay(200);
  _buffer = _readSerial();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sending ... ");
  lcd.setCursor(0, 1);
  lcd.print(message.substring(0, 16));  // Display first part of the message
  delay(5000);
}

void RecieveMessage() {
  sim.println("AT+CMGF=1");
  delay(200);
  sim.println("AT+CNMI=1,2,0,0,0"); // Receive SMS automatically
  delay(200);
  
  if (sim.available() > 0) {
    String receivedMessage = sim.readString();
    Serial.println("Received: " + receivedMessage);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("New Message!");
    lcd.setCursor(0, 1);
    lcd.print(receivedMessage.substring(0, 16)); // Display part of the message
    
    // Check if the message contains "hi"
    if (receivedMessage.indexOf("hi") >= 0) {
      SendMessage("Hello");  // Send "Hello" as a reply
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Auto Reply: ");
      lcd.setCursor(0, 1);
      lcd.print("Hello Sent");
    }
    delay(5000);
  }
}

String _readSerial() {
  _timeout = 0;
  while (!sim.available() && _timeout < 12000) {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
  return "";
}

void callNumber() {
  sim.print(F("ATD"));
  sim.print(number);
  sim.print(F(";\r\n"));
  _buffer = _readSerial();
  Serial.println(_buffer);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calling.... ");
  lcd.setCursor(0, 1);
  lcd.print(number);
  delay(14000);
}
