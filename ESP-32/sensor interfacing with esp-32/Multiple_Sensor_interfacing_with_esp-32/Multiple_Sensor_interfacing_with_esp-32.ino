#include<LiquidCrystal.h>
#include<DHT.h>
#define DHT_TYPE DHT11
#define DHT_PIN 25
DHT dht(DHT_PIN,DHT_TYPE);

int relay=15;
int ldr=13;
int relay1=4;

int trig=22;
int echo=23;
long duration;
int distance;

int red=18;
int water=12;

LiquidCrystal lcd(5,14,27,26,19,21);
void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(relay, OUTPUT);
  pinMode(relay1,OUTPUT);
  pinMode(red,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  project_name();
  dht.begin();
}

void loop() {
  float temp=dht.readTemperature();
  float hum=dht.readHumidity();
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=duration * 0.034/2;
  int value=analogRead(ldr);
  int val=analogRead(water);
  lcd.clear();
  
  Serial.print("Temperature:");
  Serial.println(temp);
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.setCursor(13,0);
  lcd.print(temp);
  delay(600);
  lcd.clear();
  Serial.print("Humidity:");
  Serial.println(hum);
  lcd.setCursor(0,0);
  lcd.print("Humidity:");
  lcd.setCursor(9,0);
  lcd.print(hum);
  delay(600);
  lcd.clear();
  Serial.print("Ldr:");
  Serial.println(value);
  lcd.setCursor(0,0);
  lcd.print("Ldr:");
  lcd.setCursor(4,0);
  lcd.print(value);
  delay(600);
  lcd.clear();
  Serial.print("distance:");
  Serial.print(distance);
  Serial.println("cm");
  lcd.setCursor(0,0);
  lcd.print("Distance:");
  lcd.setCursor(9,0);
  lcd.print(distance);
  delay(600);
  lcd.clear();
  Serial.print("Water-level:");
  Serial.println(val);
  lcd.setCursor(0,0);
  lcd.print("Water-level:");
  lcd.setCursor(12,0);
  lcd.print(val);
  delay(600);
  lcd.clear();
  delay(1000);

  
  if(value>3000)
  {
  digitalWrite(relay, HIGH);
  delay(1000);
  }
  else
  {
  digitalWrite(relay, LOW);
  delay(500);
  }

  if(distance<15)
  {
  digitalWrite(relay1, HIGH);
  delay(1000);
  }
  else
  {
  digitalWrite(relay1, LOW);
  delay(1000);
  }
  if(val>3500)
  {
  digitalWrite(red, HIGH);
  delay(1000);
  }
  else
  {
  digitalWrite(red, LOW);
  delay(1000);
  }

}
void project_name()
{
  lcd.setCursor(0,0);
  lcd.print("Multiple Sensor");
  lcd.setCursor(2,1);
  lcd.print("Interfacing");
  delay(3000);
}
