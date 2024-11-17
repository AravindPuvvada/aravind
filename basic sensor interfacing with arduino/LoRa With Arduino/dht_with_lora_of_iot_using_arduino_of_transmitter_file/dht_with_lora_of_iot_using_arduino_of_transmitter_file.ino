#define BLYNK_TEMPLATE_ID "TMPL304Tf8L5c"
#define BLYNK_TEMPLATE_NAME "Dht with arduino"
#define BLYNK_AUTH_TOKEN "yhNxknsy90C8jcoS2isNfhbYAULy6B86"

#include<SPI.h>
#include<LoRa.h>
#include "DHT.h"

#define DHT_TYPE DHT11
#define DHT_PIN A0

#define NSS 10
#define RST 9
#define DIO0 2

#define BLYNK_PRINT Serial
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

DHT dht(DHT_PIN, DHT_TYPE);


void setup()
{
  Serial.begin(9600);
  dht.begin();
  LoRa.setPins(NSS,RST,DIO0);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
  while(!Serial)
  Serial.println("LoRa Sender");
  if(!LoRa.begin(868E6))
  {
    Serial.println("Starting LoRa Failed");
  }
  else
  {
    Serial.println("Intiliazed Successfully");
  }
}

void loop()
{

  float temp=dht.readTemperature();
  float hum=dht.readHumidity();
  Blynk.run();
  Blynk.virtualWrite(V0,temp);
  Blynk.virtualWrite(V1,hum);
  Serial.println("Sending Packet");
  LoRa.beginPacket();
  LoRa.print("Temperature:");
  LoRa.print(temp);
  LoRa.print("c");
  LoRa.print("  Humidity:");
  LoRa.print(hum);
  LoRa.print("%");

  Serial.print("Temparature:");
  Serial.println(temp);
  Serial.print("Humidity:");
  Serial.println(hum);
  LoRa.endPacket();
  delay(3000);
}
