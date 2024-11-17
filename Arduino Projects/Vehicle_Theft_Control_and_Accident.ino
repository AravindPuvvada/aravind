#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd(8,9,4,5,6,7);
SoftwareSerial sim(2, 3);
String number = "+916281104093";
const int relayPin = 12;
TinyGPSPlus gps;
int vib=11;
int buzzer=10;
int v;
volatile float minutes, seconds;
volatile int degree, secs, mins;
unsigned long start;
uint8_t hr_val, min_val, sec_val;
bool loc_valid, alt_valid, time_valid;
double lat_val, lng_val, alt_m_val;

void setup() {
  
  Serial.begin(9600);
  lcd.begin(16, 2); // Sets the LCD size to 16 columns and 2 rows


  sim.begin(9600);
  project_name();
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  Serial.println("System Started...");
  pinMode(buzzer,OUTPUT);
  pinMode(vib,INPUT);
  delay(1000);
  sim.println("AT");  
  delay(500);
  
  sim.println("AT+CMGF=1"); // Set SMS text mode
  delay(500);
  
  sim.println("AT+CNMI=1,2,0,0,0"); // Enable SMS notification
  delay(500);
  Serial.println("GSM SIM800L Module Ready...");
  
}

void loop() {
  lcd.clear();
    get_GPSData();
    display_LongLati_Values();
    ReceiveMessage();
  
  if (sim.available() > 0) {
    Serial.write(sim.read());
  }
  v=digitalRead(vib);
  if(v==LOW)
  {
    lcd.clear();
    String locationMessage = "Alert!! Accident Detected Latitude: " + String(lat_val, 6) + ", Longitude: " + String(lng_val, 6);
    SendMessage(locationMessage);
    digitalWrite(buzzer,HIGH);
    lcd.print("Accident Detect");
        digitalWrite(relayPin,LOW);

    delay(1000);
    digitalWrite(relayPin,LOW);
  }
  else
  {
    digitalWrite(buzzer,LOW);
    lcd.print("Accident: None");
    delay(1000);
  }
  
}

void ReceiveMessage() {
  if (sim.available() > 0) {
    String receivedMessage = sim.readString();
    Serial.println("Received: " + receivedMessage);

    if (receivedMessage.indexOf("Engine on") >= 0) {
      digitalWrite(relayPin, HIGH);
      Serial.println("Relay ON");
    } 
    else if (receivedMessage.indexOf("Engine off") >= 0) {
      digitalWrite(relayPin, LOW);
      Serial.println("Relay OFF");
    } 
    else if (receivedMessage.indexOf("location") >= 0) {
      if (loc_valid) {
        String locationMessage = "Latitude: " + String(lat_val, 6) + ", Longitude: " + String(lng_val, 6);
        SendMessage(locationMessage);
        Serial.println("Location sent via SMS: " + locationMessage);
      } else {
        SendMessage("GPS location not available.");
        Serial.println("GPS location not available.");
      }
    } else {
      String locationMessage = "Latitude: " + String(lat_val, 6) + ", Longitude: " + String(lng_val, 6);
      Serial.println("Command not recognized");
    }
  }

  
}

void SendMessage(String message) {
  sim.println("AT+CMGF=1");
  delay(200);
  sim.println("AT+CMGS=\"" + number + "\"\r"); 
  delay(200);
  sim.print(message);
  delay(100);
  sim.write(26); // Send Ctrl+Z character to send SMS
  delay(2000);
  Serial.println("Message sent: " + message);
}

void display_LongLati_Values(){
  if (!loc_valid) {          
    Serial.print("Latitude:");
    Serial.println("*****");
    Serial.print("Longitude:");
    Serial.println("*****");
  } else {
    DegMinSec(lat_val);
  }
}

void get_GPSData(){
  smartDelay(1000); // Precise delay of 1 second
  lat_val = gps.location.lat(); // Get latitude data
  loc_valid = gps.location.isValid(); // Check if location data is valid
  lng_val = gps.location.lng(); // Get longitude data
  alt_m_val = gps.altitude.meters(); // Get altitude in meters
  alt_valid = gps.altitude.isValid(); // Check if altitude data is valid
}

static void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (Serial.available()) // Encode data read from GPS
      gps.encode(Serial.read());
  } while (millis() - start < ms);
}

void DegMinSec(double tot_val) { // Convert data in decimal degrees to degrees-minutes-seconds
  degree = (int)tot_val;
  minutes = tot_val - degree;
  seconds = 60 * minutes;
  minutes = (int)seconds;
  mins = (int)minutes;
  seconds = seconds - minutes;
  seconds = 60 * seconds;
  secs = (int)seconds;
}

void project_name() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vehicle Theft &");
  lcd.setCursor(0, 1);
  lcd.print("Accident Alert");
  delay(3000);
}
