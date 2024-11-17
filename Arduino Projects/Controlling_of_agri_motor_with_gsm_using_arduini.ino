#include <SoftwareSerial.h>
SoftwareSerial sim(2, 3); 
int _timeout;
String _buffer;
String number = "+917396055789";
unsigned long previousMillis = 0;
const long interval = 60000; 
int water=A0;
// Define the relay pin
const int relayPin = 12; 
int value;
void setup() {
  pinMode(relayPin, OUTPUT); 
  digitalWrite(relayPin, LOW); 

  Serial.begin(9600);
  _buffer.reserve(50);
  Serial.println("System Started...");
  sim.begin(9600);
  delay(1000);
  Serial.println("GSM SIM800L Module Ready...");
}

void loop() {
  unsigned long currentMillis = millis();
  value = analogRead(water);
  Serial.print("Water-level: ");
  Serial.println(value);
  delay(1000);

  if (value >200) {
    SendMessage("No water in the Tank");
    delay(1000);
  }

  // Check for incoming SMS commands
  RecieveMessage();

  if (sim.available() > 0) {
    Serial.write(sim.read());
  }
}

void SendMessage(String message) {
  sim.println("AT+CMGF=1");    
  delay(200);
  sim.println("AT+CMGS=\"" + number + "\"\r"); 
  delay(200);
  sim.println(message);  
  delay(100);
  sim.println((char)26); 
  delay(200);
  _buffer = _readSerial();
  Serial.println("Sending message: " + message);
}

void RecieveMessage() {
  sim.println("AT+CMGF=1");
  delay(200);
  sim.println("AT+CNMI=1,2,0,0,0"); 
  delay(200);
  
  if (sim.available() > 0) {
    String receivedMessage = sim.readString();
    Serial.println("Received: " + receivedMessage);
    
    if (receivedMessage.indexOf("motor on") >= 0) 
    {
      digitalWrite(relayPin, HIGH); // Turn relay ON
      Serial.println("Relay ON");
    } 
    else if (receivedMessage.indexOf("motor off") >= 0) 
    {
      digitalWrite(relayPin, LOW); // Turn relay OFF
      Serial.println("Relay OFF");
    }
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
  Serial.println("Calling: " + number);
  delay(1000);
}
