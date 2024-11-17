#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <DHT.h>

SoftwareSerial BTSerial(0, 1);
LiquidCrystal lcd(10, 11, 4, 5, 6, 7);
SoftwareSerial sim800l(12,13); 
#define DHTPIN A4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int motor1of1 = A0;
const int motor1of2 = A1;
const int motor2of1 = A2;
const int motor2of2 = A3;

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

  BTSerial.begin(9600);
  Serial.begin(9600);
  lcd.begin(16, 2); 
  dht.begin();
  
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
  
  if (distance < 20) {
    stop();
    lcd.setCursor(0, 0);
    lcd.print("Dist:");
    lcd.print(distance);
    lcd.setCursor(0, 1);
    lcd.print("Obstacle Detect");
    delay(1000);
    motorStatus = "Stopped";
  }
  
  int temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    lcd.setCursor(10, 0);
    lcd.print("T:");
    lcd.print(temperature);
    
  }

  if(temperature>40)
  {
    sendSMS("+919441348531", ("Alert!! Temperature Becomes High: " + String(dht.readTemperature())).c_str());
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
  }

  delay(1000);
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
void sendSMS(const char* phoneNumber, const char* message) {
  sim800l.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  sim800l.print("AT+CMGS=\"");
  sim800l.print(phoneNumber);
  sim800l.println("\"");
  delay(1000);
  sim800l.print(message);
  sim800l.write(0x1A); // Send Ctrl+Z to finish message
  delay(1000);
}
