#include <WiFi.h>
#include <ThingESP.h>

ThingESP32 thing("Aravind", "ldrvalues", "message");

int LED = 2;
int ldr = 34;

unsigned long previousMillis = 0;
const long INTERVAL = 6000;

void setup() {
  Serial.begin(115200);
  pinMode(ldr, INPUT);
  pinMode(LED, OUTPUT);
  thing.SetWiFi("projectpulse", "hailucky123");
  thing.initDevice();
}

String HandleResponse(String query) {

  int value = analogRead(ldr);
  Serial.print("LDR value: ");
  Serial.println(value); // Debugging statement to print the LDR value
  Serial.print("Received query: ");
  Serial.println(query); // Debugging statement to print the received query
  if(value>3000)
  {
    return String(value);
  }
  else{
    return "value not exceeds";
  }
}

void loop() {
  thing.Handle();
  delay(1000);
}
