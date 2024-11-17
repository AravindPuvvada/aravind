#include<SPI.h>
#include<LoRa.h>

#define NSS 10
#define RST 9
#define DIO0 2
void setup()
{
  Serial.begin(9600);
  LoRa.setPins(NSS,RST,DIO0);
  while(!Serial)
  Serial.println("LoRa Receiver");
  if(!LoRa.begin(868E6))
  {
    Serial.println("Starting LoRa Failed");
  }
  else
  {
    Serial.println("Intialized Successfully");
  }
}
void loop()
{
  int packetsize=LoRa.parsePacket();
  if(packetsize)
  {
    Serial.println("");
    Serial.println("Received Packet:");
    while(LoRa.available())
    {
      char incoming=(char)LoRa.read();
      if(incoming)
      {
        Serial.print(incoming);
      }
    }
  }
}
