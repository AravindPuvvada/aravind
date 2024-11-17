#include <dht.h>
#include <SoftwareSerial.h>

#define DHT11_PIN A0
SoftwareSerial sim800l(10, 11); // RX, TX

SoftwareSerial wifi(8, 9);


String apiKey = "5PDLFQ8TZJ5U78YI";
dht DHT;
int value;
int val1;
int val;
int val2;
int val3;
int val4;

int trig=5;
int echo=7;
int distance;
long duration;


void setup(){
  Serial.begin(9600);
  sim800l.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  wifi.begin(115200);
  Serial.println("Wifi Module is Initializing.....");
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
  Serial.println("Wifi Module is Intialized");
  delay(700);
  delay(1000);

  
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  value=analogRead(A1);
  val=analogRead(A2);
  val2=analogRead(A3);
  val3=analogRead(A4);
  val4=analogRead(A5);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  duration=pulseIn(echo,HIGH);
  distance=duration*0.034/2;
  Serial.print("Temperature:");
  Serial.println(DHT.temperature);
  Serial.print("Humidity:");
  Serial.println(DHT.humidity);
  Serial.print("LDR:");
  Serial.println(value);
  Serial.print("Water-Level:");
  Serial.println(val);
  Serial.print("Rain-Sensor:");
  Serial.println(val2);
  //Serial.print("MQ-7:");
  //Serial.println(val3);
  delay(500);
  SendWiFi_Data();
  
  if(DHT.temperature>30)
  {
    sendSMS("+919398594569",("Alert Temperature is High"+String(DHT.temperature)).c_str());
    delay(3000);
    Serial.println("SMS of temp is Sent");
  }
  if(DHT.humidity>55)
  {
    sendSMS("+919398594569",("Alert Humidity is high"+String(DHT.humidity)).c_str());
    delay(3000);
    Serial.println("SMS of hum is Sent");
  }
  if(value>600)
  {
    sendSMS("+919398594569",("Alert Turn On the Ligths"+String(value)).c_str());
    delay(3000);
    Serial.println("SMS of ldr is Sent");
  }
  if(val>450)
  {
    sendSMS("+919398594569",("Alert Water level is high"+String(val)).c_str());
    delay(3000);
    Serial.println("SMS of water-level is Sent");
  }
  if(val2<300)
  {
    sendSMS("+919398594569",("Alert Rain is High"+String(val2)).c_str());
    delay(3000);
    Serial.println("SMS of rain-sensor  is Sent");
  }
  
}

void SendWiFi_Data() 
{
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
  getStr += String(val);

  getStr += "&field5=";
  getStr += String(val2);

  getStr += "&field6=";
  getStr += String(val3);

  getStr += "&field7=";
  getStr += String(val4);
  
  getStr += "&field8=";
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
