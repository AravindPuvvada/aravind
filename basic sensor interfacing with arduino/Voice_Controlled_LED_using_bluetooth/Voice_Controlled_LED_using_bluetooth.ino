#include <SoftwareSerial.h>

SoftwareSerial BTSerial(0, 1); // RX, TX

const int ledPin = 12;

void setup() {
  pinMode(ledPin, OUTPUT);
  BTSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (BTSerial.available()) {
    String command = BTSerial.readStringUntil('\n');
    command.trim();

    if (command.equalsIgnoreCase("switch on the LED")) {
      digitalWrite(ledPin, HIGH);  // Turn LED ON
      Serial.println("LED is ON");
    } 
    else if (command.equalsIgnoreCase("Switch OFF The Led")) {
      digitalWrite(ledPin, LOW);   // Turn LED OFF
      Serial.println("LED is OFF");
    }
  }
}
