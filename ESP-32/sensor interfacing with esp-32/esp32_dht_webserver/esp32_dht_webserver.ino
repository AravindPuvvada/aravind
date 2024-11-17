#include <WebServer.h>
#include <WiFi.h>
#include "DHT.h"

const char* ssid = "projectpulse";
const char* password = "hailucky123";

int LED_PIN = 2;
#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

void setup()
{
  Serial.begin(115200);
  dht.begin();
  pinMode(LED_PIN, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP Address is ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP Server Started");
}

void loop()
{
  server.handleClient();
}

void handleRoot()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  bool LED = (temperature > 40 || humidity > 60);

  if (LED)
  {
    digitalWrite(LED_PIN, HIGH); // Turn LED on
    delay(800);
  }
  else
  {
    digitalWrite(LED_PIN, LOW); // Turn LED off
    delay(800);
  }

  String ledState = LED ? "ON" : "OFF";

  // HTML webpage content
  String webpage = "<!DOCTYPE html><html><head><title>DHT11 Sensor Data</title>";
  webpage += "<style>";
  webpage += "body { background-color: #f0f0f0; font-family: Arial, sans-serif;}";
  webpage += ".container { max-width: 500px; margin: 0 auto; padding: 20px; background-color: #ffffff; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1);}";
  webpage += ".status { margin-top: 20px; text-align: center;}";
  webpage += ".status .temperature, .status .humidity { font-size: 24px; font-weight: bold;}";
  webpage += ".bulb { display: block; margin: 20px auto; width: 50px; height: 50px; background-color: ";
  webpage += LED ? "#ffcc00;" : "#cccccc;"; // Change bulb color based on condition
  webpage += "border-radius: 50%; box-shadow: 0 0 10px rgba(0,0,0,0.2);}";
  webpage += "</style>";
  webpage += "</head><body>";
  webpage += "<div class='container'>";
  webpage += "<h1 style='text-align: center;'>ESP32 DHT11 WEBSERVER</h1>";
  webpage += "<div class='status'>";
  webpage += "<p class='temperature'>Temperature: " + String(temperature) + " &deg;C</p>";
  webpage += "<p class='humidity'>Humidity: " + String(humidity) + " %</p>";
  webpage += "<div class='bulb'></div>";
  webpage += "</div></div></body></html>";

  server.send(200, "text/html", webpage);
}
