#define BLYNK_DEBUG
#define BLYNK_TEMPLATE_ID "TMPL3u26PSuYY"
#define BLYNK_TEMPLATE_NAME "Garbage Monitoring System"
#define BLYNK_AUTH_TOKEN "xbwnZBlVm4O4DQ9L05AQax4tiV7X5REP"

#include<LiquidCrystal.h>
LiquidCrystal lcd(10,11,4,5,6,7);
int buzzer=A0;
#define BLYNK_PRINT Serial

#include <SoftwareSerial.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
int flag=0;

// Define SoftwareSerial for ESP8266
SoftwareSerial EspSerial(8, 9);
SoftwareSerial sim800l(12,13);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "projectpulse";
char pass[] = "hailucky123";

#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);

const int trigPin = 2;
const int echoPin = 3;

void setup() {

  Serial.begin(9600);

  Serial.begin(9600);
  delay(10);
  lcd.begin(16,2);
  sim800l.begin(9600);
  pinMode(buzzer,OUTPUT);
  project_name();
  delay(10);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
EspSerial.println("ATE0");  // Send ATE0 to disable echo
delay(800);
  // Blynk setup
  Blynk.begin(auth, wifi, ssid, pass);

  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
 
  long distance = measureDistance();
  lcd.clear();
  lcd.print("Distance:");
  lcd.print(distance);
  Serial.print("Distance:");
  Serial.println(distance);
  Blynk.virtualWrite(V0, distance); 
  if(distance<10)
  {
    lcd.setCursor(0,1);
    lcd.print(" Dustbin Full!!");
    sendSMS("+916300074004", "Dustbin level is full clear it fastly!!");
    Blynk.logEvent("dustbin_alert","dustbin level is full clear it fastly!!");
    buzz();
    lcd.clear();
    
  }
  /*
  if(distance>30 && distance<50)
  {
    
    sendSMS("+916300074004", "dustbin level is medium clear it!!");
    Blynk.logEvent("dustbin_notification","dustbin level is medium clear it!!");
  }
  */
  Blynk.run();
  delay(2000);
}

void buzz()
{
  digitalWrite(buzzer,HIGH);
  delay(800);
  digitalWrite(buzzer,LOW);
  delay(800);
  digitalWrite(buzzer,HIGH);
  delay(800);
  digitalWrite(buzzer,LOW);
  delay(800);
  digitalWrite(buzzer,HIGH);
  delay(800);
  digitalWrite(buzzer,LOW);
  delay(800);
  digitalWrite(buzzer,HIGH);
  delay(800);
  digitalWrite(buzzer,LOW);
  delay(800);
}

long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration / 2) * 0.0343;
  return distance;
}

void project_name() {
  lcd.setCursor(0,0);
  lcd.print("Garbage");
  lcd.setCursor(0,1);
  lcd.print("     Monitoring");
  delay(4000);
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
  Serial.println("SMS Sent");
}
