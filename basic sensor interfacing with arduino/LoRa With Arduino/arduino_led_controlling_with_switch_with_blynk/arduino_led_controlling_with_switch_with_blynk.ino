#define BLYNK_TEMPLATE_ID "TMPL3uleUTqVV"
#define BLYNK_TEMPLATE_NAME "LoRa with Arduino"
#define BLYNK_AUTH_TOKEN "YusV8-iBh8OP8zNNm_yW9i2jcOf1ZoV-"

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

// Define pins for the LED and push button
#define LED_PIN 2
#define PUSH_BUTTON_PIN 3

void setup()
{
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Set the push button pin as input with internal pull-up resistor
  pinMode(PUSH_BUTTON_PIN, INPUT_PULLUP);

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
  // Read the state of the push button
  int buttonState = digitalRead(PUSH_BUTTON_PIN);

  // Control the LED based on the push button state
  if (buttonState == LOW) {
    digitalWrite(LED_PIN, HIGH);
    delay(1500);// Turn LED ON when button is pressed
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn LED OFF when button is not pressed
  }

  // Send the LED state to Blynk virtual pin V0
  Blynk.virtualWrite(V0, digitalRead(LED_PIN));
    delay(1000);
}

// This function will be called every time
// when App button is pushed in SWITCH mode
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // Get the state of the button (0 or 1)
  digitalWrite(LED_PIN, pinValue); // Set the LED to the button's state
  delay(1500);
}
