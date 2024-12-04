#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
int relay = 8;
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define BUTTON_1_PIN 2  
#define BUTTON_2_PIN 3  
#define BUTTON_3_PIN 4  

const int duration500ml = 2;  
const int duration1Ltr = 4;  
const int duration2Ltr = 6;     

const unsigned long buttonTimeout = 10000;


void displayTitle() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("       Water ATM");
}

void setup() {

  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
  pinMode(BUTTON_3_PIN, INPUT_PULLUP);
  pinMode(7, 1);
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();
  displayTitle();
  delay(3000);
  displayTitle();
  lcd.clear();
  
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Scan Your Card...");
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  if (content.substring(1) == "33 C3 3D E1") {
    Serial.println("Authorized access");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Authorized ");
    lcd.setCursor(0, 1);
    lcd.print("  Access Granted");
    delay(1000);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Select Quantity:");
     lcd.setCursor(0,1);
     lcd.print("500 1000 2000");
     delay(1500);
     while (true) {
        if (digitalRead(BUTTON_1_PIN) == LOW) {
          
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Selected Qty:");
          lcd.setCursor(0,1);
          lcd.print("500ml");
          activateRelay(duration500ml);
          break;
        } else if (digitalRead(BUTTON_2_PIN) == LOW) {
          
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Selected Qty:");
          lcd.setCursor(0,1);
          lcd.print("1000ml");
          activateRelay(duration1Ltr);
          break;
        } else if (digitalRead(BUTTON_3_PIN) == LOW) {
          
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Selected Qty:");
          lcd.setCursor(0,1);
          lcd.print("2000ml");
          activateRelay(duration2Ltr);
          break;
        }
    } 
    lcd.clear();
  } 
  
  else {
    Serial.println(" Access denied");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   Access ");
    lcd.setCursor(0, 1);
    lcd.print("   Denied ");
    digitalWrite(relay, 0);
    delay(2000);
    
  }
  
}

void activateRelay(int duration) {
  digitalWrite(relay, HIGH); // Turn on the relay
  delay(duration * 1000); // Activate for the specified duration
  digitalWrite(relay, LOW); // Turn off the relay
}
