#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Enter your Auth token
char auth[] = "_5d4FYTCOxhTGehIELWeGHDcj4EroXD4";

//Enter your WIFI SSID and password
char ssid[] = "projectpulse";
char pass[] = "hailucky123";

void setup(){
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop(){
  Blynk.run();
}
