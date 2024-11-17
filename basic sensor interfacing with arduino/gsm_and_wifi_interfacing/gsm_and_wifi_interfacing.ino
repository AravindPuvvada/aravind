#include <dht.h>

#include <SoftwareSerial.h>
#define DHT11_PIN A1


SoftwareSerial wifi(8, 9);
SoftwareSerial sim800l(2,3);

String apiKey = "R79H7SCD5A3D7JSH";
dht DHT;

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
  int chk = DHT.read11(DHT11_PIN);
  SendWiFi_Data();
  if(DHT.temperature>32)
  {
    sendSMS("+919398594569",("Alert temperature is high"+String(DHT.temperature)).c_str());
    delay(1000);
  }
  if(DHT.humidity>60)
  {
    sendSMS("+919398594569",("Alert humidity is high"+String(DHT.temperature)).c_str());
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
