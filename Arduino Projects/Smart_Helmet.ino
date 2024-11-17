//Smart Helmet
#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

int trig=8;
int echo=9;
long duration;
int distance;

int mq3=A0;
int val;

int relay=10;
int buzzer=11;


void setup()
{
  lcd.begin(16,2);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
  pinMode(relay,OUTPUT);
  pinMode(buzzer,OUTPUT);
  digitalWrite(relay, LOW);
  project_name();
}

void loop()
{
  lcd.clear();
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=duration * 0.034/2;
  //Mq3 block
  val=analogRead(mq3);
  val=val/4;
  Serial.print("Mq3:");
  Serial.println(val);
  Serial.print("distance:");
  Serial.print(distance);
  Serial.println("cm");
  lcd.setCursor(0,0);
  lcd.print("Distance:");
  lcd.setCursor(10,0);
  lcd.print(  distance);
  lcd.setCursor(0,1);
  lcd.print("Alcohol:");
  lcd.setCursor(9,1);
  lcd.print(val);
  delay(1500);
  lcd.clear();
  if(distance<10 && val<200)
  {
    digitalWrite(relay,HIGH);
    lcd.setCursor(0,0);
    lcd.print(" Happy Journey");
    delay(1000);
  }
  else if(distance>10 || val>200)
  {
    digitalWrite(relay,LOW);
    buzzer_sound();
    
    if(distance>10 && val>200)
    {
      lcd.setCursor(3,0);
      lcd.print("Alcohol is");
      lcd.setCursor(3,1);
      lcd.print("Detected!!");
      delay(1000);
    }
    else if(distance>10)
    {
      Serial.println("Please Wear Helmet");
      lcd.setCursor(2,0);
      lcd.print("Please wear");
      lcd.setCursor(3,1);
      lcd.print("Helmet!!");
      delay(1000);
    }
    else if(val>200)
    {
      Serial.println("Alcohol is Detected");
      lcd.setCursor(3,0);
      lcd.print("Alcohol is");
      lcd.setCursor(3,1);
      lcd.print("Detected!!");
      delay(1000);
  
    }
    lcd.clear();
  }
}

void buzzer_sound()
{
  digitalWrite(buzzer, HIGH);
  delay(600);
  digitalWrite(buzzer, LOW);
  delay(600);
  digitalWrite(buzzer, HIGH);
  delay(600);
  digitalWrite(buzzer, LOW);
  delay(600);
}

void project_name()
{
  lcd.setCursor(0,0);
  lcd.print("  Smart Helmet");
  delay(3000);
  lcd.clear();
}
