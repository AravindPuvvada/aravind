#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Enter your Auth token
char auth[] = "UiJU5paG90HlIGnrGIbmbbj6-bmqg-07";

//Enter your WIFI SSID and password
char ssid[] = "projectpulse";
char pass[] = "hailucky123";

#define BLYNK_TEMPLATE_ID "TMPL33PHRepdZ"
#define BLYNK_TEMPLATE_NAME "LEDS controlling with esp32"
#define BLYNK_AUTH_TOKEN "UiJU5paG90HlIGnrGIbmbbj6-bmqg-07"

void setup(){
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop(){
  Blynk.run();
}
