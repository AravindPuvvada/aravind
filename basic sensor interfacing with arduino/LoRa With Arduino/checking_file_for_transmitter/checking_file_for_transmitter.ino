#include <SPI.h>
#include <LoRa.h>

#define SS 10     // Pin for LoRa module NSS (Chip Select)
#define RST 9   // Pin for LoRa module RESET
#define DIO0 2   // Pin for LoRa module DIO0 (Interrupt)

void setup() {
  Serial.begin(9600);          // Initialize serial communication at 9600 bps
  while (!Serial);             // Wait for serial port to connect

  Serial.println("LoRa Sender");

  // Setup LoRa module
  LoRa.setPins(SS, RST, DIO0); // Set LoRa module pins
  if (!LoRa.begin(868E6)) {  // Initialize LoRa at 868 MHz
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  else
  {
    Serial.println("DONE");
  }
  
  

}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(millis());

  // Send packet
  LoRa.beginPacket();
  LoRa.print("Hello ");
  LoRa.print(millis());
  LoRa.endPacket();

  delay(5000); // Send a packet every second
}
