#include<LiquidCrystal.h>
LiquidCrystal lcd(5,14,27,26,19,21);
void setup() 
{
  lcd.begin(16,2);
}

void loop() 
{
  lcd.setCursor(0,1);
  lcd.print("Aravind");
  delay(1000);
}
