#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
LiquidCrystal lcd(2,3, 4, 5, 6, 7);

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS A0

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

void setup(void)
{
  sensors.begin();  // Start up the library
  lcd.begin(16, 2);
  Serial.begin(9600);
  project_Name();
}

void loop(void)
{
  // Send the command to get temperatures
  sensors.requestTemperatures();

  //print the temperature in Celsius
  //Serial.print("Temperature: ");
  lcd.setCursor(0, 0);
  lcd.print("Temperature:    ");
  lcd.setCursor(0, 1);
  lcd.print(sensors.getTempCByIndex(0));
  lcd.setCursor(6, 1);
  lcd.print("C ,");
  delay(1000);
  //Serial.print(sensors.getTempCByIndex(0));
  //Serial.print((char)176);//shows degrees character
  //Serial.print("C  |  ");

  //print the temperature in Fahrenheit
  Serial.println((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  lcd.setCursor(9, 1);
  lcd.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  delay(1000);
  lcd.setCursor(15, 1);
  lcd.print("F");
  //Serial.print((char)176);//shows degrees character
  //Serial.println("F");

  delay(500);
}

void project_Name() {
  lcd.setCursor(0, 0);
  delay(1000);
  lcd.print("    STT-MANI    ");
  delay(2500);
  lcd.setCursor(0, 1);
  lcd.print("  Arduino UNO   ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  delay(1000);
  lcd.print("Interfacing With");
  delay(2500);
  lcd.setCursor(0, 1);
  lcd.print(" DS18b20 Sensor ");
  delay(2000);
  lcd.clear();
}
