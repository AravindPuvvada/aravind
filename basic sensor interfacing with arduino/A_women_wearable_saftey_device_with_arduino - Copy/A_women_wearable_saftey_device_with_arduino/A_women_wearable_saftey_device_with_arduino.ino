#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

TinyGPSPlus gps;


volatile float minutes, seconds;
volatile int degree, secs, mins;
unsigned long start;
uint8_t hr_val, min_val, sec_val;
bool loc_valid, alt_valid, time_valid;
double lat_val, lng_val, alt_m_val;

// Create instances for SoftwareSerial and LiquidCrystal
SoftwareSerial sim800l(8,9); // RX, TX
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // RS, E, D4, D5, D6, D7

int sw=10;
int buzzer=11;

void setup() {
  // Initialize SIM800L communication
  pinMode(buzzer,OUTPUT);
  sim800l.begin(9600);
  Serial.begin(9600);
  delay(1000);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.clear();
  project_name();
}

void loop() {
  if(digitalRead(sw)==0)
  {
  Serial.println("Button Pressed");
  lcd.print("SMS Sent!!");
  sendSMS("+919398594569", "Somebody is in the danger");
  digitalWrite(buzzer,HIGH);
  get_GPSData();
  display_LongLati_Values();
  delay(5000); // Delay between sending SMS
  }
  lcd.clear();
  digitalWrite(buzzer,LOW);
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
void project_name()
{
  lcd.setCursor(0,0);
  lcd.print(" Women Wearable");
  lcd.setCursor(0,1);
  lcd.print(" Saftey Device");
  delay(3000);
  lcd.clear();
}
void display_LongLati_Values(){
  if (!loc_valid)
        {          
          lcd.setCursor(0,0);
          lcd.print("Latitude : ");
          lcd.setCursor(0,1);
          lcd.print("*****");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Longitude : ");
          lcd.setCursor(0,1);
          lcd.print("*****");
          delay(1000);
          lcd.clear();
          
          Serial.print("Latitude:");
          Serial.println("*****");
          Serial.print("Longitude:");
          Serial.println("*****");
        }
        else
        {
          DegMinSec(lat_val);
          
          lcd.setCursor(0,0);
          Serial.println("LAT:");
          lcd.print("LAT: ");
          lcd.setCursor(5,0);
          Serial.println(lat_val, 8);
          lcd.print(lat_val, 8);
          lcd.setCursor(0,1);
          Serial.println("LON:");
          lcd.print("LON: ");
          lcd.setCursor(5,1);
          Serial.println(lng_val, 8);
          lcd.print(lng_val, 8);
        }
}

void get_GPSData(){
  {
        smartDelay(1000); /* Generate precise delay of 1ms */
        lat_val = gps.location.lat(); /* Get latitude data */
        loc_valid = gps.location.isValid(); /* Check if valid location data is available */
        lng_val = gps.location.lng(); /* Get longtitude data */
        alt_m_val = gps.altitude.meters();  /* Get altitude data in meters */
        alt_valid = gps.altitude.isValid(); /* Check if valid altitude data is available */
   }
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial.available())  /* Encode data read from GPS while data is available on serial port */
      gps.encode(Serial.read());
/* Encode basically is used to parse the string received by the GPS and to store it in a buffer so that information can be extracted from it */
  } while (millis() - start < ms);
}

void DegMinSec( double tot_val)   /* Convert data in decimal degrees into degrees minutes seconds form */
{  
  degree = (int)tot_val;
  minutes = tot_val - degree;
  seconds = 60 * minutes;
  minutes = (int)seconds;
  mins = (int)minutes;
  seconds = seconds - minutes;
  seconds = 60 * seconds;
  secs = (int)seconds;
}
