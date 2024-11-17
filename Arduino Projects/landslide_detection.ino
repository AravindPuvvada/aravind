#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

// Create instances for SoftwareSerial and LiquidCrystal
SoftwareSerial sim800l(8,9); // RX, TX
LiquidCrystal lcd(10,11, 4, 5, 6, 7); // RS, E, D4, D5, D6, D7

int ir=2;
int rain=A0;
int soil=A1;
int buzzer=13;

void setup() {
  // Initialize SIM800L communication
  pinMode(ir,INPUT);
  pinMode(buzzer,OUTPUT);
  sim800l.begin(9600);
  Serial.begin(9600);
  lcd.begin(16, 2);
  project_name();
}

void loop() {
  int value=analogRead(soil);
  Serial.print("Soil:");
  Serial.println(value);
  int value1=analogRead(rain);
  Serial.print("Rain:");
  Serial.println(value1);
  lcd.setCursor(0,0);
  lcd.print("Rain-Value:");
  lcd.print(value1);
  if (value1<600)
  {
    Serial.println("Rain is Detected");
    lcd.setCursor(0,1);
    lcd.print("Rain Detected");
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("No Rain Detect");
  }
  delay(800);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Soil-Value:");
  lcd.print(value);
  if (value>700)
  {
    Serial.println("Soil is Dry");
    lcd.setCursor(0,1);
    lcd.print("Soil is dry");
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("Soil is wet");
  }
  Serial.print("ir:");
  Serial.println(digitalRead(ir));
  delay(800);
  lcd.clear();
  if(digitalRead(ir)==0)
  {
  Serial.println("Landslide Detected");

  lcd.setCursor(0,0);
  lcd.print(" Alert LandSlide");
  lcd.setCursor(0,1);
  lcd.print("  is Detected");
  sendSMS("+916281104093", "Landslide is detected");
  buzz();
  delay(1000); // Delay between sending SMS
  Serial.println("SMS Sent");
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("  LandSlide is");
    lcd.setCursor(0,1);
    lcd.print("  Not Detected");
    delay(800);
    
  }
  lcd.clear();
  
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
  lcd.print("   Landslide");
  lcd.setCursor(0,1);
  lcd.print("   Detection");
  delay(3000);
  lcd.clear();
}
void buzz()
{
  digitalWrite(buzzer,HIGH);
  delay(600);
  digitalWrite(buzzer,LOW);
  delay(600);
  digitalWrite(buzzer,HIGH);
  delay(600);
  digitalWrite(buzzer,LOW);
  delay(600);
  digitalWrite(buzzer,HIGH);
  delay(600);
  digitalWrite(buzzer,LOW);
  delay(600);
  digitalWrite(buzzer,HIGH);
  delay(600);
  digitalWrite(buzzer,LOW);
  delay(600);
}
