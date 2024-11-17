#define BLYNK_TEMPLATE_ID "TMPL3t5upcit_"
#define BLYNK_TEMPLATE_NAME "DHT with esp32"
#define BLYNK_AUTH_TOKEN "_Y1p0zeSxw7Dt6uSGCyL4LCw7DXv3blc"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
char auth[] = "_Y1p0zeSxw7Dt6uSGCyL4LCw7DXv3blc";
char ssid[] = "projectpulse";  // type your wifi name
char pass[] = "hailucky123";  // type your wifi password
#define DHTPIN 13 //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;


void sendSensor()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

    Blynk.virtualWrite(V0, temperature);
    Blynk.virtualWrite(V1, humidity);
    Serial.print("Temperature : ");
    Serial.print(temperature);
    Serial.print("    Humidity : ");
    Serial.println(humidity);
}
void setup()
{   

  Serial.begin(115200);


  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(2000L, sendSensor);
  
  }

void loop()
{
  Blynk.run();
  timer.run();
}
