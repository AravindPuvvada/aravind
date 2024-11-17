#include <dht.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define DHT11_PIN A0

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
SoftwareSerial wifi(10,11);
SoftwareSerial sim800l(8, 9);

String apiKey = "K7Y457T5021TZ3Q9";
dht DHT;

int ldr = A1;
int val;
int led=A4;
int led2=A5;

int waterlevel = A3;
int val3;

int relay = 12;
int relay1 = 13;

int soil = A2;
int val2;

bool motorOnSent = false;
bool tankFullSent = false;

bool watermotor = false;
bool soildry = false;

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(led2,OUTPUT);
  digitalWrite(led,LOW);
  digitalWrite(relay, LOW);
  digitalWrite(relay1, LOW);
  lcd.begin(16,2);
  project_name();
  lcd.setCursor(0, 0);
  Serial.begin(9600); // Start serial communication with PC
  Serial.println("WiFi Module is Initializing...........");
  sim800l.begin(9600);
  lcd.clear();
  lcd.print("WiFi module     ");
  lcd.setCursor(0, 1);
  lcd.print("Initializing.... ");
  wifi.begin(115200);
  wifi.println("AT+RST");
  delay(4000);
  wifi.println("AT+CWMODE=3");
  delay(4000);
  wifi.print("AT+CWJAP=");
  wifi.write('"');
  wifi.print("Vivo T1");
  wifi.write('"');
  wifi.write(',');
  wifi.write('"');
  wifi.print("12345678");
  wifi.write('"');
  wifi.println();
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("  WiFi module     ");
  lcd.setCursor(0, 1);
  lcd.print(" Initialized..... ");
  Serial.println("WiFi Module is Initialized");
  delay(1000);
  lcd.clear();
}

void loop() {
  int chk = DHT.read11(DHT11_PIN);
  val = analogRead(ldr);
  val2 = analogRead(soil);
  val3 = analogRead(waterlevel);

  Serial.print("Temperature: ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity: ");
  Serial.println(DHT.humidity);
  Serial.print("ldr: ");
  Serial.println(val);
  Serial.print("Water-level: ");
  Serial.println(val3);
  Serial.print("Soil: ");
  Serial.println(val2);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.setCursor(2, 0);
  lcd.print(DHT.temperature);
  lcd.setCursor(9, 0);
  lcd.print("H:");
  lcd.setCursor(11,0);
  lcd.print(DHT.humidity);
  lcd.setCursor(4,1);
  lcd.print("LDR:");
  lcd.setCursor(8,1);
  lcd.print(val);
  delay(1500);
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("Soil:");
  lcd.setCursor(8,1);
  lcd.print(val2);
  lcd.setCursor(0,0);
  lcd.print("Water-level:");
  lcd.setCursor(12,0);
  lcd.print(val3);
  if (val2 >=350 && !watermotor) {
    sendSMS("+919398594569", "Soil is Dry Water Pump is On");
    delay(2000);
    watermotor = true; // Set flag to avoid resending
    digitalWrite(relay1, HIGH);
  }

  if (val2 < 400 && watermotor && !soildry ) {
    sendSMS("+919398594569", "water pump is Off. Soil is wet");
    delay(2000);
    soildry  = true; // Set flag to avoid resending
    digitalWrite(relay1, LOW);
  }

  // Reset flags if water level drops below 100
  if (val2 < 400 && soildry) {
    watermotor = false; // Allow for new motor on message when water level is low again
    soildry  = false; // Allow for new tank full message when tank is full again
  }



  if (val3 <= 100 && !motorOnSent) {
    sendSMS("+919398594569", "Motor is On");
    delay(2000);
    motorOnSent = true; // Set flag to avoid resending
    digitalWrite(relay, HIGH);
  }

  if (val3 > 450 && motorOnSent && !tankFullSent) {
    sendSMS("+919398594569", "Motor is Off. Tank Full");
    delay(2000);
    tankFullSent = true; // Set flag to avoid resending
    digitalWrite(relay, LOW);
  }

  // Reset flags if water level drops below 100
  if (val3 > 100 && tankFullSent) {
    motorOnSent = false; // Allow for new motor on message when water level is low again
    tankFullSent = false; // Allow for new tank full message when tank is full again
  }

  if(val>700)
  {
    digitalWrite(led,HIGH);
    digitalWrite(led2,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
    digitalWrite(led2,LOW);
  }


  SendWiFi_Data();
  delay(2000);
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
  getStr += String(val);
  getStr += "&field4=";
  getStr += String(val3);
  getStr += "&field5=";
  getStr += String(val2);
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
void project_name()
{
  lcd.setCursor(0,0);
  lcd.print("  Smart Garden");
  lcd.setCursor(0,1);
  lcd.print("   Automation");
  delay(3000);
}
