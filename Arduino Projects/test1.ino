#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include<Servo.h>

Servo rad;
SoftwareSerial BTSerial(0, 1);
LiquidCrystal lcd(10, 11, 4, 5, 6, 7);
SoftwareSerial sim800l(12,13); 

const int motor1of1 = A1;
const int motor1of2 = A2;
const int motor2of1 = A3;
const int motor2of2 = A4;

const int trigPin = 2;
const int echoPin = 3;

String motorStatus = "Stopped";

void setup() {
  sim800l.begin(9600);
  pinMode(motor1of1, OUTPUT);
  pinMode(motor1of2, OUTPUT);
  pinMode(motor2of1, OUTPUT);
  pinMode(motor2of2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  rad.attach(4);
  rad.write(0);

  BTSerial.begin(9600);
  Serial.begin(9600);
  lcd.begin(16, 2); 
  
  projectName();
}

void loop() {
  lcd.clear();
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  lcd.setCursor(0, 0);
  lcd.print("Dist:");
  lcd.print(distance);

  lcd.setCursor(0, 1);
  lcd.print(motorStatus);

  /*
  int angle=0;
  int i=0;
  if(i==0)
  {
  rad.write(angle);
  angle+=20;
  if(angle==180)
  {
    i=1;
  }
  }
  if(i==1)
  {
    angle-=20;
    rad.write(angle);
    if(angle==0)
    {
      i=0;
    }
    
  }
  */

  if(distance<15)
  {
   stop();
   return;
  }
  if (BTSerial.available()) {
    String command = BTSerial.readStringUntil('\n');
    command.trim();
    
    if (command.equalsIgnoreCase("forward") || command == "1") {
      Serial.println("Moving Forward");
      front();
      motorStatus = "Forward";
    } 
    else if (command.equalsIgnoreCase("backward") || command == "2") {
      Serial.println("Moving Backward");
      back();
      motorStatus = "Backward";
    }
    else if (command.equalsIgnoreCase("turn left") || command == "3") {
      Serial.println("Turning Left");
      left();
      motorStatus = "Turning Left ";
    }
    else if (command.equalsIgnoreCase("turn right") || command == "4") {
      Serial.println("Turning Right");
      right();
      motorStatus = "Turning Right ";
    }
    else if (command.equalsIgnoreCase("stop") || command == "5") {
      stop();
      motorStatus = "Stopped     ";
      Serial.println("Stopping");
    }

     else if (command.equalsIgnoreCase("radar on") || command == "5") {

     for (int pos = 0; pos <= 180; pos += 45) { // Move from 0 to 180 degrees
    rad.write(pos);
    delay(500); // Wait for half a second
  }
  for (int pos = 180; pos >= 0; pos -= 45) { // Move back from 180 to 0 degrees
    rad.write(pos);
    delay(500);
  }

  
  }

  delay(1000);
  }
}

void projectName() {
  lcd.setCursor(0, 0);
  lcd.print("  Voice Control");
  lcd.setCursor(0, 1);
  lcd.print("   Wheelchair");
  delay(3000);
}

void front() {
  digitalWrite(motor1of1, HIGH);
  digitalWrite(motor1of2, LOW);
  digitalWrite(motor2of1, HIGH);
  digitalWrite(motor2of2, LOW);
}

void back() {
  digitalWrite(motor1of1, LOW);
  digitalWrite(motor1of2, HIGH);
  digitalWrite(motor2of1, LOW);
  digitalWrite(motor2of2, HIGH);
}

void left() {
  digitalWrite(motor1of1, LOW);
  digitalWrite(motor1of2, HIGH);
  digitalWrite(motor2of1, HIGH);
  digitalWrite(motor2of2, LOW);
  delay(2500);
  stop();
}

void right() {
  digitalWrite(motor1of1, HIGH);
  digitalWrite(motor1of2, LOW);
  digitalWrite(motor2of1, LOW);
  digitalWrite(motor2of2, HIGH);
  delay(2500);
  stop();
}

void stop() {
  digitalWrite(motor1of1, LOW);
  digitalWrite(motor1of2, LOW);
  digitalWrite(motor2of1, LOW);
  digitalWrite(motor2of2, LOW);
}
