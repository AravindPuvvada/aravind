#define BLYNK_TEMPLATE_ID "TMPL3IjG8wT-s"
#define BLYNK_TEMPLATE_NAME "LED Blynk"
#define BLYNK_AUTH_TOKEN "PeLf5wRE_GX6iAOyQgTGo5oUuwhaT7c7"

#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// Replace with your Blynk Auth Token
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials
char ssid[] = "projectpulse";
char pass[] = "hailucky123";

// Set your ESP8266 Serial object
#define EspSerial Serial

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

void setup()
{
  // Set the LED pin as output
  pinMode(10, OUTPUT);

  // Debug console
  Serial.begin(9600);
  delay(10);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  // Blynk setup
  Blynk.begin(auth, wifi, ssid, pass);
}

void loop()
{
  Blynk.run();
}

// This function will be called every time
// when App button is pushed in SWITCH mode
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // Get the state of the button (0 or 1)
  digitalWrite(10,pinValue);    // Set the LED to the button's state
}
