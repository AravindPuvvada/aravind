#include <SoftwareSerial.h>

SoftwareSerial BTSerial(0, 1); // RX, TX

const int fanPin = 12;
const int lightPin = 13;
char terminalRead;  // Variable to read data

void setup() {
  pinMode(fanPin, OUTPUT);
  pinMode(lightPin, OUTPUT);

  BTSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // Check if there is Bluetooth input
  if (BTSerial.available()) {
    String command = BTSerial.readStringUntil('\n');
    command.trim();

    // Voice Commands
    if (command.equalsIgnoreCase("LIGHT ON")) {
      digitalWrite(lightPin, HIGH);  // Turn Light ON
      Serial.println("Light is ON");
    } 
    else if (command.equalsIgnoreCase("LIGHT STOP")) {
      digitalWrite(lightPin, LOW);   // Turn Light STOP (formerly OFF)
      Serial.println("Light is STOPPED");
    } 
    else if (command.equalsIgnoreCase("FAN ON")) {
      digitalWrite(fanPin, HIGH);    // Turn Fan ON
      Serial.println("Fan is ON");
    } 
    else if (command.equalsIgnoreCase("FAN STOP")) {
      digitalWrite(fanPin, LOW);     // Turn Fan STOP (formerly OFF)
      Serial.println("Fan is STOPPED");
    } 
    else if (command.equalsIgnoreCase("ALL ON")) {
      digitalWrite(lightPin, HIGH);  // Turn Light ON
      digitalWrite(fanPin, HIGH);    // Turn Fan ON
      Serial.println("All devices are ON");
    } 
    else if (command.equalsIgnoreCase("ALL STOP")) {
      digitalWrite(lightPin, LOW);   // Turn Light STOP (formerly OFF)
      digitalWrite(fanPin, LOW);     // Turn Fan STOP (formerly OFF)
      Serial.println("All devices are STOPPED");
    }
  }

  // Check if there is input from buttons
  if (Serial.available() > 0) {
    terminalRead = Serial.read();  // Read whatever data is received

    // Button commands
    if (terminalRead == '1') {
      digitalWrite(lightPin, HIGH);  // Turn Light ON
      Serial.println("Light is ON");
    } 
    else if (terminalRead == '2') {
      digitalWrite(lightPin, LOW);   // Turn Light STOP (formerly OFF)
      Serial.println("Light is STOPPED");
    } 
    else if (terminalRead == '3') {
      digitalWrite(fanPin, HIGH);    // Turn Fan ON
      Serial.println("Fan is ON");
    } 
    else if (terminalRead == '4') {
      digitalWrite(fanPin, LOW);     // Turn Fan STOP (formerly OFF)
      Serial.println("Fan is STOPPED");
    } 
    else if (terminalRead == '5') {
      digitalWrite(lightPin, HIGH);  // All ON
      digitalWrite(fanPin, HIGH);
      Serial.println("All devices are ON");
    } 
    else if (terminalRead == '6') {
      digitalWrite(lightPin, LOW);   // All STOP (formerly OFF)
      digitalWrite(fanPin, LOW);
      Serial.println("All devices are STOPPED");
    }
  }
}
