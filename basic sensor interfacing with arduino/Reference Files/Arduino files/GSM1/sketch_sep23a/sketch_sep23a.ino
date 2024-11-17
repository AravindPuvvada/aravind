#include <SoftwareSerial.h>
SoftwareSerial sim(8, 9);//Tx of GSM to arduino pin 8, Rx of GSM to arduino pin 9//
#include <LiquidCrystal.h>
const int rs = 10, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int _timeout;
String _buffer;
String number = "+916300074004"; //-> change with your number
void setup() {
  //delay(7000); //delay for 7 seconds to make sure the modules get the signal
 lcd.begin(16, 2);
  lcd.setCursor(0,0);
    lcd.print("Subscribe");
    lcd.setCursor(0,1);
    lcd.print("STT-MANI");
  Serial.begin(9600);
  _buffer.reserve(50);
  Serial.println("System Started...");
  sim.begin(9600);
  delay(1000);
  Serial.println("Type s to send an SMS, r to receive an SMS, and c to make a call");
 delay(6000);

 }
void loop() {
   
    lcd.setCursor(0,0);
    lcd.print("  GSM SIM 800L ");
    lcd.setCursor(0,1);
    lcd.print("Caller ID Projct"); 
  if (Serial.available() > 0)
    switch (Serial.read())
    {
      case 's':
        SendMessage();
        break;
      case 'r':
        RecieveMessage();
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You May Send");
     lcd.setCursor(0,1);
    lcd.print("Message Now"); 
    delay(6000);
        break;
      case 'c':
        callNumber();
        break;
    }
  if (sim.available() > 0)
    Serial.write(sim.read());
}
void SendMessage()
{
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(200);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(200);
  String SMS = "Hello, how are you? ";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(200);
  _buffer = _readSerial();
  lcd.clear();
   lcd.setCursor(0,0);
    lcd.print("Sending ... ");
    lcd.setCursor(0,1);
    lcd.print("Hello, how r u?");
  delay(5000);


}
void RecieveMessage()
{
  Serial.println ("SIM800L Read an SMS");
  sim.println("AT+CMGF=1");
  delay (200);
  sim.println("AT+CNMI=1,2,0,0,0"); // AT Command to receive a live SMS
  delay(200);
  Serial.write ("Unread Message done");
   
}
String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
   
  }
  
  if (sim.available()) {
    return sim.readString();
    
   
     
  }
}
void callNumber() {
  sim.print (F("ATD"));
  sim.print (number);
  sim.print (F(";\r\n"));
  _buffer = _readSerial();
  Serial.println(_buffer);
   lcd.clear();
   lcd.setCursor(0,0);
    lcd.print("Calling.... ");
    lcd.setCursor(0,1);
    lcd.print("+916300074004");
  delay(14000);
}
