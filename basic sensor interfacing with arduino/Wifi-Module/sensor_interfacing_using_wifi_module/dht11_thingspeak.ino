#include<LiquidCrystal.h>
#include <SoftwareSerial.h>
#include<dht.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
SoftwareSerial wifi(8, 9);


int value;
int value1;
int value2;
int value3;
int value4;

dht DHT;
#define DHT11_PIN A1

String apiKey = "83KIURQRRF9UQBZV";

void setup(){
  lcd.begin(16, 2);
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

}

void loop()
{
  value=analogRead(A0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ldr:");
  lcd.setCursor(4,0);
  lcd.print(value);
  delay(2000);
  lcd.clear();

  int chk=DHT.read11(DHT11_PIN);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T:      H:");
  lcd.setCursor(2,0);
  lcd.print(DHT.temperature);
  lcd.setCursor(11,0);
  lcd.print(DHT.humidity);
  delay(2000);
  lcd.clear();

  value1=analogRead(A2);
  lcd.setCursor(0,0);
  lcd.print("Water-Level:");
  lcd.setCursor(12,0);
  lcd.print(value1);
  delay(2000);

  value2=analogRead(A3);
  lcd.setCursor(0,0);
  lcd.print("Rain-Sensor:");
  lcd.setCursor(12,0);
  lcd.print(value2);
 

  value3=analogRead(A4);
  lcd.setCursor(0,0);
  lcd.print("Soil Sensor:");
  lcd.setCursor(12,0);
  lcd.print(value3);

  value4=analogRead(A5);
  lcd.setCursor(0,0);
  lcd.print("MQ-7:");
  lcd.setCursor(5,0);
  lcd.print(value4);
  
  SendWiFi_Data();
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
  getStr += String(value);
  getStr += "&field2=";
  getStr += String(DHT.humidity);
  getStr += "&field3=";
  getStr += String(DHT.temperature);
  getStr += "&field4=";
  getStr += String(value1);
  getStr += "&field5=";
  getStr += String(value2);
  getStr += "&field6=";
  getStr += String(value3);
  getStr += "&field7=";
  getStr += String(value4);
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  wifi.println(cmd);
  delay(1500);
  wifi.println(getStr);
  delay(1000);
}
