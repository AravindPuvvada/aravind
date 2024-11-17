#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();                 // Initialize the LCD
  lcd.backlight();            // Turn on the backlight
  lcd.setCursor(0, 0);        // Set cursor to the first row, first column
  lcd.print("Hello, World!"); // Print message on the first row
}

void loop() {
  lcd.setCursor(0, 1);        // Set cursor to the second row, first column
  lcd.print("I2C LCD Ready!"); // Print message on the second row
  delay(1000);
}
