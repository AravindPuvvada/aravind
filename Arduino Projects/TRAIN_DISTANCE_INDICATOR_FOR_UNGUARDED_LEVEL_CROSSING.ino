#include <Servo.h>
#include <LiquidCrystal.h>

#define TRIG_PIN 2
#define ECHO_PIN 3
#define Vib_PIN 4
#define buzzer A0
#define SERVO_PIN 6
int flag=0;
int i=0;
int j=0;
Servo cgate;
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(Vib_PIN, INPUT);
  pinMode(buzzer, OUTPUT);
  cgate.attach(SERVO_PIN);
  
  cgate.write(0);
  

  lcd.begin(16, 2);  
  projectName();
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = (duration * 0.034) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  int Value = digitalRead(Vib_PIN);
  
  lcd.setCursor(0, 0);  // Move cursor to the second row
  lcd.print("Distance:");
  lcd.print(distance);
  Serial.println(flag);
  if (distance<20 && Value==0) {
      lcd.clear();
      lcd.setCursor(0, 0);  // Move cursor to the second row
      lcd.print("Distance:");
      lcd.print(distance);
      lcd.setCursor(0,1);
      lcd.print("GATE CLOSED");
      if(flag==0)
      {
      digitalWrite(buzzer,HIGH);
      cgate.write(90);
      delay(3000);
      digitalWrite(buzzer,LOW);
       flag=1;
      }
      
     
      delay(800);
    
  }


  else
  {
  
      lcd.clear();
      lcd.setCursor(0, 0);  // Move cursor to the second row
      lcd.print("Distance:");
      lcd.print(distance);
      lcd.setCursor(0,1);
      lcd.print("GATE OPEN");
      if(flag==1)
      {
      digitalWrite(buzzer,HIGH);
      cgate.write(0);
      delay(3000);
      digitalWrite(buzzer,LOW);
      flag=0;
      }
      delay(1000);
      }
      
  delay(1000);
}

void projectName() {
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print(" Train Distance");  
  lcd.setCursor(0, 1);  
  lcd.print("   Indicator");   
  delay(3000);  
  lcd.clear();
}
