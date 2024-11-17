#include<LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <dht.h>
#include <LiquidCrystal_I2C.h>
// Create instances for SoftwareSerial and LiquidCrystal
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial wifi(8, 9);
int Soil = A0;
#define DHT11_PIN A1
dht DHT;
int value;
int relay = 12;
String apiKey = "OGJ0STR8GBW5AWP0";
bool watermotor = false;
bool soildry = false;
void setup()
{
  pinMode(Soil, INPUT);
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
  
  lcd.init();            // Initialize the LCD
  lcd.backlight();
  project_name();
  lcd.setCursor(0,0);
  lcd.print("WiFi module     ");
  lcd.setCursor(0,1);
  lcd.print("Initilizing.... ");
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
  lcd.setCursor(0,0);
  lcd.print("  WiFi module     ");
  lcd.setCursor(0,1);
  lcd.print(" Initilized..... ");
  delay(1000);
  lcd.clear();

}

void loop() {
  value = analogRead(Soil);

  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature:");
  Serial.println(DHT.temperature);
  Serial.print("Humidity:");
  Serial.println(DHT.humidity);
  Serial.print("Soil-Value:");
  Serial.println(value);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:       H:      ");
  lcd.setCursor(2, 0);
  lcd.print(DHT.temperature);
  lcd.setCursor(11, 0);
  lcd.print(DHT.humidity);
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soil Value:");
  lcd.print(value);
  if(value>600)
  {
    digitalWrite(relay,HIGH);
    lcd.setCursor(3, 1);
    lcd.print("Motor On");
    delay(800);
    
  }
  else
  {
    digitalWrite(relay,LOW);
    lcd.setCursor(3, 1);
    lcd.print("Motor Off");
    delay(800);
    
  }
  SendWiFi_Data();
  lcd.clear();
}
void project_name()
{
  lcd.setCursor(5, 0);
  lcd.print("Smart");
  lcd.setCursor(0, 1);
  lcd.print("Irrigation Sys..");
  delay(3000);
  lcd.clear();
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
  getStr += String(DHT.humidity);
  getStr += "&field2=";
  getStr += String(DHT.temperature);
  
  getStr += "&field3=";
  getStr += String(value);
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  wifi.println(cmd);
  delay(1500);
  wifi.println(getStr);
  delay(1000);
  
}
