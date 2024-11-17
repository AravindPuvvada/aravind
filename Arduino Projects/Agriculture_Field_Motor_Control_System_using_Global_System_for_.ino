#include<LiquidCrystal.h>
#include <SoftwareSerial.h>

// Create instances for SoftwareSerial and LiquidCrystal
LiquidCrystal lcd(10,11,4,5,6,7);
SoftwareSerial sim800l(2,3); // RX, TX
int Soil=A0;
int relay=12;

bool watermotor = false;
bool soildry = false;
void setup() 
{
 pinMode(Soil,INPUT);
 pinMode(relay,OUTPUT);
 Serial.begin(9600);
 sim800l.begin(9600);
 lcd.begin(16,2);
 project_name();

}

void loop() {
int value=analogRead(Soil);
Serial.print("Soil-Value:");
Serial.println(value);
lcd.setCursor(0,0);
lcd.print("Soil Value:");
lcd.print(value);
if(value>=600)
{
      lcd.setCursor(0,1);
      lcd.print("    Motor On");
      delay(800);
}
else
{
      lcd.setCursor(0,1);
      sendSMS("+919398594569", "water pump is Off Soil is wet");
      lcd.print("    Motor Off");
      
      delay(800);
}
if (value >=600 && !watermotor) {
  sendSMS("+919398594569", "Soil is Dry\nWater Pump is On");
    digitalWrite(relay, HIGH);
    
    watermotor = true; // Set flag to avoid resending
    
    delay(800);
   
  }

  if (value < 600 && watermotor && !soildry ) {
    digitalWrite(relay, LOW);
    
    sendSMS("+919398594569", "water pump is Off Soil is wet");
    delay(800);
    soildry  = true; // Set flag to avoid resending
   
  }

  // Reset flags if water level drops below 100
  if (value < 600 && soildry) {
    watermotor = false; // Allow for new motor on message when water level is low again
    soildry  = false; // Allow for new tank full message when tank is full again
  }
  delay(1000);
  lcd.clear();
}
void project_name()
{
  lcd.setCursor(0,0);
  lcd.print("Agri Motor");
  lcd.setCursor(0,1);
  lcd.print("     Control GSM");
  delay(3000);
  lcd.clear();
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
