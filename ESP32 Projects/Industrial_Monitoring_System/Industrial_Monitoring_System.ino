#define BLYNK_TEMPLATE_ID "TMPL3t5upcit_"
#define BLYNK_TEMPLATE_NAME "DHT with esp32"
#define BLYNK_AUTH_TOKEN "_Y1p0zeSxw7Dt6uSGCyL4LCw7DXv3blc"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <LiquidCrystal.h> // Include the standard LCD library for parallel connection

int red = 22;          // Red LED pin
int green = 4;        // Green LED pin
int fan = 23;         // Fan pin
char auth[] = "_Y1p0zeSxw7Dt6uSGCyL4LCw7DXv3blc";
char ssid[] = "projectpulse";  // Type your Wi-Fi name
char pass[] = "hailucky123";   // Type your Wi-Fi password

#define DHTPIN 13               // Connect DHT Out pin to GPIO13 in ESP32
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

#define MQ2PIN 34               // Define MQ-2 analog pin (adjust according to your setup)

// Define LCD pins: (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(5, 14, 27, 26, 19, 21); // Initialize LCD

BlynkTimer timer;

void sendSensor()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  int mq2Value = analogRead(MQ2PIN); // Read analog value from MQ-2 sensor

  Blynk.virtualWrite(V0, temperature); // Send temperature to Blynk
  Blynk.virtualWrite(V1, humidity);    // Send humidity to Blynk
  Blynk.virtualWrite(V2, mq2Value);    // Send MQ-2 value to Blynk
  
  // Update LED and fan status to Blynk
  if (mq2Value > 3000)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Alert! Dangerous");
    lcd.setCursor(0, 1);
    lcd.print(" Gas detected");
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    Blynk.virtualWrite(V3, red);   // Send Red LED status to Blynk
    Blynk.virtualWrite(V4, green); // Send Green LED status to Blynk
    delay(1000);
  }
  else
  {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    Blynk.virtualWrite(V3, red);  // Send Red LED status to Blynk
    Blynk.virtualWrite(V4, green); // Send Green LED status to Blynk
  }

  if (temperature > 30)
  {
    digitalWrite(fan, HIGH);
    Blynk.virtualWrite(V5, fan);   // Send Fan status to Blynk
    delay(1000);
  }
  else
  {
    digitalWrite(fan, LOW);
    Blynk.virtualWrite(V5, fan);  // Send Fan status to Blynk
    delay(1000);
  }

  // Print the sensor values on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print(" H:");
  lcd.print(humidity);
  lcd.setCursor(0, 1);
  lcd.print("MQ2:");
  lcd.print(mq2Value);

  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.print("    Humidity : ");
  Serial.print(humidity);
  Serial.print("    MQ-2 Reading : ");
  Serial.println(mq2Value);
}

void setup()
{   
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  dht.begin();
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(fan, OUTPUT);
  
  // Initialize LCD
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows
  lcd.setCursor(0, 0);
  lcd.print("Industrial");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring Sys.");
  delay(2000); // Display project name for 2 seconds

  timer.setInterval(2000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
