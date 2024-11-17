#include<SPI.h>
#include<LoRa.h>

#define NSS 10
#define RST 9
#define DIO0 2

int sw=3;

void setup()
{
  pinMode(sw,INPUT);
  Serial.begin(9600);
  
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
  int val=digitalRead(sw);
  Serial.println("Sending Packet");
  LoRa.beginPacket();
  LoRa.print(val);
  LoRa.endPacket();
  delay(3000);
}
