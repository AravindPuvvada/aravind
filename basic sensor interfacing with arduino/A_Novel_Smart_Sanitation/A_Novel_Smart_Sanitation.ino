#include<LiquidCrystal.h>
#include<DHT.h>
#define DHT_TYPE DHT11
#define DHT_PIN A2
DHT dht(DHT_PIN,DHT_TYPE);
int relay3=10;
LiquidCrystal lcd(2,3,4,5,6,7);

int water=A0;
int val;
int relay1=8;

int ldr=A1;
int relay2=9;
int val1;

int val2;
int mq=A3;
int relay4=11;
void setup() {
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  dht.begin();
  project_name();  
}

void loop() {
 lcd.clear();
 waterLevel();
 Ldr();
 Dht();
 Mq();
 
}
void project_name()
{
  lcd.setCursor(0,0);
  lcd.print(" A Novel Smart");
  lcd.setCursor(2,1);
  lcd.print("Sanitation");
  delay(3000);
}
void waterLevel()
{
 val=analogRead(water);
 Serial.print("Water-level:");
 Serial.println(val);
 lcd.setCursor(0,0);
 lcd.print("Water level:");
 lcd.setCursor(13,0);
 lcd.print(val);
 delay(1000);
 if(val<50)
 {
  digitalWrite(relay1,HIGH);
  lcd.setCursor(2,1);
  lcd.print("Motor is ON"); 
  delay(500);
 }
 else if(val>450)
 {
  digitalWrite(relay1,LOW);
  lcd.setCursor(2,1);
  lcd.print("Motor is off");
  delay(600);
 }
 lcd.clear();
}
void Ldr()
{
 val1=analogRead(ldr);
 Serial.print("ldr:");
 Serial.println(val1);
 lcd.setCursor(0,0);
 lcd.print("LDR:");
 lcd.setCursor(5,0);
 lcd.print(val1);
 delay(1000);
 if(val1>600)
 {
  digitalWrite(relay2,HIGH);
  lcd.setCursor(1,1);
  lcd.print("Ligths Are ON"); 
  delay(500);
 }
 else
 {
  digitalWrite(relay2,LOW);
  lcd.setCursor(1,1);
  lcd.print("Ligths Are OFF");
  delay(600);
 
 }
  lcd.clear();
}
void Dht()
{
  float temp=dht.readTemperature();
  float hum=dht.readHumidity();
  Serial.print("Temperature:");
  Serial.print(temp);
  Serial.println("c");
  Serial.print("Humidity:");
  Serial.println(hum);
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.setCursor(12,0);
  lcd.print(temp);
  lcd.setCursor(0,1);
  lcd.print("Humidity:");
  lcd.setCursor(10,1);
  lcd.print(hum);
  delay(1000);
  lcd.clear();
   
  if(temp>35)
  {
    digitalWrite(relay3,HIGH);
    delay(500);
    lcd.setCursor(4,0);
    lcd.print("Fan is On");
  }
  else
  {
    digitalWrite(relay3,LOW);
    lcd.print("Fan is off");
  }
  delay(600);
  lcd.clear();
}

void Mq()
{
  val2=analogRead(mq);
  Serial.print("MQ-7:");
  Serial.println(val2);
  lcd.setCursor(0,0);
  lcd.print("MQ-7:");
  lcd.setCursor(5,0);
  lcd.print(val2);
  delay(1000);
  if(val2>400)
  {
    lcd.clear();
    digitalWrite(relay4,HIGH);
    lcd.setCursor(0,0);
    lcd.print("  Toxic Gases are");
    lcd.setCursor(3,1);
    lcd.print("Detected");
    delay("1000");
  }
  lcd.clear();
}
