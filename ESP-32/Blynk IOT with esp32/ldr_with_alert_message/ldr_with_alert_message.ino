#define BLYNK_TEMPLATE_ID "TMPL3dNtbm1Yu"
#define BLYNK_TEMPLATE_NAME "LDR with alert message"
#define BLYNK_AUTH_TOKEN "eZevgjMS6A_E97Q7YyN0KBfocZuY9Imr"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "eZevgjMS6A_E97Q7YyN0KBfocZuY9Imr";
char ssid[] = "projectpulse";  // type your wifi name
char pass[] = "hailucky123";  // type your wifi password

#define LDR_PIN  34
BlynkTimer timer;
int led=2;

// Virtual Pin for LDR
#define VIRTUAL_PIN V0

void notifyligths() {
  int ldrvalue = analogRead(LDR_PIN);
  Serial.print("LDR:");
  Serial.println(ldrvalue);
  Blynk.virtualWrite(V0, ldrvalue);

  if (ldrvalue > 3500) {
    digitalWrite(led,HIGH);
    Serial.println("Lights are on");
    Blynk.email("aravindpuvvada196@gmail.com", "Alert", "Lights are on");
    Serial.println("Email sent");
    Blynk.logEvent("LDR with alert message", "Ligths on");
    Serial.println("Event logged");
  }
  else
  {
    digitalWrite(led,LOW);
    
  }

  // Send LDR value to Blynk app
  Blynk.virtualWrite(VIRTUAL_PIN, ldrvalue);
}

void setup() {
  pinMode(LDR_PIN, INPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  if (Blynk.connected()) {
    Serial.println("Blynk connected");
  } else {
    Serial.println("Blynk not connected");
  }

  timer.setInterval(2500L, notifyligths);
}

void loop() {
  Blynk.run();
  timer.run();
}
