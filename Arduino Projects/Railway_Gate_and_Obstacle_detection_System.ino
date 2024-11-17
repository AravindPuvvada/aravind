#include <Servo.h>
#include <LiquidCrystal.h>

#define TRIG_PIN 2
#define ECHO_PIN 3
#define IR_PIN 4
#define IR1_PIN 5
#define buzzer A0
#define SERVO_PIN 6
int flag=0;
int plag=0;
int pass=0;
int i=0;
int j=0;
Servo cgate;
Servo ogate;
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(IR1_PIN, INPUT);
  pinMode(buzzer, OUTPUT);
  cgate.attach(SERVO_PIN);
  ogate.attach(7); 
  cgate.write(0);
  ogate.write(0);

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

  int Value = digitalRead(IR_PIN);
  int value = digitalRead(IR1_PIN);
  
  lcd.setCursor(0, 0);  // Move cursor to the second row
  lcd.print("D:");
  lcd.print(distance);
  if(pass==0)
  {
  if (value==0 || Value==0) {
    if(value==0)
    {
      lcd.setCursor(7,0);
      lcd.print("GT CLOSE");
      lcd.setCursor(0,1);
      lcd.print("TRAIN ARRIVED");
      digitalWrite(buzzer,HIGH);
      cgate.write(90);
      ogate.write(90);
      delay(3000);
      digitalWrite(buzzer,LOW);
      flag=1;
      pass=1;
      
    }
    else if(Value==0)
    {
      lcd.setCursor(7,0);
      lcd.print("GT CLOSE");
      lcd.setCursor(0,1);
      lcd.print("TRAIN ARRIVED");
      digitalWrite(buzzer,HIGH);
      cgate.write(90);
      ogate.write(90);
      delay(3000);
      digitalWrite(buzzer,LOW);
      plag=1;
      pass=1;
      
    }
  }
  }


  
  if(flag==1)
  {
    if(Value==0 or i==1)
    {
      i=1;
      if(Value==1)
      {
        lcd.clear();
       lcd.setCursor(0, 0);  // Move cursor to the second row
  lcd.print("D:");
  lcd.print(distance);
      lcd.setCursor(7,0);
      lcd.print("GT OPEN ");
      lcd.setCursor(0,1);
      lcd.print("TRAIN DEPARTURED");
      digitalWrite(buzzer,HIGH);
      cgate.write(0);
      ogate.write(0);
      delay(3000);
      digitalWrite(buzzer,LOW);
      flag=0;
      pass=0;
      i=0;
      lcd.clear();
      }
    }
  }
  
  if(plag==1 )
  {
    if(value==0 or j==1)
    {
      j=1;
      if(value==1)
      {
      lcd.clear();
      lcd.setCursor(0, 0);  // Move cursor to the second row
  lcd.print("D:");
  lcd.print(distance);
      lcd.setCursor(7,0);
      lcd.print("GT OPEN");
      lcd.setCursor(0,1);
      lcd.print("TRAIN DEPARTURED");
      digitalWrite(buzzer,HIGH);
      digitalWrite(buzzer,HIGH);
      cgate.write(0);
      ogate.write(0);
      delay(3000);
      digitalWrite(buzzer,LOW);
      plag=0;
      pass=0;
      j=0;
      lcd.clear();
      }
    }
  }

  delay(1000);
}

void projectName() {
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print("  Railway Gate");  
  lcd.setCursor(0, 1);  
  lcd.print(" Obstacle System");   
  delay(3000);  
  lcd.clear();
}
