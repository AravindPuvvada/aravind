#include<LiquidCrystal.h>
#include <SoftwareSerial.h>


LiquidCrystal lcd(10,11, 4, 5, 6, 7);
SoftwareSerial wifi(8, 9);

String apiKey = "PQV3F1Z35STOX3ZX";


int trig=2;
int echo=3;
int distance;
long duration;

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(trig,OUTPUT);
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

void loop()
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=duration*0.034/2;
  Serial.print("Distance:");
  Serial.print(distance);
  Serial.println("cm");
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
  getStr += "&field3=";
  getStr += String(distance);
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  wifi.println(cmd);
  delay(1500);
  wifi.println(getStr);
  delay(1000);
}
