#include<SPI.h>
#include<LoRa.h>
#include "DHT.h"

#define DHT_TYPE DHT11
#define DHT_PIN A0

#define NSS 10
#define RST 9
#define DIO0 2

DHT dht(DHT_PIN, DHT_TYPE);


void setup()
{
  Serial.begin(9600);
  dht.begin();
  LoRa.setPins(NSS,RST,DIO0);
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
