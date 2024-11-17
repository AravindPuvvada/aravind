#define BLYNK_TEMPLATE_ID "TMPL3uRsK0nph"
#define BLYNK_TEMPLATE_NAME "Servo with esp32"
#define BLYNK_AUTH_TOKEN "tA-FoV64eY6S4swxaJW8S1L3_CjTVOGX"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

char auth[] = "tA-FoV64eY6S4swxaJW8S1L3_CjTVOGX"; // Blynk authentication token
char ssid[] = "projectpulse"; // Your WiFi SSID
char pass[] = "hailucky123"; // Your WiFi password

Servo servo1;


void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  servo1.attach(4); // Attach servo 1 to GPIO 4
  
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V0) // Slider Widget for Servo 1 on V0
{
  int pos1 = param.asInt(); // Get value from slider
  servo1.write(pos1); // Set servo 1 position
  Blynk.virtualWrite(V1, pos1);
}
