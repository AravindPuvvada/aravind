#include<LiquidCrystal.h>
#include <SoftwareSerial.h>
#include<dht.h>

SoftwareSerial wifi(8, 9);
SoftwareSerial sim800l(2,3);


int value;
int value1;
int value2;
int value3;
int value4;

dht DHT;
#define DHT11_PIN A1

String apiKey = "83KIURQRRF9UQBZV";

void setup(){
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
}

void loop()
{
  value=analogRead(A1);

  int chk=DHT.read11(DHT11_PIN);
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


  if(DHT.temperature>30)
  {
    sendSMS("+919398594569", "(Alert Temperature is High:"+String(DHT.temperature)).c_str());
    delay(1000);
  }
  if(DHT.humidity>40)
  {
    sendSMS("+919398594569", ("Alert Humidity is high:"+String(DHT.humidity)).c_str());
    delay(1000);
  }
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

void sendSMS(const char* phoneNumber, const char* message) {
  sim800l.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  sim800l.print("AT+CMGS=\"");
  sim800l.print(phoneNumber);
  sim800l.println("\"");
  delay(1000);
  sim800l.print(message);
  sim800l.write(0x1A); // Send Ctrl+Z to finish message
  delay(1000);
}
