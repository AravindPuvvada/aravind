//GPS is used in this project,Tx of GPS is connected to Rx of Arduino. Gps reads the data and transmit data to arduino, arduino receives data and display the data on LCD//
#include <TinyGPS++.h>
#include<LiquidCrystal.h>


LiquidCrystal lcd(2, 3, 4, 5, 6, 7);//RS=2,E=3,D4=4,D5=5,D6=6,D7=7//

TinyGPSPlus gps;

volatile float minutes, seconds;
volatile int degree, secs, mins;
unsigned long start;
uint8_t hr_val, min_val, sec_val;
bool loc_valid, alt_valid, time_valid;
double lat_val, lng_val, alt_m_val;

void setup() {
  Serial.begin(9600); /* Define baud rate for serial communication */
  //lcd.begin(16, 2);
}

void loop(){
  get_GPSData();
  display_LongLati_Values();
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
