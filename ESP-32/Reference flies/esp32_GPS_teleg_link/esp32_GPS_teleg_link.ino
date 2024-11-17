#include <TinyGPS++.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <HTTPClient.h>

const char* ssid = "projectpulse";
const char* password = "hailucky123";

#define BOT_TOKEN "7223310266:AAH_pTQSeZPTmydouaC3J5_KkpZzyEoyObQ"
#define CHAT_ID "6241323443"

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
TinyGPSPlus gps;

volatile bool loc_valid = false;
double lat_val, lng_val;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Initializing GPS module...");
  
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Necessary for secure connections
}

void loop() {
  get_GPSData();
  if (loc_valid) {
    sendLocationToTelegram();
    sendTelegramMessage("Current location: " + String(lat_val, 6) + ", " + String(lng_val, 6) + "https://maps.google.com/?q=" + String(lat_val, 6) + "," + String(lng_val, 6));
    loc_valid = false; 
  }
  delay(1000); 
}

void sendLocationToTelegram() {
  String message = "https://maps.google.com/?q=" + String(lat_val, 6) + "," + String(lng_val, 6);
  
  Serial.print("Sending location to Telegram: ");
  Serial.println(message);

  bool messageSent = bot.sendMessage(CHAT_ID , message);

  if (messageSent) {
    Serial.println("Location sent to Telegram.");
  } else {
    Serial.println("Failed to send location to Telegram.");
  }

  delay(1000); 
}

void get_GPSData() {
  while (Serial.available() > 0) {
    if (gps.encode(Serial.read())) {
      if (gps.location.isValid()) {
        loc_valid = true;
        lat_val = gps.location.lat();
        lng_val = gps.location.lng();
        Serial.print("Latitude: ");
        Serial.println(lat_val, 6);
        Serial.print("Longitude: ");
        Serial.println(lng_val, 6);
      } else {
        loc_valid = false;
      }
    }
  }
}

void sendTelegramMessage(String message) {
  Serial.println("Sending message to Telegram...");
  
  HTTPClient http;
  
  String url = "https://api.telegram.org/bot";
  url += BOT_TOKEN;
  url += "/sendMessage?chat_id=";
  url += CHAT_ID;
  url += "&text=";
  url += message;
  
  http.begin(url);
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("Message sent successfully:");
      Serial.println(payload);
    } else {
      Serial.print("Error sending message. HTTP error code: ");
      Serial.println(httpCode);
    }
  } else {
    Serial.println("Unable to connect to Telegram API");
  }
  
  http.end();
}
