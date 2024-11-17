#include <dht.h>
#include<LiquidCrystal.h>
#include <SoftwareSerial.h>
#define DHT11_PIN A5

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
SoftwareSerial wifi(8, 9);

int echo=5;
int trig=4;

String apiKey = "64I4PJ79G50E94SD";
dht DHT;

int ldr;
int mq;
int ultra;
long duration;
int distance;


void setup()
{
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
  lcd.clear();

  pinMode(trig,OUTPUT);
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  ldr=analogRead(A4);
  mq=analogRead(A3);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=duration * 0.034/2;
  
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
  getStr += String(DHT.humidity);
  getStr += "&field2=";
  getStr += String(DHT.temperature);
  getStr += "&field3=";
  getStr += String(ldr);
  getStr += "&field4=";
  getStr += String(distance);
  getStr += "&field5=";
  getStr += String(mq);
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  wifi.println(cmd);
  delay(1500);
  wifi.println(getStr);
  delay(1000);
}
