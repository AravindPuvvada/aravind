#include <LiquidCrystal.h>

// Initialize the LCD with the numbers of the interface pins
LiquidCrystal lcd(D1, D2, D3, D4, D5, D6); // Replace with your actual pin numbers

void setup() {
  lcd.begin(16, 2);    // Set up the LCD's number of columns and rows
  lcd.print("Hello,"); // Print a message to the LCD
  lcd.setCursor(0, 1); // Set cursor to the beginning of the second row
  lcd.print("NodeMCU!");
}

void loop() {
  // Nothing to do here
}
