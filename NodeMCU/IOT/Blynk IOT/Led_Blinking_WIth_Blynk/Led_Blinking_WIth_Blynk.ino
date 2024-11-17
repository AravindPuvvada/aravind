//Tech Trends Shameer
//Control LED Using Blynk 2.0/Blynk IoT

#define BLYNK_TEMPLATE_ID "TMPL3Kh2OqfdT"
#define BLYNK_TEMPLATE_NAME "LED Blynk"
#define BLYNK_AUTH_TOKEN "mcXCl4Z5Y3AVgkGv3p7UBvot1ObSTNQ-"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "projectpulse";  // Enter your Wifi Username
char pass[] = "hailucky123";  // Enter your Wifi password

int ledpin = D0;  // LED pin

// This function will be called every time the virtual pin V1 changes
BLYNK_WRITE(V0) {
  int ledState = param.asInt(); // Get the state of the button from the Blynk app
  digitalWrite(ledpin, ledState); // Set the LED state
}

void setup()
{     
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);    
  pinMode(ledpin, OUTPUT); // Set the LED pin as an output
}

void loop()
{
  Blynk.run(); 
}
