#include <SPI.h>
#include <LoRa.h>

#define NSS 10
#define RST 9
#define DIO0 2
#define LED_PIN 4 // Define the LED pin

void setup() {
  Serial.begin(9600);
  while (!Serial);

  LoRa.setPins(NSS, RST, DIO0);
  
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  } else {
    Serial.println("Initialized successfully");
  }

  pinMode(LED_PIN, OUTPUT); // Initialize LED pin as output
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet: '");

    // read packet
    String receivedText = "";
    while (LoRa.available()) {
      receivedText += (char)LoRa.read();
    }
    Serial.print(receivedText);

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());

    // Parse humidity from the received packet
    int humIndex = receivedText.indexOf("Humidity:");
    if (humIndex != -1) {
      String humStr = receivedText.substring(humIndex + 9, receivedText.indexOf("%", humIndex));
      float humidity = humStr.toFloat();

      Serial.print("Extracted Humidity: ");
      Serial.println(humidity);

      // Check if humidity exceeds 60%
      if (humidity > 60) {
        digitalWrite(LED_PIN, HIGH); // Turn on LED
      } else {
        digitalWrite(LED_PIN, LOW);  // Turn off LED
      }
    } else {
      // If no humidity data found, turn off the LED
      digitalWrite(LED_PIN, LOW);
    }
  }
}
