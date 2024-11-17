#include<DHT.h>
#define DHT_TYPE DHT11
#define DHT_PIN A0
DHT dht(DHT_PIN,DHT_TYPE);
int soil=A1;
int ldr=A2;
int led=8;
int r1=2;
int r2=3;
void setup() {
  dht.begin();
  Serial.begin(9600);
  pinMode(soil,INPUT);
  pinMode(r1,OUTPUT);
  pinMode(led,OUTPUT);
}

void loop() {
  
  float temp=dht.readTemperature();
  Serial.print("Temperature:");
  Serial.print(temp);
  Serial.println("c");

  //dht block
  float hum=dht.readHumidity();
  Serial.print("Humidity:");
  Serial.println(hum);
  delay(2000);
  if(hum>50)
  {
    digitalWrite(led,HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(led,LOW);
  }

  // soil moisture block
  int value=analogRead(soil);
  Serial.print("soil Sensor:");
  Serial.println(value);
  if(value>250)
  {
    digitalWrite(r1,HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(r1,LOW);
  }
  
  //ldr block
  int val=analogRead(ldr);
  Serial.print("ldr value:");
  Serial.println(val);
  if(val>600)
  {
    digitalWrite(r2,HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(r2,LOW);
  }
  
}
