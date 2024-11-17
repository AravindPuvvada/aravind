#include<DHT.h>
#define DHT_TYPE DHT11
#define DHT_PIN 12

DHT dht(DHT_PIN,DHT_TYPE);
void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temp=dht.readTemperature();
  float hum=dht.readHumidity();
  Serial.print("Temperature:");
  Serial.println(temp);
  Serial.print("Humidity:");
  Serial.println(hum);
  delay(1000);
  
}
