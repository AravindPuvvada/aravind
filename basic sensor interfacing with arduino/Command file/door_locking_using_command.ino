#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int red=12,green=11;
String password="";
//int sw=8,sw=9;
void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
}
void loop()
{
  if(Serial.available())
  {
    
    
    while (Serial.available())
    {
    char pass=(char)Serial.read();
    password+=pass;
    if(pass=='\n')
    {
      Serial.println("Enter password");
      password.trim();
      
    if(password=="Aravind" || password=="Rajith")
    {
      //Serial.println(password);
      Serial.println("Accesed");
      digitalWrite(green,HIGH);
      delay(1000);
      digitalWrite(red,LOW);
      
    }
    else
    {
      //Serial.println(pass);
      Serial.println("Invalid");
      digitalWrite(red,HIGH);
      delay(1000);
      digitalWrite(green,LOW);
    }
    password="";
  }
 }
}
}
