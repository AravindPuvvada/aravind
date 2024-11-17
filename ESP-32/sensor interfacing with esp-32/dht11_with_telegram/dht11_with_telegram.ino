#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define DHTPIN 13
#define DHTTYPE DHT11

#define BOT_TOKEN "7223310266:AAH_pTQSeZPTmydouaC3J5_KkpZzyEoyObQ"
#define CHAT_ID "6241323443"

const char* ssid = "projectpulse";
const char* password = "hailucky123";

WiFiServer server(80);

DHT dht(DHTPIN, DHTTYPE);
float temperature;
float humidity;
void setup() {
  Serial.begin(115200);
  delay(1000);
  dht.begin();
   WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
    
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C ");
  Serial.print("__________");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %\t");
  
  if (temperature > 20.0 || humidity > 20.0) {
    sendTelegramMessage(humidity,temperature);
  }

  delay(5000); 
}
void sendTelegramMessage(float humidity,float temperature) {
  Serial.println("Sending message to Telegram...");
  HTTPClient http;
  String message = "Humidity detected: " + String(humidity) + "%";  
  String message1 = "Temperature detected: " + String(temperature) + "c";
  String url = "https://api.telegram.org/bot" + String(BOT_TOKEN) + "/sendMessage?chat_id=" + String(CHAT_ID) + "&text=" + message;
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) 
    {
      String payload = http.getString();
      Serial.println(payload);
    }
  }
  http.end();



 
  message = "Temperature detected: " + String(temperature) + "°C";
  url = "https://api.telegram.org/bot" + String(BOT_TOKEN) + "/sendMessage?chat_id=" + String(CHAT_ID) + "&text=" + message;
  http.begin(url);
  httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.println("Error: " + String(httpCode));
    }
  } else {
    Serial.println("Error on HTTP request: " + http.errorToString(httpCode));
  }
  http.end();
}
