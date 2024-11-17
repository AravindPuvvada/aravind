#define BLYNK_TEMPLATE_ID "TMPL3OyvB85WU"
#define BLYNK_TEMPLATE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "AM2Mwh1JoGFMC-D8FSKe0bGsUoqDGT9V"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
char auth[] = "AM2Mwh1JoGFMC-D8FSKe0bGsUoqDGT9V";
char ssid[] = "projectpulse";  // Type your Wi-Fi name
char pass[] = "hailucky123";   // Type your Wi-Fi password


#include <DHT.h>

#define DHTPIN 13
#define DHTTYPE DHT11
#define MQ2_PIN 34
#define LDR_PIN 35
#define PIR_PIN 32
#define RELAY_LDR_PIN 27
#define RELAY_PIR_PIN 2
#define BUZZER_PIN 25
int fan=4;

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_LDR_PIN, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(RELAY_PIR_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(RELAY_LDR_PIN, LOW);
  digitalWrite(RELAY_PIR_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  timer.setInterval(2000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
  
}
void sendSensor()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int mq2Value = analogRead(MQ2_PIN);
  int ldrValue = analogRead(LDR_PIN);
  int pirValue = digitalRead(PIR_PIN);
   Blynk.virtualWrite(V0, temperature); // Send temperature to Blynk
  Blynk.virtualWrite(V1, humidity);    // Send humidity to Blynk
  Blynk.virtualWrite(V3, mq2Value); 
  Blynk.virtualWrite(V2, ldrValue); 
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, MQ-2 Value: ");
  Serial.print(mq2Value);
  Serial.print(", LDR Value: ");
  Serial.print(ldrValue);
  Serial.print(", PIR Motion Detected: ");
  Serial.println(pirValue == LOW? "Yes" : "No");

  if (temperature > 30) {
    digitalWrite(fan, HIGH);
  } else {
    digitalWrite(fan, LOW);
  }
  if (ldrValue > 3000) {
    digitalWrite(RELAY_LDR_PIN, HIGH);
  } else {
    digitalWrite(RELAY_LDR_PIN, LOW);
  }

  if (pirValue == LOW) {
    digitalWrite(RELAY_PIR_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIR_PIN, LOW);
  }

  if (mq2Value > 3500) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(2000);
}
