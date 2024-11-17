#include <dht.h>
#include <SoftwareSerial.h>
#define DHT11_PIN A0
SoftwareSerial wifi(8,9);

String apiKey = "JG1GG1KWFO9JFKXG";
dht DHT;
int soil=A1;
int gas=A2;
int water=A3;
int value,val,v;
int motor=2,fan=3;
void setup(){
  pinMode(motor,OUTPUT);
  pinMode(fan,OUTPUT);
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
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature:");
  Serial.println(DHT.temperature);
  Serial.print("Humidity:");
  Serial.println(DHT.humidity); 
  SendWiFi_Data();
  value=analogRead(soil);
  val=analogRead(gas);
  v=analogRead(water);
  if(value>600)
  {
    digitalWrite(motor,HIGH);
  }
  else
  {
    digitalWrite(motor,LOW);
  }
  if(DHT.temperature>30)
  {
    digitalWrite(fan,HIGH);
  }
  else
  {
    digitalWrite(fan,LOW);
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
  getStr += String(DHT.temperature);
  getStr += "&field2=";
  getStr += String(DHT.humidity);
  getStr += "&field3=";
  getStr += String(value);
  getStr += "&field4=";
  getStr += String(val);
  getStr += "&field5=";
  getStr += String(v);
  
  
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
