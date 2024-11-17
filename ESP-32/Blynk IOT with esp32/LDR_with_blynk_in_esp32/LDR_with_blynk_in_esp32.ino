#define BLYNK_TEMPLATE_ID "TMPL3M_T-e-0C"
#define BLYNK_TEMPLATE_NAME "ldr sensor"
#define BLYNK_AUTH_TOKEN "jfb5GhaEDePlP4WvcTLzJJANpmI26c9e"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "projectpulse";  // type your WiFi name
char pass[] = "hailucky123";  // type your WiFi password

#define LDR_PIN 34 // Define the pin for the LDR
int led=2;

BlynkTimer timer;

void sendSensor()
{
    int ldrValue = analogRead(LDR_PIN); 
    Blynk.virtualWrite(V0, ldrValue); 
    Serial.print("LDR: ");
    Serial.println(ldrValue);
    if(ldrValue>3500)
    {
      Blynk.logEvent("ligth_alert","LED ON"); 
      Serial.println("Email Sent");
      digitalWrite(led,HIGH);
    }
    else
    {
      digitalWrite(led,LOW);
    }
}

void setup()
{
  pinMode(led,OUTPUT);   
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, sendSensor); // Set a timer to call sendSensor every 2 seconds
}

void loop()
{
  Blynk.run();
  timer.run();
}
