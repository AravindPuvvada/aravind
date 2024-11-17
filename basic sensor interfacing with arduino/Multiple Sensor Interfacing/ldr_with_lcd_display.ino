#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int ldr=A0;
int led=10;
void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value=analogRead(A0);
  Serial.print("ldr value:");
  Serial.println(value);
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("ldr value:");
  delay(1000);
  lcd.setCursor(11,1);
  lcd.print(value);
  delay(500);
  lcd.clear();
  if(value>400)
  {
    digitalWrite(led,HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(led,LOW);
  }
}
