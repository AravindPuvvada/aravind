#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#define DHT_TYPE DHT11
#define DHT_PIN A5
DHT dht(DHT_PIN,DHT_TYPE);
// Create instances for SoftwareSerial and LiquidCrystal
SoftwareSerial sim800l(0, 1); // RX, TX
LiquidCrystal lcd(10, 11, 4, 5, 6, 7); // RS, E, D4, D5, D6, D7

int ldr;
int led=7;

int rain;
int water;
int mq;
void setup() {
  // Initialize SIM800L communication
  sim800l.begin(9600);
  delay(1000);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sending SMS...");
  pinMode(led,OUTPUT);

  dht.begin();
}

void loop() {
  sendSMS("+919441348531","Hello From STTMani");
  float temp=dht.readTemperature();
  float hum=dht.readHumidity();
 
  if(hum>40)
  {
  sendSMS("+917396055789",("Alert humidity is:"+String(hum)).c_str());
  delay(4000); 
  }else
  {
    sendSMS("+917396055789",("humidity is Normal:"+String(hum)).c_str());
      delay(4000); 
  }
  if(temp>32)
  {
    sendSMS("+917396055789",("Alert temperature is:"+String(temp)).c_str());
    delay(4000);
  }

  ldr=analogRead(A4);
  if(ldr>400)
  {
    sendSMS("+917396055789",("Alert Turn on the ligths:"+String(ldr)).c_str());
    delay(4000);
    digitalWrite(led,HIGH);
  }
  else
   {
    sendSMS("+917396055789",("Alert Turn of the ligths:"+String(ldr)).c_str());
    delay(4000);
    digitalWrite(led,LOW);
  }
  rain=analogRead(A3);
  if(rain<150)
  {
    sendSMS("+917396055789",("Alert Rain is heavy:"+String(rain)).c_str());
    delay(4000);
  }
  else if(rain>=150 && rain<=550)
  {
    sendSMS("+917396055789",("Alert rain is slowly increasing:"+String(rain)).c_str());
    delay(4000);
  }
  else
  {
    sendSMS("+917396055789",("No rainfall:"+String(rain)).c_str());
    delay(4000);
  }

  water=analogRead(A2);
  if(water==0)
  {
    sendSMS("+917396055789",("Alert No water:"+String(water)).c_str());
    delay(4000);
  }
  else if(water>0 && water<100)
  {
    delay(500);
  }
  else
  {
    sendSMS("+917396055789",("Alert Water level is full:"+String(water)).c_str());
    delay(4000);
  }
  mq=analogRead(A1);
  if(mq>200)
  {
    sendSMS("+917396055789",("Gas is detected:"+String(mq)).c_str());
    delay(4000);
  }
  // You can add more logic or functionality here if needed
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
