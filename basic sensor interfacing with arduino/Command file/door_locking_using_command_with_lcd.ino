#include<LiquidCrystal.h>
LiquidCrystal lcd(4,5,6,7,8,9);
int green=2,red=3;
String password="";
void setup() {
Serial.begin(9600);
pinMode(green,OUTPUT);
pinMode(red,OUTPUT);
lcd.begin(16,2);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Enter password:");
  delay(1000);
  if(Serial.available())
  {
    while(Serial.available())
    {
      char alpha=(char)Serial.read();
      password+=alpha;
      if(alpha=='\n')
      {
        Serial.println("Enter a password:");
        password.trim();
        if(password=="Aravind")
        {
          digitalWrite(green,HIGH);
          delay(1000);
          digitalWrite(red,LOW);
          Serial.println("Accesed");
          lcd.setCursor(4,1);
          lcd.clear();
          lcd.print("Accessed");
          delay(1000);
        }
        else
        {
          digitalWrite(red,HIGH);
          delay(1000);
          digitalWrite(green,LOW);
          Serial.println("Invalid");
          lcd.setCursor(4,1);
          lcd.clear();
          lcd.print("Invalid");
          delay(1000);hello
          
        }
        delay(2000);
        digitalWrite(green,LOW);
        digitalWrite(red,LOW);
        password="";
        lcd.setCursor(4,1);
        lcd.clear();
      }
    }
  }

}
