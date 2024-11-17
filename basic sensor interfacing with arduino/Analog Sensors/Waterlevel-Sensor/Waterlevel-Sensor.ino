#include<LiquidCrystal.h>
LiquidCrystal lcd(10,11,12,13,9,8);
int led=7;
int led1=6;
int led2=5;

void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop() {
  int value=analogRead(A0);
  //value=value/2;
  Serial.print("Water:");
  Serial.println(value);
  lcd.setCursor(0,0);
  lcd.print("Water-level:");
  delay(1000);
  lcd.setCursor(13,0);
  lcd.print(value);
  delay(1000);
  lcd.clear();
  
  if(value==0)
  {
 
    digitalWrite(led,LOW);
    lcd.setCursor(5,1);
    lcd.print("empty");
    delay(1000);
    lcd.clear();
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
  }
  else if(value>0 && value<=150)
  {
    digitalWrite(led,HIGH);
    lcd.setCursor(3,1);
    lcd.print("LOW");
    delay(1000);
    lcd.clear();
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
  }
  else if(value<=270)
  {
    
    digitalWrite(led1,HIGH);

    lcd.setCursor(3,1);
    lcd.print("moderate");
    delay(1000);
    lcd.clear();
    digitalWrite(led,LOW);
    digitalWrite(led2,LOW);
  }
  else
  {
    digitalWrite(led2,HIGH);
    lcd.setCursor(3,1);
    lcd.print("High");
    delay(1000);
    lcd.clear();
    digitalWrite(led,LOW);
    digitalWrite(led1,LOW);
  }
}
