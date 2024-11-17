#include <dht.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define DHT11_PIN A0
#define mq7n A1
int buzzer=10;
SoftwareSerial wifi(8, 9);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

String apiKey = "REZ9ZAXCBGE1DQLN";
dht DHT;
int valn;

void setup() {
  lcd.begin(16, 2); // 16 columns, 2 rows
  lcd.setCursor(0, 0);
  lcd.print(" Air Pollution");
  lcd.setCursor(0, 1);
  lcd.print("   Monitoring...");
  pinMode(buzzer,HIGH);
  delay(2000); // Show the title for 2 seconds
  Serial.begin(9600);
  wifi.begin(115200);
  wifi.println("AT+RST");
  delay(4000);
  wifi.println("AT+CWMODE=3");
  delay(4000);
  wifi.print("AT+CWJAP=");
  wifi.write('"');
  wifi.print("projectpulse");
  wifi.write('"');
  wifi.write(',');
  wifi.write('"');
  wifi.print("hailucky123");
  wifi.write('"');
  wifi.println();
  delay(1000);

  // Initialize LCD
  
  lcd.clear();
}

void loop() {
  int chk = DHT.read11(DHT11_PIN);
  valn = analogRead(mq7n);

  // Print data to Serial Monitor
  Serial.print("Temperature: ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity: ");
  Serial.println(DHT.humidity);
  Serial.print("Gas Value: ");
  Serial.println(valn);
  lcd.clear();
  // Display data on LCD
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(DHT.temperature);
  lcd.print(" C");

  lcd.setCursor(9, 0);
  lcd.print("H:");
  lcd.print(DHT.humidity);
  lcd.print(" %");
  lcd.setCursor(0, 1);
  lcd.print("Gas: ");
  lcd.print(valn);
  delay(1000);
  if(valn>400)
  {
    digitalWrite(buzzer,HIGH);
    lcd.clear();
    lcd.print("Alert! Dangerous");
    lcd.setCursor(0,1);
    lcd.print(" Gas Detected"); 
    delay(1000);}
    else
    {
      digitalWrite(buzzer,LOW);
    }
  SendWiFi_Data(); // Send data to ThingSpeak
}

void SendWiFi_Data() {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  wifi.println(cmd);
  delay(1500);

  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr += "&field1=";
  getStr += String(DHT.temperature);
  getStr += "&field2=";
  getStr += String(DHT.humidity);
  getStr += "&field3=";
  getStr += String(valn);

  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  wifi.println(cmd);
  delay(1500);
  wifi.println(getStr);
  delay(1000);
  Serial.println("Data Sent");
}
