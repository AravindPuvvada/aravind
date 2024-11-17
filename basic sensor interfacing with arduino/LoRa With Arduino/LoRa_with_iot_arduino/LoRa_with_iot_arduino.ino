#define BLYNK_TEMPLATE_ID "TMPL3uleUTqVV"
#define BLYNK_TEMPLATE_NAME "LoRa with Arduino"
#define BLYNK_AUTH_TOKEN "YusV8-iBh8OP8zNNm_yW9i2jcOf1ZoV-"
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <LoRa.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
// Your WiFi credentials
char ssid[] = "projectpulse";
char pass[] = "hailucky123";

#define EspSerial Serial

#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

#define LORA_FREQUENCY 868E6

#define LED_PIN 7

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  delay(10);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Blynk.run();
}
BLYNK_WRITE(V0) {
  int pinValue = param.asInt(); 
  digitalWrite(LED_PIN, pinValue); 
  LoRa.beginPacket();
  LoRa.print(pinValue);
  LoRa.endPacket();
  Serial.print("Sent via LoRa: ");
  Serial.println(pinValue);
}
