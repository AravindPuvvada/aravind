//                                 SMART PARKING SYSTEM

#define BLYNK_TEMPLATE_ID "TMPL3Wrkhg4jh"
#define BLYNK_TEMPLATE_NAME "Smart Parking"
#define BLYNK_AUTH_TOKEN "QyZDrHp4ig6hn9C3SFbxDsZkL8S7A-6z"

#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// Replace with your Blynk Auth Token
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials
char ssid[] = "projectpulse";
char pass[] = "hailucky123";

// Set your ESP8266 Serial object
#define EspSerial Serial

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);


#include<Servo.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int ir=9;
int ir1=10;
int ir2=11;
Servo park;
int slot=2;
void setup() 
{
  Serial.begin(9600);
  Serial.println("...");
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
    Blynk.begin(auth, wifi, ssid, pass);
  Serial.println("Welcome To Smart Parking System");
  lcd.begin(16,2);
  park.attach(8);
  park.write(0);
  pinMode(ir,INPUT);
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  project_name();
  lcd.clear();
  Serial.println("Getting Started");

}

void loop() 
{
  Blynk.run();
  lcd.setCursor(0,0);
  lcd.print("Available Slots");
  int val=digitalRead(ir);
  int val2=digitalRead(ir1);
  int val3=digitalRead(ir2);
  Blynk.virtualWrite(V0,val);
  Blynk.virtualWrite(V1,val2);
  Serial.print("val1:");
  Serial.println(val);
  Serial.print("val2:");
  Serial.println(val2);
  if(val3==0)
  {
    if(val==0 && val2==0)
    {
      park.write(0);
    }
    else
    {
      park.write(90);
      delay(3000);
      park.write(0);
    }
  }
  if(val==0 && val2==0)
  {
   Serial.println("No Slots Are Available");
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Sorry! No Slots");
   lcd.setCursor(0,1);
   lcd.print(" are available");
   delay(500);
   lcd.clear();
  }
  if(val==0 && val2==1)
  {
    lcd.setCursor(0,1);
    lcd.print("      Slot 2");
    delay(1000);
    lcd.clear();
  }
  if(val==1 && val2==1)
  {
    lcd.setCursor(0,1);
    lcd.print("Slot 1 & Slot 2");
    delay(1000);
    lcd.clear();
  }
  if(val==1 && val2==0)
  {
    lcd.setCursor(0,1);
    lcd.print("      Slot 1");
    delay(1000);
    lcd.clear();
  }
}

void project_name()
{
  lcd.print(" Smart Parking");
  lcd.setCursor(0,1);
  lcd.print("     System");
  delay(4000);
}
