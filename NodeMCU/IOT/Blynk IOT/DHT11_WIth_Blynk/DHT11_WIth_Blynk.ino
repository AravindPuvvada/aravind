// Tech Trends Shameer
// Control DHT11 Sensor Data Using Blynk 2.0/Blynk IoT

#define BLYNK_TEMPLATE_ID "TMPL3YGPMfAuc"
#define BLYNK_TEMPLATE_NAME "DHT11"
#define BLYNK_AUTH_TOKEN "3VeuFlVXBcu5YbFjBbaa5eVilvVR3oCq"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Replace with your network credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "projectpulse";  // Enter your Wifi Username
char pass[] = "hailucky123";  // Enter your Wifi password

#define DHTPIN D4       // Pin connected to the DHT11 data pin
#define DHTTYPE DHT11   // Define the type of DHT sensor

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

void setup()
{     
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);    
  dht.begin(); // Start the DHT sensor
}

void loop()
{
  // Read temperature and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Send the humidity and temperature data to Blynk
  Blynk.virtualWrite(V1, humidity); // Virtual pin V1 for humidity
  Blynk.virtualWrite(V0, temperature); // Virtual pin V2 for temperature
  
  delay(2000); // Wait for 2 seconds between readings
    Blynk.run(); // Run Blynk

}
