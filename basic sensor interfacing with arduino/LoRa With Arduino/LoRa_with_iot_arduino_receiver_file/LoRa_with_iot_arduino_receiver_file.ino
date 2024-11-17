#include <SPI.h>
#include <LoRa.h>

#define NSS 10
#define RST 9
#define DIO0 2

int led = 4;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  while (!Serial); // Optional: Wait for Serial connection
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa Failed");
    while (1);
  }
  Serial.println("Initialized Successfully");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.println("Packet received!");

    String receivedValue = "";
    while (LoRa.available()) {
      receivedValue += (char)LoRa.read();
    }
    
    Serial.print("Received value: ");
    Serial.println(receivedValue);

    // Use the received value to control the LED
    if (receivedValue == "1") {
      digitalWrite(led, HIGH); // Turn on LED if received value is "0"
      Serial.println("LED ON");
    } else if (receivedValue == "0") {
      digitalWrite(led, LOW);  // Turn off LED if received value is "1"
      Serial.println("LED OFF");
    } else {
      Serial.println("Unexpected data received.");
    }

  }
}
